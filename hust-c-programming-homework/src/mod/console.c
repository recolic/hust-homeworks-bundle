#include "console.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

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
    if(ret > 63) die("Memory violate: sprintf prints too many chars(%s)", ins);RECORD
    //return execl("/bin/bash", "/bin/bash", "-c", cmd, (char *)nullptr);
    return system(cmd);
}

int doCmd(fd _stdin, fd _stdout, fd _stderr, const char *cmd)
{
    if(_stdin == FD_DEFAULT) _stdin = 0;
    if(_stdout == FD_DEFAULT) _stdout = 1;
    if(_stderr == FD_DEFAULT) _stderr = 2;RECORD
    auto cmdlen = strlen(cmd); //Warning: potential DOS.
    auto newcmd = (char *)calloc((cmdlen + 64), sizeof(char));RECORD
    strcpy(newcmd, cmd);RECORD
    auto ret = _doCmd(_stdin, _stdout, _stderr, newcmd, cmdlen);RECORD
    free(newcmd);RECORD
    return ret;RECORD
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
