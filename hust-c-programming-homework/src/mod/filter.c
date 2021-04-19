#include "filter.h"
#include "console.h"
#include <unistd.h>

/*
 * Warning: This source SHOULD NEVER be adapted to industry environment,
 * as implementation is error-prone.
 * ONLY designed for HUST C homework usage.
 * Consider Shell Script if necessary.
 *
 * Recolic Keghart
 */

int filterClassToIndex(FILTER_CLASS fc)
{
    switch(fc)
    {
        case VEG_CLASS_CODE:
            return 0;
        case VEG_NAME:
            return 1;
        case VEG_NEU:
            return 3;
        case VEG_CLASS_CODE_BY_INFO:
            return 2;
        case VEG_NAME_BY_JOB:
            return 2;
        case JOB_YEAR:
            return 5;
        default:
            die("Failed to assign index: fc=%d", (int)fc);
    }
}

//TODO: implement filter after data-ls op.
void filter(fd fin, fd fout, bool fullMatch, const char *keyString, FILTER_CLASS type)
{
    auto index = filterClassToIndex(type);
    auto keyLen = strlen(keyString);
    char *pattern = (char *)calloc(1034, sizeof(char));
    strcpy(pattern, "grep '^");
    if(index*6+keyLen+8 > 1023) die("keyString too long.");
    for(size_t cter = 0; cter < index; ++cter)
        memcpy(pattern + 6 * cter + 6, "[^|]*|", 6);
    if(fullMatch)
    {
        sprintf(pattern + 6 + 6 * index, "%s", keyString);
        sprintf(pattern + 6 + 6 * index + keyLen, "|'");
    }
    else
    {
        sprintf(pattern + 6 + 6 * index, "[^|]*");
        sprintf(pattern + 11 + 6 * index, "%s", keyString);
        sprintf(pattern + 11 + 6 * index + keyLen, "'");
    }
    debug printf("filter cmd=%s\n", pattern);
    debug printf("fout=%d", fout);
    doCmd(fin, fout, FD_DEFAULT, pattern);
    debug doCmd(fin, FD_DEFAULT, FD_DEFAULT, "grep '.'");
    free(pattern);
    return;
}

void printFd(fd fin)
/* maybe it's better.
{
    filter(fin, 1, false, "", FILTER_NULL);
}
 */
{
    doCmd(fin, FD_DEFAULT, FD_DEFAULT, "grep '.'");
}
