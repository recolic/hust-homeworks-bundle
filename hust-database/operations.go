package main

import (
	"errors"
	"fmt"
	"github.com/go-pg/pg"
	"github.com/go-pg/pg/orm"
	"strconv"
	"strings"
)

func checkUserUpdatePermission(commiter uid_t, updatedUserPerm []string) bool {
	updatedUserIsCustomer := true
	if ArrayContains(updatedUserPerm, PERM_ADMIN) ||
		ArrayContains(updatedUserPerm, PERM_CASHIER) ||
		ArrayContains(updatedUserPerm, PERM_CUSTOMER_SERV) {
		updatedUserIsCustomer = false
	}

	if commiter != ROOT_UID {
		// if uid is 1(root), just skip all check. so that system can create uid 1 without permission.
		if !updatedUserIsCustomer {
			// Admin can create non-customer user.
			if CheckPermission(commiter, PERM_ADMIN) == false {
				return false
			}
		} else {
			// costomer_serv can create customer user.
			if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
				return false
			}
		}
	}
	return true
}

func AddUser(commiter uid_t, name, password, permissions, email string) (uid_t, error) {
	// password is already salted-hashed in client.
	// TODO: role maybe a comma-seperated string as permission list.
	perm := strings.Split(permissions, ",")
	if checkUserUpdatePermission(commiter, perm) == false {
		return -1, errors.New("Permission denied.")
	}

	newUid := uid_t(0)

	err := db.RunInTransaction(func(tx *pg.Tx) error {
		u := UserInfo{
			Name:         name,
			Password:     password,
			Permissions:  perm,
			Balance:      0,
			Achievements: 0,
			Email:        email,
		}

		err := tx.Insert(&u)
		if err != nil {
			return err
		}
		newUid = u.Id

		if ArrayContains(perm, PERM_CUSTOMER) {
			// The CustomerService is introducing new customer. Give him salary!
			commiter := UserInfo{
				Id: commiter,
			}
			err2 := tx.Select(&commiter)
			if err2 != nil {
				return err2
			}

			commiter.Achievements += EARNING_PER_ADDUSER
			return tx.Update(&commiter)
		} else {
			return nil
		}
	})

	return newUid, err
}

func RemoveUser(commiter uid_t, fuckedUsername string) error {
	fuckedUser, err := UsernameToInfo(fuckedUsername)
	if err != nil {
		return err
	}

	if checkUserUpdatePermission(commiter, fuckedUser.Permissions) == false {
		return errors.New("Permission denied.")
	}

	return db.Delete(&UserInfo{Id: fuckedUser.Id})
}

func AddPlan(commiter uid_t, planName string, planPriceStr string) (planid_t, error) {
	if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
		return -1, errors.New("Permission denied")
	}

	planPrice, err0 := StringToMoneyT(planPriceStr)
	if err0 != nil {
		return -1, err0
	}

	p := PlanInfo{
		Name:  planName,
		Price: planPrice,
	}

	err := db.Insert(&p)
	if err != nil {
		return -1, err
	}

	return p.Id, nil
}

func RemovePlan(commiter uid_t, fuckedPlanname string) error {
	fucked, err := PlannameToInfo(fuckedPlanname)
	if err != nil {
		return err
	}

	if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
		return errors.New("Permission denied.")
	}

	var userUsingThisPlan []UserInfo
	err = db.Model(&userUsingThisPlan).Where("plan = " + strconv.FormatInt(int64(fucked.Id), 10)).Select()
	if err != nil && err.Error() != PG_NOT_FOUND_ERR {
		return err
	}

	if len(userUsingThisPlan) > 0 {
		return errors.New("The plan is still in use by some user: " + userUsingThisPlan[0].Name)
	}

	return db.Delete(&PlanInfo{Id: fucked.Id})
}

func UpdateUserPlan(commiter uid_t, fuckedUsername string, planName string) error {
	if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
		return errors.New("Permission denied.")
	}

	u, err := UsernameToInfo(fuckedUsername)
	if err != nil {
		return err
	}

	if CheckPermission(u.Id, PERM_CUSTOMER) == false {
		return errors.New("Only customer can have a plan.")
	}

	newPlan, err2 := PlannameToInfo(planName)
	if err2 != nil {
		return err2
	}

	u.Plan = newPlan.Id

	return db.Update(&u)
}

