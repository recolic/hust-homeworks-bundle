#include "afx.h"

extern char products_name[PRODUCT_NUM][32];
extern int output_price[PRODUCT_NUM];
extern int input_price[PRODUCT_NUM];
extern int rank_table[PRODUCT_NUM];
extern float profit_table[PRODUCT_NUM];

void func3_fill_profit_table() {
    int cter;
    for(cter = 0; cter < PRODUCT_NUM; ++cter)
        profit_table[cter] = output_price[cter] / input_price[cter] - 1;
}

void func4_fill_rank_table() {
    int cter;
    int cter2;
    for(cter = 0; cter < PRODUCT_NUM; ++cter) {
        rank_table[cter] = 1;
        for(cter2 = 0; cter2 < PRODUCT_NUM; ++cter2) {
            if(profit_table[cter] < profit_table[cter2])
                ++rank_table[cter];
        }
    }
}

char profit_mark_of(int index) {
    float rate = output_price[index] / input_price[index] - 1;
    if(rate < 0)
        return 'F';
    if(rate > 0.9)
        return 'A';
    if(rate > 0.5)
        return 'B';
    if(rate > 0.2)
        return 'C';
    return 'D';
}

int search_product(const char *name) {
    int cter = 0;
    for(; cter < PRODUCT_NUM; ++cter) {
        const char *product_name = products_name[cter];
        if(streql(name, product_name))
            return cter;
    }
    return -1;
}
