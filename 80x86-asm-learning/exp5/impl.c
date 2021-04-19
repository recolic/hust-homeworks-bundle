#include <Windows.h>
#include <tchar.h>
extern HWND hShowWin;

#define PRODUCT_NUM 6
BOOL calc_done = FALSE;

typedef struct _product {
	CHAR name[32];
	LONG in_price;
	LONG out_price;
	CHAR grade;
} product;

product products[PRODUCT_NUM] = {{"scala", 30, 70, '?'},{"java", 500, 500, '?'},{"golang", 60, 50, '?'},{"C++1z", 1000, 1100, '?'},{"Python", 10, 1000, '?'},{"Assembly", 100000, 1, '?'}};

char profit_mark_of(float o, float i) {
    float rate = o / i - 1;
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
void calc_average() {
	SetWindowText(hShowWin, TEXT("Calculation done."));
	calc_done = TRUE;
	for(int cter = 0; cter < PRODUCT_NUM; ++cter) {
		products[cter].grade = profit_mark_of((float)products[cter].out_price, (float)products[cter].in_price);
	}
}

// Avoid linking libc.
void r_memcpy(void *target, void *source, int len) {
	for(int cter = 0; cter < len; ++cter)
		((char *)target)[cter] = ((char *)source)[cter];
}
void r_strncpy_fillspace(char *target, char *source, int len) {
	BOOL done = FALSE;
	for(int cter = 0; cter < len; ++cter) {
		if(done) target[cter] = ' ';
		else if(!source[cter]){
			done = TRUE;
			target[cter] = ' ';
		}
		else
			target[cter] = source[cter];
	}
}
void r_long8_to_mem(char *target, long num) {
	target[0] = num / 10000000 % 10 + '0';
	target[1] = num / 1000000 % 10 + '0';
	target[2] = num / 100000 % 10 + '0';
	target[3] = num / 10000 % 10 + '0';
	target[4] = num / 1000 % 10 + '0';
	target[5] = num / 100 % 10 + '0';
	target[6] = num / 10 % 10 + '0';
	target[7] = num / 1 % 10 + '0';
	for(int cter = 0; cter < 8; ++cter) {
		if(target[cter] == '0') target[cter] = ' ';
		else break;
	}
}
void r_serialize_record(char *target, product *p) {
	// len(target) = 28
	r_strncpy_fillspace(target, p->name, 8);
	r_long8_to_mem(target + 8, p->in_price);
	r_long8_to_mem(target + 16, p->out_price);
	target[24] = ' ';
	target[25] = p->grade;
	target[26] = '\r';
	target[27] = '\n';
}
#define INIT_STR "name    in_price out_price grade\r\n"
void show_list() {
	char buf[28*PRODUCT_NUM + sizeof(INIT_STR)] = INIT_STR;
	int pos = sizeof(INIT_STR) - 1;
	for(int cter = 0; cter < PRODUCT_NUM; ++cter, pos += 28) {
		r_serialize_record(buf + pos, &products[cter]);
	}
	buf[sizeof(buf)] = '\0';
	SetWindowTextA(hShowWin, buf);
}