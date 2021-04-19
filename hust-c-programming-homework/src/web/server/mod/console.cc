#include "console.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <exception>
#include <stdexcept>

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

int _doCmd(fd stdin, fd stdout, fd stderr, char *cmd, size_t cmdlen) //There must be 64 bytes pre-allocated after \0. (44 bytes at least.)
{
    char *ins = cmd + cmdlen;
    auto ret = sprintf(ins, " < /dev/fd/%d > /dev/fd/%d 2> /dev/fd/%d", stdin, stdout, stderr);
    if(ret > 63) throw std::runtime_error("Memory violate: sprintf prints too many chars");
    return execl("/bin/bash", "/bin/bash", "-c", cmd, (char *)nullptr);
}

int doCmd(fd _stdin, fd _stdout, fd _stderr, const char *cmd)
{
    if(_stdin == FD_DEFAULT) _stdin = 0;
    if(_stdout == FD_DEFAULT) _stdout = 1;
    if(_stderr == FD_DEFAULT) _stderr = 2;
    auto cmdlen = strlen(cmd); //Warning: potential DOS.
    auto newcmd = (char *)calloc((cmdlen + 64), sizeof(char));
    strcpy(newcmd, cmd);
    auto ret = _doCmd(_stdin, _stdout, _stderr, newcmd, cmdlen);
    free(newcmd);
    return ret;
}

int _doCmd_pure(char *cmd, size_t cmdlen) //There must be 64 bytes pre-allocated after \0. (44 bytes at least.)
{
    char *ins = cmd + cmdlen;
    return execl("/bin/bash", "/bin/bash", "-c", cmd, (char *)nullptr);
}

int doCmd_pure(const char *cmd)
{
    auto cmdlen = strlen(cmd); //Warning: potential DOS.
    auto newcmd = (char *)calloc((cmdlen + 64), sizeof(char));
    strcpy(newcmd, cmd);
    auto ret = _doCmd_pure(newcmd, cmdlen);
    free(newcmd);
    return ret;
}

#include <string>
//#include <rlib/string/string.hpp>
using namespace std;

void do_execv(const string &cmd, fd out)
{
    string toexe = "./chw-cli ";
    toexe += cmd;
    toexe += " > /dev/fd/" + to_string(out) + " 2>&1";
    system(toexe.c_str());
    return;
}

string run(string cmd)
{
    fd pfd[2];
    if(-1 == pipe(pfd)) throw runtime_error("pipe fail.");
//    rlib::replaceSubString(cmd, "[$space$]", "");
    do_execv(cmd, pfd[1]);
    //doCmd(FD_DEFAULT, pfd[1], pfd[1], (string("./chw-cli ") + cmd).c_str());
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
