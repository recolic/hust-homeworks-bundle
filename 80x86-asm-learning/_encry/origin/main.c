/**
 * This source is extremely unsafe. You must not use it under any consequence
 *     except hust homework.
 */

/* C99 only */
typedef int bool;
#define true 1
#define false 0

typedef unsigned long uint32_t;

char user[32] = "bensong liu";
/*char pswd[32] = "testP@ssw0rd,:)";*/
unsigned long IllIlIlIOoOoOo0o[32] = {2786,5586,4070,2786,5615,1109,4070,4070,4944,1887,1214,5600,3474,152,1861};

unsigned long IllIllIl0OoOO00o = 18421261;
unsigned long llIlIIlIO0O0ooO0 = 4196056063;

#define PRODUCT_NUM 3

char products[PRODUCT_NUM][32] = {"book", "pen", "scala"};
/*unsigned long input_price[PRODUCT_NUM] = {4444444,33811,22108};*/
unsigned long input_price[PRODUCT_NUM] = {24559091,20310268,20265651};
/*unsigned long output_price[PRODUCT_NUM] = {3333344,44622,55801};*/
unsigned long output_price[PRODUCT_NUM] = {17281039,20300449,20296982};


/* r_hash */

unsigned long r_hash(const char *cstr) {
    unsigned long seed = 19990719;
    unsigned long tmp;
    while(*cstr) {
        tmp = *cstr;
        seed += (tmp << (tmp % 16));
        ++cstr;
    }
    return seed;
}

/* rsa */

/* Montgomery module method */
int meg_mod(int modN, uint32_t base, uint32_t *exp, int exp_len) {
    return 0; /* GGGGGGG */
}
unsigned long naive_mod(unsigned long modN, unsigned long base, unsigned long exp) {
    unsigned long half;
    unsigned long result;
    int cter = 0;
    if(exp < 10000) {
        result = base % modN;
        for(;cter < exp; ++cter) {
            result *= base;
            result %= modN;
        }
    }
    else {
        half = naive_mod(modN, base, exp / 2);
        result = half * half % modN;
        if(exp % 2) {
            result = result * base % modN;
        }
    }
    return result;
}
/*
bool verifyIllIlIlIOoOoOo0o(const char plain[32], const char encrypted[32], const char rsa2048_pubkey[256], int rsa2048_N) {

}
*/
bool fake_verify(const char plain[32], const unsigned long encrypted[32], int pubkey, int n) {
    int cter = 0;
    unsigned long curr;
    for(; cter < 32; ++cter) {
        curr = plain[cter];
        if(!curr && !encrypted[cter]) return true;
        curr = naive_mod(n, curr, pubkey);
        if(curr != (encrypted[cter]))
            return false;
    }
    return true;
}

void r_print_2d(int l) {
    char debug[3] = {0};
    debug[0] = l/10%10+'0';
    debug[1] = l%10+'0';
    r_print(debug);
}

void r_print_long(unsigned long l) {
    char debug[12] = {0};
    char *buf = debug;
    debug[0] = l/10000000000%10+'0';
    debug[1] = l/1000000000%10+'0';
    debug[2] = l/100000000%10+'0';
    debug[3] = l/10000000%10+'0';
    debug[4] = l/1000000%10+'0';
    debug[5] = l/100000%10+'0';
    debug[6] = l/10000%10+'0';
    debug[7] = l/1000%10+'0';
    debug[8] = l/100%10+'0';
    debug[9] = l/10%10+'0';
    debug[10] = l%10+'0';
    while(*buf == '0') ++buf;
    r_print(buf);
}
int r_strlen(const char *txt) {
    int res = 0;
    while(*txt) {
        ++txt, ++res;
    }
    return res;
}
bool r_streql(const char *a, const char *b) {
    while(*a) {
        if(*a != *b)
            return false;
        ++a, ++b;
    }
    return !(*b);
}
void r_print(const char *txt) {
    int len = r_strlen(txt);
    char buffer[256];
    int cter = 0;
    for(; cter < len; ++cter) {
        buffer[cter] = txt[cter];
    }
    buffer[cter] = '$';
    /*r_print(buffer);  alter `call r_print_` to `call r_print_impl` */
    __asm lea ax, -100h[bp];
    __asm push dx
    __asm mov dx, ax
    __asm mov ah, 9
    __asm int 21h
    __asm pop dx
}
char r_noecho_getchar() {
    char tmp = '\n';
    /* insert `call r_getchar_impl` */
    __asm mov ah, 08h;
    __asm int 21h;
    return tmp;
}
char r_getchar() {
    char tmp = '\n';
    /* insert `call r_getchar_impl` */
    __asm mov ah, 01h;
    __asm int 21h;
    return tmp;
}
void r_exit() {
    /* insert `call r_exit_impl` */
    __asm mov ah, 4ch
    __asm xor al, al
    __asm int 21h
}

void echo(const char *txt) {
    r_print(txt);
    r_print("\r\n");
}


void noecho_readline_unsafe(char *out) {
    char c;
    int pos = 0;
    while(true) {
        c = r_noecho_getchar();
        if(c == '\r' || c == '\n')
            break;
        out[pos] = c;
        ++pos;
    }
    out[pos] = '\0';
}
void readline_unsafe(char *out) {
    char c;
    int pos = 0;
    while(true) {
        c = r_getchar();
        if(c == '\r' || c == '\n')
            break;
        out[pos] = c;
        ++pos;
    }
    out[pos] = '\0';
}

/***************** lib done ***************/
void decrypt_prices(const char *key) {
    int cter;
    unsigned long hashed_key = r_hash(key);
    for(cter = 0; cter < PRODUCT_NUM; ++cter) {
        input_price[cter] ^= hashed_key;
        output_price[cter] ^= hashed_key;
    }
}

bool login() {
    char buffer[32] = { 0 };
    int cter;

    r_print("Your name please: ");
    readline_unsafe(buffer);

    if(buffer[0] == '\0')
        return false;
    if(buffer[0] == 'q')
        r_exit();
    if(!r_streql(buffer, user)) {
        echo("Permission denied.");
        return false;
    } 

    r_print("Your password please: ");
    noecho_readline_unsafe(buffer);
    if(!fake_verify(buffer, IllIlIlIOoOoOo0o, llIlIIlIO0O0ooO0, IllIllIl0OoOO00o)) {
        echo("Permission denied.");
        return false;
    }
    echo("Passed.");
    decrypt_prices(buffer);
    echo("Information decrypted.");
    return true;
}

char profit_mark_of(int index) {
    float rate = (float)output_price[index] / (float)input_price[index] - 1;
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



void show_secret(bool logged_in) {
    char buf[32];
    int index = -1;
    int cter = 0;
    r_print("What product ? ");
    readline_unsafe(buf);
    if(r_streql(buf, "q"))
        r_exit();
    if(r_streql(buf, ""))
        return;
    for(;cter < PRODUCT_NUM; ++cter) {
        if(r_streql(buf, products[cter])) {
            index = cter;
            break;
        }
    }
    if(index == -1)
        echo("Not found.");
    else {
        if(logged_in) {
            buf[0] = profit_mark_of(index);
            buf[1] = 0;
            r_print("Input price ");
            r_print_long(input_price[index]);
            r_print(", output price ");
            r_print_long(output_price[index]);
            r_print(", profit rate ");
            echo(buf);
            return;
        }
        else {
            echo(buf);
        }
    }
}


int fake_main() {
    int cter = 0;
    for(; cter < 3; ++cter) {
        if(login()) {
            while(true) show_secret(true);
            return 0;
        }
    }
    while(true) show_secret(false);
    return 0;
}
