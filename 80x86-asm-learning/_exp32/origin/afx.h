#ifndef AFX_H
#define AFX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* C99 only */
typedef int bool;
#define true 1
#define false 0

#define streql !strcmp

#define PRODUCT_NUM 3

void func1_ls();
void func2_edit();
void func3_fill_profit_table();
void func4_fill_rank_table();
void func5_print_profit_and_rank();
void func6_exit();
char profit_mark_of(int index);
int search_product(const char *name);

#endif
