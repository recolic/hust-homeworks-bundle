/**
 * This source is extremely unsafe. You must not use it under any consequence
 *     except hust homework.
 */

#include "afx.h"

char user[32] = "bensong liu";
char pswd[32] = "test";
char shopA[16] = "SHOP1";
char shopB[16] = "SHOP2";

char products_name[PRODUCT_NUM][32] = {"pen", "book", "scala"};
int input_price[PRODUCT_NUM] = {35, 22, 61};
int output_price[PRODUCT_NUM] = {11, 28, 1000};
float profit_table[PRODUCT_NUM] = {0,0,0};
int rank_table[PRODUCT_NUM] = {-1,-1,-1};

bool logged_in = false;

void echo(const char *txt) {
    printf("%s\r\n", txt);
}

void readline_unsafe(char *out) {
    char c;
    int pos = 0;
    while(true) {
        c = getchar();
        if(c == '\r' || c == '\n')
            break;
        out[pos] = c;
        ++pos;
    }
    out[pos] = '\0';
}

bool login() {
    char buffer[32] = "";
    int cter;

again:
    printf("Your name please: ");
    readline_unsafe(buffer);

    if(buffer[0] == '\0')
        goto again;
    if(buffer[0] == 'q')
        exit(0);
    if(!streql(buffer, user)) {
        echo("Permission denied.");
        goto again;
    } 

    printf("Your password please: ");
    readline_unsafe(buffer);
    if(!streql(buffer, pswd)) {
        echo("Permission denied.");
        goto again;
    }
    echo("Passed.");
    return true;
}

void func1_ls() {
    int cter;
    for(cter = 0; cter < PRODUCT_NUM; ++cter) {
        printf("%s > InputPrice %d OutputPrice %d.\r\n", products_name[cter], input_price[cter], output_price[cter]);
    }
}

void func2_edit() {
    char name[32];
    int input, output;
    int pos;
    echo("Give `$name $inputPrice $outputPrice` please.");
    scanf("%s %d %d", name, &input, &output);

    pos = search_product(name);
    if(pos == -1) {
        echo("Not found error.");
        return;
    }

    input_price[pos] = input;
    output_price[pos] = output;
    echo("Done.");
}

void func5_print_profit_and_rank() {
    int cter;
    for(cter = 0; cter < PRODUCT_NUM; ++cter) {
        printf("%s: profit mark %c rank %d\r\n", products_name[cter], profit_mark_of(cter), rank_table[cter]);
    }
}

void func6_exit() {
    exit(0);
}

int main() {
    char option[16];
    login(); /*Always true*/
    while(true) {
        echo("");
        echo("func1_ls");
        echo("func2_edit");
        echo("func3_calc_profit");
        echo("func4_calc_rank (depend: func3)");
        echo("func5_print_profit_and_rank (depend: func4)");
        echo("func6_exit");
        printf(" 1-6 ? ");
        readline_unsafe(option);
        switch(option[0]) {
            case '1':
                func1_ls();
                break;
            case '2':
                func2_edit();
                break;
            case '3':
                func3_fill_profit_table();
                break;
            case '4':
                func4_fill_rank_table();
                break;
            case '5':
                func5_print_profit_and_rank();
                break;
            case '6':
                func6_exit();
                break;
        }
    }
}