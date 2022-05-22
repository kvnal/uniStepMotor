#include "uniStepMotor.h"

UniStepMotor::UniStepMotor(int IN1_, int IN2_, int IN3_, int IN4_){
    IN1 = IN1_;
    IN2 = IN2_;
    IN3 = IN3_;
    IN4 = IN4_;

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
}

void UniStepMotor::rotate(int degree){

    if(micros()-lastTime >=1000){
      lastTime = micros();  
      stepCase(STEPS);
      if(STEPS > 7) STEPS =0;
      STEPS++;
    }
}

void UniStepMotor::rotateFirst(int degree){
  int rev = 4096;

  while(degree){
  if(micros()-lastTime >=900){
      lastTime = micros();  
      stepCase(STEPS);
      if(STEPS > 7) STEPS =0;
      STEPS++;
      rev--;
    }

    
    if(rev==0){
      degree--;
      rev=4096;
    }
  }
}
void UniStepMotor::stepCase(int steps){
  switch(steps){
     case 0:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     case 1:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, HIGH);
     break; 
     case 2:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 3:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 4:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 5:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
       case 6:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 7:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     default:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
  }
}
