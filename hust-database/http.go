package main

import (
	"github.com/gpmgo/gopm/modules/log"
	"net/http"
	"net/url"
	"strconv"
	"strings"
	"time"
)

func HttpApiFunc(w http.ResponseWriter, r *http.Request) {
	status, response := httpApiFuncImpl(w, r)
	w.WriteHeader(status)
	_, _ = w.Write([]byte(response))
	return
}

func apiExistArgs(apiArgs url.Values, required ...string) (string, bool) {
	for _, arg := range required {
		if _, ok := apiArgs[arg]; !ok {
			return arg, false
		}
	}
	return "", true
}

func httpApiFuncImpl(w http.ResponseWriter, r *http.Request) (int, string) {
	uri := r.RequestURI
	apiMethod := strings.Split(uri, "?")[0][1:]
	apiArgs := r.URL.Query()

	log.Info("API %s", apiMethod)

	commiterUid := uid_t(-1)
	token := ""
	if apiMethod != "Login" && apiMethod != "ForgetPassword" && apiMethod != "ChangePassword" {
		// Login don't need token.
		if val, ok := apiArgs["token"]; ok {
			token = val[0]
		} else {
			for _, cookie := range r.Cookies() {
				if cookie.Name == "token" {
					token = cookie.Value
				}
			}
		}
		if token == "" {
			return 403, "Missing token."
		}

		uid, err := VerifyToken(token)
		if err != nil {
			return 403, "Invalid token. " + err.Error()
		}
		commiterUid = uid
	}

	switch apiMethod {
	case "Login":
		if lack, ok := apiExistArgs(apiArgs, "name", "password"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		token, err := DoLogin(apiArgs["name"][0], apiArgs["password"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			newCookie := http.Cookie{Name: "token", Value: token}
			http.SetCookie(w, &newCookie)
			return 200, "token=" + token
		}
	case "Logout":
		err := DoLogout(token)
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			newCookie := http.Cookie{Name: "token", Value: token, Expires: time.Now()}
			http.SetCookie(w, &newCookie)
			return 200, "status=ok"
		}
	case "AddUser":
		if lack, ok := apiExistArgs(apiArgs, "name", "password", "role", "email"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		uid, err := AddUser(commiterUid, apiArgs["name"][0], apiArgs["password"][0], apiArgs["role"][0], apiArgs["email"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "uid=" + strconv.FormatInt(int64(uid), 10)
		}
	case "RemoveUser":
		if lack, ok := apiExistArgs(apiArgs, "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := RemoveUser(commiterUid, apiArgs["name"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "status=ok"
		}
	case "AddPlan":
		if lack, ok := apiExistArgs(apiArgs, "plan_name", "price"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		planId, err := AddPlan(commiterUid, apiArgs["plan_name"][0], apiArgs["price"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "plan_id=" + strconv.FormatInt(int64(planId), 10)
		}
	case "RemovePlan":
		if lack, ok := apiExistArgs(apiArgs, "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := RemovePlan(commiterUid, apiArgs["name"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "status=ok"
		}

	case "UpdateUserPlan":
		if lack, ok := apiExistArgs(apiArgs, "plan_name", "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := UpdateUserPlan(commiterUid, apiArgs["name"][0], apiArgs["plan_name"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "status=ok"
		}
	case "UpdateUserBalance":
		if lack, ok := apiExistArgs(apiArgs, "delta", "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := UpdateUserBalance(commiterUid, apiArgs["name"][0], apiArgs["delta"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "status=ok"
		}
	case "QueryUserInfo":
		if lack, ok := apiExistArgs(apiArgs, "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		content, err := QueryUserInfo(commiterUid, apiArgs["name"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, content
		}
	case "QueryBalanceLog":
		if lack, ok := apiExistArgs(apiArgs, "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		content, err := QueryBalanceLog(commiterUid, apiArgs["name"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, content
		}
	case "ResetDatabase":
		if lack, ok := apiExistArgs(apiArgs, "new_root_password"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := ResetDatabase(commiterUid, apiArgs["new_root_password"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			_ = DoLogout(token)
			return 200, "status=ok"
		}
	case "ListAllUserInfo":
		content, err := ListAllUserInfo(commiterUid)
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, content
		}
	case "ListAllPlanInfo":
		content, err := ListAllPlanInfo(commiterUid)
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, content
		}
	case "ForgetPassword":
		if lack, ok := apiExistArgs(apiArgs, "email", "domain", "proto"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := ForgetPassword(apiArgs["email"][0], apiArgs["domain"][0], apiArgs["proto"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "status=ok"
		}
	case "ChangePassword":
		if lack, ok := apiExistArgs(apiArgs, "old", "new", "name"); !ok {
			return 400, "Required argument '" + lack + "' not defined."
		}
		err := ChangePassword(apiArgs["name"][0], apiArgs["old"][0], apiArgs["new"][0])
		if err != nil {
			return 500, "Server API error: " + err.Error()
		} else {
			return 200, "status=ok"
		}

	}

	return 404, "Method not found."
}
