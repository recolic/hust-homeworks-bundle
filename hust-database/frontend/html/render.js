
// string format
if (!String.prototype.format) {
  String.prototype.format = function() {
    var args = arguments;
    return this.replace(/{(\d+)}/g, function(match, number) { 
      return typeof args[number] != 'undefined'
        ? args[number]
        : match
      ;
    });
  };
}

function setCookie(name,value,days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days*24*60*60*1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + (value || "")  + expires + "; path=/";
}
function getCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}
function eraseCookie(name) {   
    document.cookie = name+'=; Max-Age=-99999999;';  
}
function httpGetSync(theUrl)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
    xmlHttp.send( null );
    return xmlHttp.responseText;
}
function httpGetAsync(theUrl)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, true ); // false for synchronous request
    xmlHttp.send( null );
}
function httpGetAsyncCallback(theUrl, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.send(null);
}

///// libs done

function generateTabs(nameUrlMap) {
    let res = "";
    Object.keys(nameUrlMap).forEach(key => {
        res += '<a class="navbar-item" href="{0}">{1}</a>'.format(nameUrlMap[key], key);
    });
    return res;
}

function renderTabs(elementId) {
    if(webFileName == "home.html" || webFileName == "login.html") {
        document.getElementById("topbar-contents").innerHTML = generateTabs({
            "home": "/home.html",
            "login": "/login.html",
        });
    }
    else {
        let u = httpGetSync('/api/QueryUserInfo?name=' + getCookie("name"));
        if(!u.startsWith('name')) {
            if(webFileName == "changePassword.html") {
                // changing password. do not kick out.
                return;
            }
            window.location.href = "/login.html";
        }
        let perms = u.split("&")[1].split("=")[1].split(",");
        let tabsMap = {};
        tabsMap["Me"] = "/me.html";
        tabsMap["ChangePassword"] = "/changePassword.html";
        perms.forEach(perm => {
            if(perm == "root") {
                tabsMap["ResetDatabase"] = "/resetDatabase.html";
                tabsMap["User"] = "/users.html"; // root user can add/remove all users
            }
            else if(perm == "customer_service") {
                tabsMap["Plan"] = "/plans.html"; // may add/view plan
                tabsMap["User"] = "/users.html"; // may set user's plan, see user's info
            }
            else if(perm == "cashier") {
                tabsMap["AddCredit"] = "/addCredit.html"; // may charge customer
            }
            else if(perm == "customer") {
                tabsMap["MyTransactions"] = "/history.html"; // balance log
            }
        });
        document.getElementById("topbar-contents").innerHTML = generateTabs(tabsMap);
        logoutHTML = '<a class="navbar-item" href="/home.html" onclick="httpGetSync(\'/api/Logout\');">Logout</a>';
        document.getElementById("topbar-right-contents").innerHTML = logoutHTML;
    }

}