func UpdateUserBalance(commiter uid_t, customerUsername string, balanceChangeStr string) error {
	if CheckPermission(commiter, PERM_CASHIER) == false {
		return errors.New("Permission denied.")
	}

	balanceChange, err0 := StringToMoneyT(balanceChangeStr)
	if err0 != nil {
		return err0
	}

	u, err := UsernameToInfo(customerUsername)
	if err != nil {
		return err
	}

	if CheckPermission(u.Id, PERM_CUSTOMER) == false {
		return errors.New("Only customer can be updated balance.")
	}

	// Pull commiter and customer info.

	cashier := UserInfo{
		Id: commiter,
	}
	err1 := db.Select(&cashier)
	if err1 != nil {
		return err1
	}

	// Prepare event
	event := UserBalanceEvent{
		UId: u.Id,
		What: fmt.Sprintf("balance_update %s from %s to %s by %d",
			balanceChange.String(), u.Balance.String(), (u.Balance + balanceChange).String(), commiter),
	}

	u.Balance += balanceChange
	if balanceChange > 0 {
		// cashier receive money and charge user.
		cashier.Achievements += balanceChange
	}

	err2 := db.RunInTransaction(func(tx *pg.Tx) error {
		err := tx.Update(&u)
		if err != nil {
			return err
		}

		err2 := tx.Update(&cashier)
		if err2 != nil {
			return err
		}

		return tx.Insert(&event)
	})

	return err2
}

func QueryUserInfo(commiter uid_t, usernameToQuery string) (string, error) {
	u, err := UsernameToInfo(usernameToQuery)
	if err != nil {
		return "", err
	}

	if u.Id != commiter {
		if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
			return "", errors.New("Permission denied.")
		}
	}

	p := PlanInfo{Id: u.Plan}
	err2 := db.Select(&p)
	if u.Plan != 0 && err2 != nil {
		return "", err2
	}

	return fmt.Sprintf("name=%s&permission=%s&balance=%s&achi=%s&plan_name=%s&plan_price=%s",
		u.Name, strings.Join(u.Permissions, ","), u.Balance.String(), u.Achievements.String(),
		p.Name, p.Price.String()), nil
}

func QueryBalanceLog(commiter uid_t, usernameToQuery string) (string, error) {
	u, err := UsernameToInfo(usernameToQuery)
	if err != nil {
		return "", err
	}

	if u.Id != commiter {
		if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
			return "", errors.New("Permission denied.")
		}
	}

	var events []UserBalanceEvent
	err2 := db.Model(&events).Where(fmt.Sprintf("u_id = %d", u.Id)).Select()
	if err2 != nil {
		if err2.Error() == PG_NOT_FOUND_ERR {
			return "events=", nil
		} else {
			return "", err2
		}
	}

	eventStrs := make([]string, len(events))
	for index, event := range events {
		eventStrs[index] = event.What
	}

	return "events=" + strings.Join(eventStrs, "\n"), nil
}

func ResetDatabase(commiter uid_t, newRootPassword string) error {
	if CheckPermission(commiter, PERM_ADMIN) == false {
		return errors.New("Permission denied.")
	}

	err := db.RunInTransaction(func(tx *pg.Tx) error {
		for _, model := range []interface{}{&UserInfo{}, &UserBalanceEvent{}, &PlanInfo{}} {
			err := tx.DropTable(model, &orm.DropTableOptions{
				IfExists: true,
				Cascade:  true,
			})
			if err != nil {
				return err
			}
		}

		for _, model := range []interface{}{&UserInfo{}, &UserBalanceEvent{}, &PlanInfo{}} {
			err := tx.CreateTable(model, &orm.CreateTableOptions{
				IfNotExists: true,
			})
			if err != nil {
				return err
			}
		}

		u := UserInfo{
			Name:        "root",
			Permissions: RolesPermission[ROLE_ADMIN],
			Password:    newRootPassword,
		}
		err3 := tx.Insert(&u)
		if err3 != nil {
			return err3
		}
		if u.Id != ROOT_UID {
			return errors.New("ROOT UID is incorrect. Failed to clear db.")
		}
		return nil
	})

	return err
}

func ListAllUserInfo(commiter uid_t) (string, error) {
	if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
		return "", errors.New("Permission denied.")
	}

	var users []UserInfo
	err := db.Model(&users).Select()
	if err != nil {
		return "", err
	}

	result := ""

	for _, u := range users {
		p := PlanInfo{Id: u.Plan}
		err2 := db.Select(&p)
		if u.Plan != 0 && err2 != nil {
			return "", err2
		}

		result += fmt.Sprintf("name=%s&permission=%s&balance=%s&achi=%s&plan_name=%s&plan_price=%s",
			u.Name, strings.Join(u.Permissions, ","), u.Balance.String(), u.Achievements.String(),
			p.Name, p.Price.String())
		result += "\n"
	}
	return result, nil
}

func ListAllPlanInfo(commiter uid_t) (string, error) {
	if CheckPermission(commiter, PERM_CUSTOMER_SERV) == false {
		return "", errors.New("Permission denied.")
	}

	var plans []PlanInfo
	err := db.Model(&plans).Select()
	if err != nil {
		return "", err
	}

	result := ""

	for _, p := range plans {
		result += fmt.Sprintf("plan_name=%s&plan_price=%s",
			p.Name, p.Price.String())
		result += "\n"
	}
	return result, nil
}
