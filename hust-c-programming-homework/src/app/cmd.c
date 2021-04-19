#include "cmd.h"
#include "data.h"
#include "veg-class.h"
#include "veg.h"
#include "job.h"
#include "filter.h"
#include "shit-op.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void usage(const char *exeName)
{
    if(exeName == NULL)
        exeName = "./thisBin";
    #if defined nl || defined exe
    #error __FILE__:__LINE__ alias conflict. Please repair.
    #endif
    #define nl "\n"
    #define exe ,exeName);printf(
    printf(
        "Usage:" nl
        "%s <sub-command> <required arguments ...> [optional arguments ...]" exe nl nl
        "sub-commands:" nl
        "veg-class-set <classNum> <className>" nl
        "veg-class-ls [--code=...]" nl
        "veg-class-rm <classNum>" nl
        "veg-info-set <vegName> <classNum> <neuInfoStr>" nl
        "veg-info-ls [--name-keyword=...] [--neu-keyword=...] [--class-code=...]" nl
        "veg-info-rm <vegName>" nl
        "job-set <jobNum> <vegNum> <area> <weight> <year>" nl
        "job-ls [--veg-name-keyword=...] [--veg-name=...] [--year=...]" nl
        "job-rm <jobNum>" nl nl 
        //Shit below: Must be implemented by bash script.
        "job-report-by-veg-class #print className+sumArea+sumWeight" nl
        "job-report-by-year-and-veg-name <yearBegin> <yearEnd(NOT included)> #print vegName+className+sumArea+sumWeight(decrease)" nl
        "check-weight-by-veg-class <classNum> #print sumWeight" nl
        "Please use veg-info-ls to print veg info by neu keyword." nl nl
    );
    #undef exe
    #undef nl
    return;
}

#define streql(sa, sb) (strlen(sa) == strlen(sb) && strcmp(sa, sb) == 0)
#define strheadeql(___sa, ___sb) ({int ___la=strlen(___sa);int ___lb=strlen(___sb);!strncmp(___sa,___sb,min(___la,___lb));})
//Warning: NO alias unpack.
#define ifcmd(t) if(streql(subcmd, t))

void deal_veg_info_ls(size_t, char **);
void deal_job_ls(size_t, char **);
//TODO: finish deal_ls.

int do_cmd_process(size_t arglen, char **argv)
{
    if(arglen < 2)
    {
        usage(arglen == 1 ? argv[0] : NULL);
        return 1;
    }
    const char *binName = argv[0];
    const char *subcmd = argv[1];
#define BAD_ARGUMENT do {usage(binName); die("bad_argument");} while(0)
#define REQUIRE_ARGLEN(n) if(arglen < n) BAD_ARGUMENT;
    ifcmd("veg-class-set")
    {
        REQUIRE_ARGLEN(4)
        veg_class vc;
        vc.code = atoi(argv[2]);
        strncpy(vc.name, argv[3], 63);
        veg_class_set(vc);
    }
    else ifcmd("veg-class-ls")
    {
        REQUIRE_ARGLEN(2)
        if(arglen == 2)
            veg_class_ls(1);
        else
        { //dirty.
            if(strheadeql(argv[2], "--code="))
            {
                const char *codeArg = argv[2] + 7;
                fd pipefd[2];
                if(-1 == pipe(pipefd))
                    die("failed to init pipe.");
                veg_class_ls(pipefd[1]);
                close(pipefd[1]);
                filter(pipefd[0], 1, true, codeArg, VEG_CLASS_CODE);
                close(pipefd[0]);
            }
            else
                BAD_ARGUMENT;
        }
    }
    else ifcmd("veg-class-rm")
    {
        REQUIRE_ARGLEN(3)
        if(veg_class_rm(atoi(argv[2])) == false)
            printf("Failed to remove record. Confirm if it do exists.");
    }
    else ifcmd("veg-info-set")
    {
        REQUIRE_ARGLEN(5)
        veg_info vi;
        strncpy(vi.name, argv[2], 63);
        vi.pclass = code_to_veg_class(atoi(argv[3]));
        if(vi.pclass == nullptr) die("v_class not exist.");
        strncpy(vi.nutr_info, argv[4], 63);
        veg_info_set(vi);
    }
    else ifcmd("veg-info-ls")
    {RECORD
        REQUIRE_ARGLEN(2) RECORD
        deal_veg_info_ls(arglen, argv);
    }
    else ifcmd("veg-info-rm")
    {
        REQUIRE_ARGLEN(3)
        if(veg_info_rm(argv[2]) == false)
            printf("Failed to remove record. Confirm if it do exists.");
    }
    else ifcmd("job-set")
    {
        REQUIRE_ARGLEN(7)
        job_info ji;
        ji.no = atoi(argv[2]);
        ji.pveg = no_to_veg_info(atoi(argv[3]));
        if(ji.pveg == nullptr) die("v_info not exist.");
        ji.area = atoi(argv[4]);
        ji.weight = (float)atof(argv[5]);
        ji.year = atoi(argv[6]);
        job_set(ji);
    }
    else ifcmd("job-ls")
    {
        REQUIRE_ARGLEN(2)
        deal_job_ls(arglen, argv);
    }
    else ifcmd("job-rm")
    {
        REQUIRE_ARGLEN(3)
        if(job_rm(atoi(argv[2])) == false)
            printf("Failed to remove record. Confirm if it do exists.");
    }
    else ifcmd("job-report-by-veg-class")
    {
        REQUIRE_ARGLEN(2)
        _impl_job_report_by_veg_class(1);
    }
    else ifcmd("job-report-by-year-and-veg-name")
    {
        REQUIRE_ARGLEN(4)
        _impl_job_report_by_year_and_veg_name_decrease(1, atoi(argv[2]), atoi(argv[3]));
    }
    else ifcmd("check-weight-by-veg-class")
    {
        REQUIRE_ARGLEN(3)
        _impl_check_weight_by_veg_class(1, atoi(argv[2]));
    }
    else
        BAD_ARGUMENT;
    //TODO: some shit algo to impl
#undef REQUIRE_ARGLEN
    return 0;
}

