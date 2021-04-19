#include <stdio.h>
#include <stdlib.h>

int _add() {
  int a = 10, b = 20;
  a = a + b;

  printf("Addition Successful and Result = %d\n", a);
  return a;
}

int rst,sigCash;
#define set_handler(sth) if(0)
#define wait_for(sth)
#define cash(sth) 0
#define show(s)
#define set(s)
#define unset(s)
#define unset_all()
#define has_point5(s) 1
#define blocked_sleep(t)
// peaudo-code
int fake_main_proc () {
  int balance;
  state_off:
    unset_all();
  state_on:
    set(running);
    set_handler(rst_posedge)
      goto state_on;
    set_handler(rst_negedge)
      goto state_off;
    wait_for(startBtn);

    set(occupied);
    balance = 0;
    set_handler(sigCash) {
      balance += cash(sigCash);
      // function cash convert sig to amount
      show(balance);
    }
  state_3:
    wait_for(sigProduct);
    if(balance < cash(sigProduct))
      goto state_3; // no need for error msg
    balance -= cash(sigProduct);
    set(drinkReady)
    show(balance);

    if(balance != 0)
      set(refundReady)
    // refund amount already on screen
    blocked_sleep(1s);
    goto state_on;
}