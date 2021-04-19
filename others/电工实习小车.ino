/*
* Reconstructed by Recolic Keghart.
 * Nov 1, 2017
 * TODO: add reverse mode? --Done.
 */
#define STANDARD_SPEED 200
#define SLOW_WHILE_AUTO_DRIVE 0.9
int usual_speed = STANDARD_SPEED;
int bReverseMode = 0;
int bForceBoost = 0;

#define LEFT_POWER_MAIN 6
#define LEFT_POWER 5
#define RIGHT_POWER 9 
#define RIGHT_POWER_MAIN 10

//If right wheel is higher, set it to >1.
#define ADJUST_LR_BALANCE 1.2

int L_st=0;
void setup()
{
  Serial.begin(9600);
  pinMode( 18, INPUT);
  pinMode( 14, INPUT);
  pinMode( 17, INPUT);
  pinMode( 16, INPUT);
  pinMode( RIGHT_POWER_MAIN, OUTPUT);
  pinMode( LEFT_POWER_MAIN, OUTPUT);
  pinMode( LEFT_POWER, OUTPUT);
  pinMode( RIGHT_POWER, OUTPUT);
  analogWrite(LEFT_POWER , 0);

  analogWrite(LEFT_POWER_MAIN , 0);

  analogWrite(RIGHT_POWER , 0);

  analogWrite(RIGHT_POWER_MAIN , 0);

}

//libraries begin.
#define REVERSE_BOOL(bBool) (bBool?0:1)
void set_mode(int left_sp, int right_sp, int bNeg = 0)
{
  bNeg = bReverseMode ? REVERSE_BOOL(bNeg) : bNeg;
  left_sp *= ADJUST_LR_BALANCE;
  if(bForceBoost)
  {
    left_sp *= 5;
    right_sp *= 5;
  }
  if(bNeg)
  {
    analogWrite(LEFT_POWER , left_sp);
    analogWrite(LEFT_POWER_MAIN , 0);
    analogWrite(RIGHT_POWER , right_sp);
    analogWrite(RIGHT_POWER_MAIN , 0);
  }
  else
  {
    analogWrite(LEFT_POWER , 0);
    analogWrite(LEFT_POWER_MAIN , left_sp);
    analogWrite(RIGHT_POWER , 0);
    analogWrite(RIGHT_POWER_MAIN , right_sp);
  }
}

void go_left(int bNeg = 0)
{
  set_mode(usual_speed, 0, bNeg);
}
void go_right(int bNeg = 0)
{
  set_mode(0, usual_speed, bNeg);
}
void go_forward(int bNeg = 0)
{
  set_mode(usual_speed, usual_speed, bNeg);
}
void set_stop()
{
  set_mode(0, 0, 0);
}
#define _BACK 1
//All lib done.

/*
  //Slower while auto-driving.
  usual_speed *= SLOW_WHILE_AUTO_DRIVE;
  if(  !(digitalRead(14)  ||  digitalRead(18))  )
  {
    go_right();
  }
  else
    go_forward();
  usual_speed = STANDARD_SPEED;
  return;
*/

void _track()
{
  //Slower while auto-driving.
  usual_speed *= SLOW_WHILE_AUTO_DRIVE;
  if (( !( digitalRead(14) ) && digitalRead(18) ))
  {
    go_left();
  }
  else
  {
    if (( !( digitalRead(18) ) && digitalRead(14) ))
    {  
      go_right();
    }
    else
    {
      if (( !( digitalRead(14) ) && !( digitalRead(18) ) ))
        go_forward();
      else
        set_stop();
    }
  }
  usual_speed = STANDARD_SPEED;
}


void _trace()
{
  //Slower while auto-driving.
  usual_speed *= SLOW_WHILE_AUTO_DRIVE;
  if (( !( digitalRead(16) ) && digitalRead(17) ))
  {
    go_left();
  }
  else
  {
    if (( !( digitalRead(17) ) && digitalRead(16) ))
      go_right();
    else
        go_forward();
  }
  usual_speed = STANDARD_SPEED;
}

void loop()
{
  char getstr=Serial.read();
  switch(getstr)
  {
  case 'l':
    go_left();
    L_st=0;
    break;
  case 'r':
    go_right();
    L_st=0;
    break;
  case 'f':
    go_forward();
    L_st=0;
    break;
  case 's':
    set_stop();
    L_st=0;
    break;
  case 'b':
    go_forward(_BACK);
    L_st=0;
    break;
  case 'i':
    L_st=1;
    break;
  case 't':
    L_st=2;
    break;
  case 'x': //Boost mode
    set_mode(5*usual_speed, 5*usual_speed);
    break;
  case 'z': //Reverse mode on
    bReverseMode = REVERSE_BOOL(bReverseMode);
    break;
  case 'c':
    bForceBoost = REVERSE_BOOL(bForceBoost);
    break;
  }
  if(L_st==1)  _track();
  else if(L_st==2)  _trace();
}



