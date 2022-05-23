/**
 * @file uniStepMotor.cpp
 * @author github.com/kvnal
 * @brief 
 * @version 0.2
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 * 
 * 
 * 
 */

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


void UniStepMotor::setDirectionByValue(int value){
  if(value>0)
    setDirection(true);
  else 
    setDirection(false);

}

void UniStepMotor::setDirection(bool clockwise){
  DIRECTION = clockwise ? true : false;
}

void UniStepMotor::setSteps(){
  if(DIRECTION) STEPS++;
  if(!DIRECTION) STEPS--;

  if(STEPS<0) STEPS=7;
  if(STEPS>7) STEPS=0;
} 

int UniStepMotor:: revolutionFirst(int no_of_rev){
  
  setDirectionByValue(no_of_rev);

  int steps = STEPS_IN_ONE_REV * abs(no_of_rev);
  
  while(steps>=0){
  if(micros()-LAST_TIME >= STEPS_INTERVAL_GAP){
    LAST_TIME=micros();
    stepCase(STEPS);
    setSteps();
    steps--;
    }
  }
  stepCase(8); //off
  return 1;
}

int UniStepMotor::rotateFirst(int degree){
  setDirectionByValue(degree);
  int steps = degreeToSteps(degree);

  while(steps){
  if(micros()-LAST_TIME >=STEPS_INTERVAL_GAP){
      LAST_TIME = micros();

      stepCase(STEPS);
      setSteps();
      steps--;
    }
  }
  stateStop();
  return 1;
}


int UniStepMotor::revolution(int no_of_rev){
  if(MOTOR_STATE==0 || MOTOR_STATE==2){
    //assign STEPS_COUNT
    setDirectionByValue(no_of_rev);
    STEPS_COUNT = STEPS_IN_ONE_REV * abs(no_of_rev);

    if(MOTOR_STATE==2) stateContinue();
  } 
  
  if(STEPS_COUNT==0){
    stateStop();
    return -1; //stop
  }

  if(MOTOR_STATE==1){
    //START / CONTINUE
    if(micros()-LAST_TIME >=STEPS_INTERVAL_GAP){
      LAST_TIME = micros();
      stepCase(STEPS);
      setSteps();
      STEPS_COUNT--;
    }
    return 1; //continue
  }

  
}

int UniStepMotor::rotate(int degree){
  
  if(MOTOR_STATE = 0 || MOTOR_STATE ==2){
    setDirectionByValue(degree);
    STEPS_COUNT = degreeToSteps(degree);
  
    if(MOTOR_STATE==2) stateContinue();
  }

  if(STEPS_COUNT==0){
    stepCase(8);
    return -1;
  }

  if(MOTOR_STATE==1){
    if(micros()-LAST_TIME>=STEPS_INTERVAL_GAP){
      LAST_TIME = micros();

      stepCase(STEPS);
      setSteps();
      STEPS--;
    }
    return 1;
  }
  
  
}

int UniStepMotor::degreeToSteps(int degree){
  int steps = ((double) STEPS_IN_ONE_REV)/(360.0/abs(degree));
  return steps;
}

void UniStepMotor::stateStop(){
  stepCase(8);
  MOTOR_STATE = -1;
}

void UniStepMotor::stateContinue(){
  MOTOR_STATE = 1;
}

void UniStepMotor::stateReset(){
  MOTOR_STATE=0;
}

void UniStepMotor::stateResetAndStart(){
  MOTOR_STATE=2;
}


int UniStepMotor::getState(){
  return MOTOR_STATE;
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
