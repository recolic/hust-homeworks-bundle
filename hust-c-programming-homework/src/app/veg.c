#include "veg.h"
#include "veg-class.h"
#include "list.h"
#include "fmtio.h"
#include <fcntl.h>
#include <unistd.h>

#define FILE_PATH DATA_DUMP_PATH_HEAD "vinf"
#define streql(sa, sb) (strlen(sa) == strlen(sb) && strcmp(sa, sb) == 0)

/*
 * Warning: This source SHOULD NEVER be adapted to industry environment,
 * as code quality is TOO BAD TO USE.
 * ONLY designed for HUST C homework usage.
 *
 * Recolic Keghart
 */

rList vibuf;

void veg_info_dump()
{
    fd cfgFile = open(FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(cfgFile == -1) die("open file %s for write failed.", FILE_PATH);
    rList_for_each(it, vibuf)
    { //trick for dump
        veg_info *p = it->data;
        p->pclass = (const veg_class *)p->pclass->code;
    }
    if(fmt_write_file(cfgFile, vibuf, sizeof(veg_info), nullptr) < 0) die("fmt_write_file failed.");
    close(cfgFile);
}
void veg_info_destructor()
{
    veg_info_dump();
    rList_destructor(vibuf);
}
void ___v_exitfunc(int ___ar, void *___ar2) {veg_info_destructor();}
void veg_info_constructor()
{
    vibuf = rList_newlist();
    fd cfgFile = open(FILE_PATH, O_RDONLY);
    if(errno == 2) goto file_not_exist;
    if(cfgFile == -1) die("open file %s for read failed.", FILE_PATH);
    if(fmt_read_file(cfgFile, vibuf, sizeof(veg_info), nullptr) < 0) die("fmt_read_file failed.");
    close(cfgFile);
    rList_for_each(it, vibuf)
    {
        veg_info *p = it->data;
        p->pclass = code_to_veg_class((int)p->pclass);
        if(p->pclass == nullptr) die("pveg_class not found. data boom.");
    }
file_not_exist:
    on_exit(___v_exitfunc, nullptr);
}

void veg_info_set(veg_info to_push)
{
    veg_info *toReplace = nullptr;
    for(rListIterator it = vibuf->first; it != nullptr; it = it -> next)
    {
        veg_info *p = (veg_info *) it->data;
        if(streql(to_push.name, p->name))
            toReplace = p;
    }
    if(toReplace)
    {
        to_push.no = toReplace->no;
        *toReplace = to_push;
    }
    else
    {
        to_push.no = vibuf->first == nullptr ? 1 : ((veg_info *)vibuf->last->data)->no + 1;
        rList_push_back(vibuf, &to_push, sizeof(to_push));
    }
}
void veg_info_ls(fd fout)
{
    for(rListIterator it = vibuf->first; it != nullptr; it = it->next)
    {
        veg_info *p = (veg_info *)it->data;RECORD
        dprintf(fout, "%d|%s|%d|%s\n", p->no, p->name, p->pclass->code, p->nutr_info);RECORD
    }
}
bool veg_info_rm(const char *name)
{
    for(rListIterator it = vibuf->first; it != nullptr; it = it -> next)
    {
        veg_info *p = (veg_info *)it->data;
        if(streql(name, p->name))
        {
            rList_eraseElem(vibuf, it);
            return true;
        }
    }
    return false;
}

const veg_info *no_to_veg_info(int no)
{
    for(rListIterator it = vibuf->first; it != nullptr; it = it -> next)
    {
        veg_info *p = (veg_info *)it->data;
        if(p->no == no)
            return p;
    }
    return nullptr;
}