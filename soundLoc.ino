#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//d_t = x*sin(ang)/s
float soundDetDist = 0.14;//x = 0.14 m
float v_s = 0.000343; // m/micros
int timeoutTime = 1000;
int soundDet1 = 14;
int soundDet2 = 15;
int soundDet3 = 16;
int soundDet4 = 17;
int time1 = 0;
int time2 = 0;
int time3 = 0;
int time4 = 0;
int detect1 = 0;
int detect2 = 0;
int detect3 = 0;
int detect4 = 0;
double ang = 0;

//motors
int leftMotor = 11;
int rightMotor = 12;
int heading = 0;

//stack
int stackTime[4];
int *spTime;
int stackPlace[4];
int *spPlace;
#define push(sp, n) (*((sp)++) = (n))
#define pop(sp) (*--(sp))

void setup() {
  // put your setup code here, to run once:
  pinMode(soundDet1, INPUT);
  pinMode(soundDet2, INPUT);
  pinMode(soundDet3, INPUT);
  pinMode(soundDet4, INPUT);

  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  
  spTime = stackTime;
  spPlace = stackPlace;

  

}

void loop() {
  // put your main code here, to run repeatedly: 
  //loop2();
  
  
  int detectNum = 0;
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;
  int val4 = 0;
  detect1 = 0;
  detect2 = 0;
  detect3 = 0;
  detect4 = 0;
   //ACTIVE CODE
 // delay(1000);
  while(detect1 == 0 || detect2 == 0 || detect3 == 0 || detect4 == 0){
    //detect loop
    int timeout1 = micros();
    int timeout = 0;
    while((val1 == 0 || detect1 == 1) && (val2 == 0 || detect2 == 1) && (val3 == 0 || detect3 == 1) && (val4 == 0 || detect4 == 1) && timeout < timeoutTime){
      val1 = digitalRead(soundDet1);
      val2 = digitalRead(soundDet2);
      val3 = digitalRead(soundDet3);
      val4 = digitalRead(soundDet4);
      timeout = micros() - timeout1;
    }
    time1 = micros();
    //detect second
    if(val1 == 1 && detect1 == 0){
      detectNum ++;
      detect1 = 1;
      push(spPlace, 1);
      push(spTime, time1);
    }else if(val2 == 1 && detect2 == 0){
      detectNum ++;
      detect2 = 1;
      push(spPlace, 3);//2
      push(spTime, time1);
    }else if(val3 == 1 && detect3 == 0){
      detectNum ++;
      detect3 = 1;
      push(spPlace, 5);//3
      push(spTime, time1);
    }else if(val4 == 1 && detect4 == 0){
      detectNum ++;
      detect4 = 1;
      push(spPlace, 7);//7
      push(spTime, time1);
    }else if(timeout >= timeoutTime){
      if(detect1 == 1 || detect2 == 1 || detect3 ==1 || detect4 == 1){
        detect1 = 1;
        detect2 = 1;
        detect3 = 1;
        detect4 = 1;
        //push(spTime, timeoutTime);
      }
    }
  }

  
  if(1){
    //time4 = pop(sp);
    
    int dir = 0;
    int first = 0;
    int sec = 0;
    int third = 0;
    int fourth = 0;
    if(detectNum < 4){
      for(int i = 0;i<detectNum;i++){
        time1 = pop(spTime);
        first = pop(spPlace);
      }
      //dir = first;
    }else if(detectNum == 4){
      
      fourth = pop(spPlace);
      third = pop(spPlace);
      sec = pop(spPlace);
      first = pop(spPlace);
  
      time4 = pop(spTime);
      time3 = pop(spTime);
      time2 = pop(spTime);
      time1 = pop(spTime);
  
      if(time2 - time1 > 150){
        dir = first;
      }else{
        if((first == 1 || first == 7) && (sec == 1 || sec == 7)){ 
          dir = 8;
        }else{
          dir = (first+sec)/2;
        }
      }
    
      //int t = abs(time1 - time2);
      Serial.print("Dir: ");
      Serial.print(dir);
      Serial.print(", Time delay: ");
      Serial.print(time2-time1);
      //ang = asin(t*c/soundDetDist);
      //ang = acos((sqrt(soundDetDist*soundDetDist-t*c*t*c) - soundDetDist*soundDetDist)/2*soundDetDist);
      //Serial.print(t);
      //Serial.print("   ");
      //Serial.print();
      //Serial.print("    ");
      //Serial.print(ang*57.296);
      Serial.print("\n");
      //change dir
      if(dir == 1){
        dir = 5;
      }else if(dir == 2){
        dir = 6;
      }else if(dir == 3){
        dir = 7;
      }else if(dir == 5){
        dir = 3;
      }else if(dir == 6){
        dir = 2;
      }else if(dir == 7){
        dir = 1;
      }else if(dir == 8){
        dir = 0;
      }
      
      moveBot(dir);
      delay(1000);
    }
  }
}

void loop2(){
  moveBot(0);
  delay(2000);
  moveBot(1);
  delay(2000);
  moveBot(2);
  delay(2000);
  moveBot(3);
  delay(2000);
  moveBot(4);
  delay(2000);
  moveBot(5);
  delay(2000);
  moveBot(6);
  delay(2000);
  moveBot(7);
}

void moveBot(int head)
{
  Serial.println(head);
  if(head == -1)
  {
    return;
  }
  if(head < 3)
  {
    digitalWrite(leftMotor, HIGH);
    delay(head * 500);
    digitalWrite(leftMotor, LOW);
  }
  else if(head < 5)
  {
    digitalWrite(leftMotor, HIGH);
    delay(head * 450);
    digitalWrite(leftMotor, LOW);
  }
   else if(head < 8)
  {
    digitalWrite(rightMotor, HIGH);
    delay((head-4) * 500);
    digitalWrite(rightMotor, LOW);
  }
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightMotor, HIGH);
  delay(500);
  digitalWrite(leftMotor, LOW);
  digitalWrite(rightMotor, LOW);
}

