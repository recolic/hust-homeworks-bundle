#ifndef CMDER_H
#define CMDER_H

#ifndef CMD_INCLUDE_ONCE_CONFIRMER
#error Include unsafe header need confirm.
#endif
#include <QString>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <exception>
#include <stdexcept>

using fd=int;
const fd FD_DEFAULT = -1;

#ifdef stdin
#undef stdin
#endif
#ifdef stdout
#undef stdout
#endif
#ifdef stderr
#undef stderr
#endif
//NO INCLUDE BELOW --------------------------

#include <string>
//#include <rlib/string/string.hpp>
using namespace std;

void do_execv(const string &cmd, fd out)
{
    string toexe = cmd;
    toexe += " > /dev/fd/" + to_string(out) + " 2>&1";
    system(toexe.c_str());
    return;
}

string run(string cmd)
{
    fd pfd[2];
    if(-1 == pipe(pfd)) throw runtime_error("pipe fail.");
    do_execv(cmd, pfd[1]);
    close(pfd[1]);

    string result;
    size_t curr = 1024;
    char *dat = (char *)malloc(curr);
    while(true)
    {
        auto ret = read(pfd[0], dat, curr - 1);
        if(ret == -1) throw runtime_error("read from fd failed.");
        dat[ret] = '\0';
        result += dat;
        if(ret + 1 < curr)
            break;
    }
    return move(result);
}


class cmder{
public:
    QString operator()(const QString &cmd)
    {
        if( access( "./chw-cli", R_OK | X_OK ) == -1 )
        { //File not exist
            return std::move(QString("Exception at caller: ./chw-cli not exist or not readable or not xable."));
        }
        QString ret = QString::fromStdString(run(cmd.toStdString()));
        return std::move(ret);
    }
};


#endif // CMDER_H
