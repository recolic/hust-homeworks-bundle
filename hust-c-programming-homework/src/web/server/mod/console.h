#ifndef _SRC_CONSOLE_H
#define _SRC_CONSOLE_H 1

typedef int fd;

extern const fd FD_DEFAULT;
int doCmd(fd _stdin, fd _stdout, fd _stderr, const char *cmd);
int doCmd_pure(const char *cmd);
// pass FD_DEFAULT to leave fd as default.

#endif //_SRC_CONSOLE_H
