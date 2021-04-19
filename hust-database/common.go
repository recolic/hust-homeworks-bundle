package main

import (
	"errors"
	"fmt"
	"github.com/go-pg/pg"
	"regexp"
	"strconv"
	"strings"
)

const (
	PERM_ADMIN         = "root"
	PERM_CASHIER       = "cashier"
	PERM_CUSTOMER_SERV = "customer_service"
	PERM_CUSTOMER      = "customer"
	PERM_PUBLIC        = "public"

	ROLE_ADMIN         = "root"
	ROLE_CASHIER       = "cashier"
	ROLE_CUSTOMER      = "customer"
	ROLE_CUSTOMER_SERV = "customer_service"
)

const PasswordSalt = "rsalt"
const ROOT_UID = 1
const PG_NOT_FOUND_ERR = "pg: no rows in result set"
const EARNING_PER_ADDUSER = 1000 // Earn 10 dollar for every new customer

var RolesPermission map[string][]string
var UsernameRegex = regexp.MustCompile(`^[A-Za-z0-9_, @.:;-]*$`)
var MoneyStrRegex = regexp.MustCompile(`^[0-9]+\.[0-9][0-9]$`)

func InitCommon() {
	RolesPermission = map[string][]string{
		"root":     {PERM_ADMIN, PERM_CASHIER, PERM_CUSTOMER_SERV, PERM_CUSTOMER, PERM_PUBLIC},
		"cash":     {PERM_CASHIER, PERM_PUBLIC},
		"serv":     {PERM_CUSTOMER_SERV, PERM_PUBLIC},
		"customer": {PERM_CUSTOMER, PERM_PUBLIC},
	}
}

// common data structure

type uid_t int64
type money_t int64
type planid_t int64

func (m money_t) String() string {
	symbol := ""
	high := "0"
	var low string
	abs := m
	if abs < 0 {
		abs = -abs
		symbol = "-"
	}
	if abs < 10 {
		low = "0" + strconv.Itoa(int(abs))
	} else if abs < 100 {
		low = strconv.Itoa(int(abs))
	} else {
		low = strconv.Itoa(int(abs % 100))
	}

	high = strconv.FormatInt(int64(abs)/100, 10)

	return fmt.Sprintf("%s%s.%s", symbol, high, low)
}
func StringToMoneyT(s string) (money_t, error) {
	dotIndex := strings.Index(s, ".")
	strWithoutDot := ""
	s += "00"
	if dotIndex == -1 {
		strWithoutDot = s
	} else {
		strWithoutDot = s[:dotIndex] + s[dotIndex+1:dotIndex+3]
	}
	m, err := strconv.ParseInt(strWithoutDot, 10, 64)
	if err != nil {
		return 0, err
	} else {
		return money_t(m), nil
	}
}

type UserInfo struct {
	Id           uid_t  `sql:",pk,unique"`
	Name         string `sql:",unique"`
	Password     string
	Permissions  []string `sql:",array"`
	Balance      money_t  // `10.32` is saved as `1032`
	Achievements money_t
	Plan         planid_t `sql:",notnull"`
	Email        string   `sql:",unique"`
}

func (u UserInfo) String() string {
	return fmt.Sprintf("UserInfo<%d %s %s BAL=%d ACHI=%d>", u.Id, u.Name, strings.Join(u.Permissions, ","), u.Balance, u.Achievements)
}

type UserBalanceEvent struct {
	EventId uid_t `sql:",pk,unique"`
	UId     uid_t
	What    string // should not contain `;`
}

func (u UserBalanceEvent) String() string {
	return fmt.Sprintf("UserBalanceEvent<%d %d %s>", u.EventId, u.UId, u.What)
}

type PlanInfo struct {
	Id    planid_t `sql:",pk,unique"`
	Name  string   `sql:",unique"`
	Price money_t
}

func (p PlanInfo) String() string {
	return fmt.Sprintf("PlanInfo<%d %s %d>", p.Id, p.Name, p.Price)
}

// database

var db *pg.DB

// other common functions
func ArrayContains(arr []string, item string) bool {
	for _, ele := range arr {
		if ele == item {
			return true
		}
	}
	return false
}

func CheckPermission(commiter uid_t, perm string) bool {
	commiterInfo := UserInfo{
		Id: commiter,
	}
	err := db.Select(&commiterInfo)
	if err != nil {
		return false
	}

	if !ArrayContains(commiterInfo.Permissions, perm) {
		return false
	}
	return true
}

func UsernameToInfo(name string) (UserInfo, error) {
	if !UsernameRegex.MatchString(name) {
		return UserInfo{}, errors.New("Invalid username format.")
	}
	u := UserInfo{}
	err := db.Model(&u).Where(fmt.Sprintf("name = '%s'", name)).Select()
	if err != nil && err.Error() == PG_NOT_FOUND_ERR {
		return u, errors.New("Name not found: " + name)
	}
	return u, err
}
func PlannameToInfo(name string) (PlanInfo, error) {
	if !UsernameRegex.MatchString(name) {
		return PlanInfo{}, errors.New("Invalid planname format.")
	}
	u := PlanInfo{}
	err := db.Model(&u).Where(fmt.Sprintf("name = '%s'", name)).Select()
	if err != nil && err.Error() == PG_NOT_FOUND_ERR {
		return u, errors.New("Name not found: " + name)
	}
	return u, err
}