/*
 *         "job-report-by-veg-class #print className+sumArea+sumWeight" nl
        "job-report-by-year-and-veg-name <yearBegin> <yearEnd(NOT included)> #print vegName+className+sumArea+sumWeight(decrease)" nl
        "check-weight-by-veg-class <classNum> #print sumWeight" nl
        "Please use veg-info-ls to print veg info by neu keyword." nl nl


        "veg-info-ls [--name-keyword=...] [--neu-keyword=...] [--class-code=...]" nl
        "job-ls [--veg-name-keyword=...] [--veg-name=...] [--year=...]" nl

        if(arglen == 2)
            veg_class_ls(1);
        else
        {
            if(strheadeql(argv[2], "--code="))
            {
                const char *codeArg = argv[2] + 7;
                fd pipefd[2];
                if(-1 == pipe(pipefd))
                    die("failed to init pipe.");
                veg_class_ls(pipefd[1]);
                filter(pipefd[0], 1, true, codeArg, VEG_CLASS_CODE);
            }
            else
                BAD_ARGUMENT;
        }
*/

void deal_veg_info_ls(size_t arglen, char **argv)
{RECORD
    debug printf("%d\n", (int)arglen);
    const char *binName = argv[0];
    fd pipefd[2];
    if(-1 == pipe(pipefd))
        die("failed to init pipe.");
    veg_info_ls(pipefd[1]);
    close(pipefd[1]);RECORD
    for(size_t cter = 2; cter < arglen; ++cter)
    {
        if(strheadeql(argv[cter], "--name-keyword="))
        {RECORD
            fd tmpPipe[2];
            if(-1 == pipe(tmpPipe))
                die("failed to init pipe.");
            filter(pipefd[0], tmpPipe[1], false, argv[cter] + 15, VEG_NAME);
            close(tmpPipe[1]);
            close(pipefd[0]);
            pipefd[0] = tmpPipe[0];
            continue;
        }
        if(strheadeql(argv[cter], "--neu-keyword="))
        {RECORD
            fd tmpPipe[2];RECORD
            if(-1 == pipe(tmpPipe))
                die("failed to init pipe.");
            filter(pipefd[0], tmpPipe[1], false, argv[cter] + 14, VEG_NEU);RECORD
            debug printf("tp0=%d, p0=%d\n", tmpPipe[0], pipefd[0]);RECORD
            close(tmpPipe[1]);
            close(pipefd[0]);
            pipefd[0] = tmpPipe[0];
            continue;
        }
        if(strheadeql(argv[cter], "--class-code="))
        {
            fd tmpPipe[2];
            if(-1 == pipe(tmpPipe))
                die("failed to init pipe.");
            filter(pipefd[0], tmpPipe[1], true, argv[cter] + 13, VEG_CLASS_CODE_BY_INFO);
            close(tmpPipe[1]);
            close(pipefd[0]);
            pipefd[0] = tmpPipe[0];
            continue;
        }
        BAD_ARGUMENT;
    }
    debug printf("p0=%d\n",pipefd[0]);
    printFd(pipefd[0]);
    close(pipefd[0]);
    return;
}
void deal_job_ls(size_t arglen, char **argv)
{RECORD
    const char *binName = argv[0];
    fd pipefd[2];
    if(-1 == pipe(pipefd))
        die("failed to init pipe.");
    job_ls(pipefd[1]);
    close(pipefd[1]);
    for(size_t cter = 2; cter < arglen; ++cter)
    {
        if(strheadeql(argv[cter], "--veg-name-keyword="))
        {
            fd tmpPipe[2];
            if(-1 == pipe(tmpPipe))
                die("failed to init pipe.");
            filter(pipefd[0], tmpPipe[1], false, argv[cter] + 19, VEG_NAME_BY_JOB);
            close(tmpPipe[1]);
            close(pipefd[0]);
            pipefd[0] = tmpPipe[0];
            continue;
        }
        if(strheadeql(argv[cter], "--veg-name="))
        {
            fd tmpPipe[2];
            if(-1 == pipe(tmpPipe))
                die("failed to init pipe.");
            filter(pipefd[0], tmpPipe[1], true, argv[cter] + 11, VEG_NAME_BY_JOB);
            close(tmpPipe[1]);
            close(pipefd[0]);
            pipefd[0] = tmpPipe[0];
            continue;
        }
        if(strheadeql(argv[cter], "--year="))
        {
            fd tmpPipe[2];
            if(-1 == pipe(tmpPipe))
                die("failed to init pipe.");
            filter(pipefd[0], tmpPipe[1], true, argv[cter] + 7, JOB_YEAR);
            close(tmpPipe[1]);
            close(pipefd[0]);
            pipefd[0] = tmpPipe[0];
            continue;
        }
        BAD_ARGUMENT;
    }
    printFd(pipefd[0]);
    close(pipefd[0]);
    return;
}


#undef BAD_ARGUMENT