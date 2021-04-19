#include "shit-op.h"
#include "list.h"
#include "data.h"
#include "console.h"
#include "cclib/containers.h" //http://www.cs.virginia.edu/~lcc-win32/ccl/ccl.html

#include "libut/uthash.h" //http://troydhanson.github.io/uthash/userguide.html

#include <unistd.h>
#include <stdio.h>

/*
 * Warning: This source SHOULD NEVER be adapted to ANY environment,
 * as code quality is TOO BAD TO USE.
 * ONLY designed for HUST C homework usage.
 *
 * Recolic Keghart
 */

extern rList jbuf; //constructed.

typedef struct ___to_print_1
{
    int classCode; //K
    char className[64];
    int sumArea;
    float sumWeight;
    UT_hash_handle hh;         /* makes this structure hashable */
} infa;
typedef infa * HashTable_infa;
void _impl_job_report_by_veg_class(fd fout) //#print className+sumArea+sumWeight
{
    HashTable_infa buf = NULL;
    //HashTable *buf = iHashTable.Create(sizeof(infa));

    for(rListIterator it = jbuf->first; it != nullptr; it = it->next)
    {
        job_info *p = (job_info *)it->data;
        infa dat;
        dat.classCode = p->pveg->pclass->code;
        strcpy(dat.className, p->pveg->pclass->name);
        dat.sumArea = p->area;
        dat.sumWeight = p->weight;

        infa *ele;
        HASH_FIND_INT(buf, &dat.classCode, ele);
        //infa *ele = iHashTable.GetElement(buf, &dat.classCode, sizeof(int));
        if(ele == nullptr)
        {
            infa *toadd = malloc(sizeof(infa));
            memcpy(toadd, &dat, sizeof(infa));
            HASH_ADD_INT(buf, classCode, toadd);
            //iHashTable.Add(buf, &dat.classCode, sizeof(int), &dat);
        }
        else
        {
            ele->sumArea += dat.sumArea;
            ele->sumWeight += dat.sumWeight;
        }
    }
    /*
    Iterator * it = iHashTable.NewIterator(buf);
    infa *dat;
    for(dat = it->GetFirst(it); dat != nullptr; dat = it->GetNext(it))
    {
        if(dprintf(fout, "%s|%d|%f\n", dat->className, dat->sumArea, dat->sumWeight) < 0)
            die("dprintf failed.");
    }
    iHashTable.DeleteIterator(it);*/
    infa *current, *tmp;
    HASH_ITER(hh, buf, current, tmp)
    {
        if(dprintf(fout, "%s|%d|%f\n", current->className, current->sumArea, current->sumWeight) < 0)
            die("dprintf failed.");
    }
    HASH_CLEAR(hh, buf);
    return;
}

typedef struct ___to_print_2
{
    const veg_info *pveg;
    int sumArea;
    float sumWeight;
    UT_hash_handle hh;         /* makes this structure hashable */
} infb;
typedef infb * HashTable_infb;
void ___filter_sort(fd fin, fd fout)
{
    doCmd(fin, fout, FD_DEFAULT, "sort --field-separator='|' -k4");
    return;
}
void ___impl_job_report_by_year_and_veg_name(fd fout, int year_begin, int year_end/*Not included*/) //#print vegName+className+sumArea+sumWeight(decrease)
{
    HashTable_infb buf = NULL;
    //HashTable *buf = iHashTable.Create(sizeof(infb));
    for(rListIterator it = jbuf->first; it != nullptr; it = it->next)
    {
        job_info *p = (job_info *)it->data;
        if(p->year < year_begin || p->year >= year_end)
            continue;
        infb dat;
        dat.pveg = p->pveg;
        dat.sumArea = p->area;
        dat.sumWeight = p->weight;

        infb *ele;
        HASH_FIND_INT(buf, &dat.pveg->no, ele);
        //infb *ele = iHashTable.GetElement(buf, &dat.pveg->no, sizeof(int));
        if(ele == nullptr)
        {
            infb *toadd = malloc(sizeof(infb));
            memcpy(toadd, &dat, sizeof(infb));
            HASH_ADD_INT(buf, pveg->no, toadd);
        }
            //iHashTable.Add(buf, &dat.pveg->no, sizeof(int), &dat);
        else
        {
            ele->sumArea += dat.sumArea;
            ele->sumWeight += dat.sumWeight;
        }
    }
    /*
    Iterator * it = iHashTable.NewIterator(buf);
    infb *dat;
    for(dat = it->GetFirst(it); dat != nullptr; dat = it->GetNext(it))
    {
        if(dprintf(fout, "%s|%s|%d|%f\n", dat->pveg->name, dat->pveg->pclass->name, dat->sumArea, dat->sumWeight) < 0)
            die("dprintf failed.");
    }
    iHashTable.DeleteIterator(it);*/
    infb *current, *tmp;
    HASH_ITER(hh, buf, current, tmp)
    {
        if(dprintf(fout, "%s|%s|%d|%f\n", current->pveg->name, current->pveg->pclass->name, current->sumArea, current->sumWeight) < 0)
            die("dprintf failed.");
    }
    HASH_CLEAR(hh, buf);
    return;
}
void _impl_job_report_by_year_and_veg_name_decrease(fd fout, int year_begin, int year_end/*Not included*/)
{
    fd pipefd[2];
    if(pipe(pipefd) == -1) die("pipe failed");
    ___impl_job_report_by_year_and_veg_name(pipefd[1], year_begin, year_end);
    close(pipefd[1]);
    ___filter_sort(pipefd[0], 1);
    close(pipefd[0]);
    return;
}


void _impl_check_weight_by_veg_class(fd fout, int classNum) //#print sumWeight
{
    float sumWeight = 0;
    for(rListIterator it = jbuf->first; it != nullptr; it = it->next)
    {
        job_info *p = it->data;
        if(p->pveg->pclass->code == classNum)
            sumWeight += p->weight;
    }
    if(dprintf(fout, "%f\n", sumWeight) < 0)
        die("dprintf failed.");
    return;
}

