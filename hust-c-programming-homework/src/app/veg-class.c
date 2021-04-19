#include "veg-class.h"
#include "list.h"
#include "fmtio.h"
#include <fcntl.h>
#include <unistd.h>

#define FILE_PATH DATA_DUMP_PATH_HEAD "vcls"

/*
 * Warning: This source SHOULD NEVER be adapted to industry environment,
 * as code quality is TOO BAD TO USE.
 * ONLY designed for HUST C homework usage.
 *
 * Recolic Keghart
 */

/* Usage tip.
 *   for (myListIterator it = goodsList->first; it != NULL; it=it->next)
     {
         Goods good = *(Goods*)(it->data);
         do something...
     }
 */
rList vcbuf;

void veg_class_dump()
{
    fd cfgFile = open(FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(cfgFile == -1) die("open file %s for write failed.", FILE_PATH);
    if(fmt_write_file(cfgFile, vcbuf, sizeof(veg_class), nullptr) < 0) die("fmt_write_file failed.");
    close(cfgFile);
}
void veg_class_destructor()
{
    veg_class_dump();
    rList_destructor(vcbuf);
}
void ___vc_exitfunc(int ___ar, void *___ar2) {veg_class_destructor();}
void veg_class_constructor()
{
    vcbuf = rList_newlist();
    fd cfgFile = open(FILE_PATH, O_RDONLY);
    if(errno == 2) goto file_not_exist;
    if(cfgFile == -1) die("open file %s for read failed.", FILE_PATH);
    if(fmt_read_file(cfgFile, vcbuf, sizeof(veg_class), nullptr) < 0) die("fmt_read_file failed.");
    close(cfgFile);
file_not_exist:
    on_exit(___vc_exitfunc, nullptr);
}
void veg_class_set(veg_class to_push)
{
    veg_class *toReplace = nullptr; RECORD
    for(rListIterator it = vcbuf->first; it != nullptr; it = it -> next)
    {RECORD
        veg_class *p = (veg_class *) it->data;RECORD
        if(p->code == to_push.code)
            toReplace = p;
    }RECORD
    if(toReplace)
        *toReplace = to_push;
    else
        rList_push_back(vcbuf, &to_push, sizeof(to_push));RECORD
}
void veg_class_ls(fd fout)
{RECORD
    for(rListIterator it = vcbuf->first; it != nullptr; it = it -> next)
    {RECORD
        veg_class *p = (veg_class *)it->data;RECORD
        dprintf(fout, "%d|%s\n", p->code, p->name);RECORD
    }RECORD
}
bool veg_class_rm(int code)
{
    for(rListIterator it = vcbuf->first; it != nullptr; it = it -> next)
    {
        veg_class *p = (veg_class *)it->data;
        if(p->code == code)
        {
            rList_eraseElem(vcbuf, it);
            return true;
        }
    }
    return false;
}

const veg_class *code_to_veg_class(int code)
{
    for(rListIterator it = vcbuf->first; it != nullptr; it = it -> next)
    {
        veg_class *p = (veg_class *)it->data;
        if(p->code == code)
            return p;
    }
    return nullptr;
}