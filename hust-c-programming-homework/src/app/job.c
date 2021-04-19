#include "job.h"
#include "list.h"
#include "veg.h"
#include "fmtio.h"
#include <fcntl.h>
#include <unistd.h>

#define FILE_PATH DATA_DUMP_PATH_HEAD "jinf"
#define streql(sa, sb) (strlen(sa) == strlen(sb) && strcmp(sa, sb) == 0)

/*
 * Warning: This source SHOULD NEVER be adapted to industry environment,
 * as code quality is TOO BAD TO USE.
 * ONLY designed for HUST C homework usage.
 *
 * Recolic Keghart
 */

rList jbuf;

void job_dump()
{
    fd cfgFile = open(FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(cfgFile == -1) die("open file %s for write failed.", FILE_PATH);
    rList_for_each(it, jbuf)
    { //trick for dump
        job_info *p = it->data;
        p->pveg = (const veg_info *)p->pveg->no;
    }
    if(fmt_write_file(cfgFile, jbuf, sizeof(job_info), nullptr) < 0) die("fmt_write_file failed.");
    close(cfgFile);
}
void job_destructor()
{
    job_dump();
    rList_destructor(jbuf);
}
void ___j_exitfunc(int ___ar, void *___ar2) {job_destructor();}
void job_constructor()
{
    jbuf = rList_newlist();
    fd cfgFile = open(FILE_PATH, O_RDONLY);
    if(errno == 2) goto file_not_exist;
    if(cfgFile == -1) die("open file %s for read failed.", FILE_PATH);
    if(fmt_read_file(cfgFile, jbuf, sizeof(job_info), nullptr) < 0) die("fmt_read_file failed.");
    close(cfgFile);
    rList_for_each(it, jbuf)
    {
        job_info *p = it->data;
        debug printf(">%d", (int)p->pveg);
        p->pveg = no_to_veg_info((int)p->pveg);
        if(p->pveg == nullptr) die("pveg_info not found. data boom.");
    }
file_not_exist:
    on_exit(___j_exitfunc, nullptr);
}

void job_set(job_info to_push)
{
    job_info *toReplace = nullptr;
    for(rListIterator it = jbuf->first; it != nullptr; it = it -> next)
    {
        job_info *p = (job_info *) it->data;
        if(to_push.no == p->no)
            toReplace = p;
    }
    if(toReplace)
        *toReplace = to_push;
    else
        rList_push_back(jbuf, &to_push, sizeof(to_push));
}
void job_ls(fd fout)
{RECORD
    for(rListIterator it = jbuf->first; it != nullptr; it = it -> next)
    {RECORD
        job_info *p = (job_info *)it->data;RECORD
        debug printf("%d", p->pveg->no);
        RECORD
        dprintf(fout, "%d|%d|%s|%d|%f|%d\n", p->no, p->pveg->no, p->pveg->name, p->area, p->weight, p->year);
    }RECORD
}
bool job_rm(int no)
{
    for(rListIterator it = jbuf->first; it != nullptr; it = it -> next)
    {
        job_info *p = (job_info *)it->data;
        if(p->no == no)
        {
            rList_eraseElem(jbuf, it);
            return true;
        }
    }
    return false;
}
