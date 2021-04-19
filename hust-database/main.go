package main

import (
	"flag"
	"github.com/go-pg/pg"
	"github.com/go-pg/pg/orm"
	"github.com/gpmgo/gopm/modules/log"
	"net/http"
)

func tryCreateRootAccount(password string) {
	u := UserInfo{Id: ROOT_UID}
	err := db.Select(&u)

	if err != nil {
		if err.Error() == PG_NOT_FOUND_ERR {
			// root not existing
			// create root account
			u.Password = passwordSaltedHash(password, PasswordSalt)
			u.Name = "root"
			u.Permissions = RolesPermission[ROLE_ADMIN]
			u.Email = "root@recolic.net"
			err2 := db.Insert(&u)
			if err2 != nil {
				panic("Unable to insert root record. " + err2.Error())
			}
		} else {
			panic("Unable to select root record. " + err.Error())
		}
	}
}

func createTables() {
	for _, model := range []interface{}{&UserInfo{}, &UserBalanceEvent{}, &PlanInfo{}} {
		err := db.CreateTable(model, &orm.CreateTableOptions{
			IfNotExists: true,
		})

		if err != nil {
			panic("Unable to create table: " + err.Error())
		}
	}
}

func main() {
	initAuthModule()
	InitCommon()
	log.Verbose = true

	dbUsername := flag.String("user", "postgres", "Username for PostgreSQL.")
	dbAddr := flag.String("addr", "127.0.0.1:5432", "Address for PostgreSQL.")
	dbPswd := flag.String("password", "", "Password for PostgreSQL.")
	httpBindAddr := flag.String("listen", ":80", "Listen address for http server.")
	defaultRootPassword := flag.String("root-password", "P@ssw0rd", "For first-time launch, set this parameter to set root password.")

	flag.Parse()

	log.Info("Connecting PostgreSQL %s as %s...", *dbAddr, *dbUsername)
	db = pg.Connect(&pg.Options{
		User:     *dbUsername,
		Addr:     *dbAddr,
		Password: *dbPswd,
	})
	defer db.Close()

	// create table if not exist
	createTables()
	tryCreateRootAccount(*defaultRootPassword)

	log.Info("HTTP listening %s.", *httpBindAddr)
	http.HandleFunc("/", HttpApiFunc)
	err := http.ListenAndServe(*httpBindAddr, nil)

	if err != nil {
		panic(err.Error())
	}
}
