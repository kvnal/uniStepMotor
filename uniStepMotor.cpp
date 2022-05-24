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

//configration
void UniStepMotor::configRevSteps(int no_of_steps_in_1_rev){
  STEPS_IN_ONE_REV = no_of_steps_in_1_rev;
}


//calc
int UniStepMotor::degreeToSteps(int degree){
  int steps = ((double) STEPS_IN_ONE_REV)/(360.0/abs(degree));
  return steps;
}


double UniStepMotor::stepsToDegree(int steps){
  return (double) 360.0/(STEPS_IN_ONE_REV/step_count); 
}


//states

/*
* 1 - continue/start/move
* 0 - stop/pause
*/

void UniStepMotor::setStateContinue(){
  motor_state = 1;
}

void UniStepMotor:: setStateStop(){
  motor_state = 0;
}

int UniStepMotor::getState(){
  return motor_state;
}


//additional info
int UniStepMotor::getStepsLeft(){
  return step_count;
}


//direction

/*
* 1 - clockwise
* 0 - counter clockwise
*/

void UniStepMotor::setDirection(int clockwise){
  direction = (clockwise>0) ? 1 : 0;
}

int UniStepMotor::getDirection(){
  return direction;
}

void UniStepMotor::setDirectionByValue(int value){
  if(value>0)
    setDirection(1);
  else
    setDirection(0);
}


//set step_count 
void UniStepMotor::setAngle(int degree){
  setDirectionByValue(degree);
  step_count = degreeToSteps(abs(degree));
}

void UniStepMotor::setRevolution(int no_of_rev){
  setDirectionByValue(no_of_rev);
  step_count = STEPS_IN_ONE_REV * abs(no_of_rev);
}

void UniStepMotor::setSteps(int no_of_steps){
  setDirectionByValue(no_of_steps);
  step_count = abs(no_of_steps);
}

//set & continue state
void UniStepMotor::setAngleAndContinue(int degree){
  setAngle(degree);
  setStateContinue();
}

void UniStepMotor::setRevolutionAndContinue(int no_of_rev){
  setRevolution(no_of_rev);
  setStateContinue();
}

void UniStepMotor::setStepsAndContinue(int no_of_steps){
  setSteps(no_of_steps);
  setStateContinue();
}


//pin handling
void UniStepMotor::setStepForStepPinCase(){
  if(direction) step_for_step_pin_case++;
  if(!direction) step_for_step_pin_case--;

  if(step_for_step_pin_case<0) step_for_step_pin_case=7;
  if(step_for_step_pin_case>7) step_for_step_pin_case=0;
}


void UniStepMotor::stepPinCase(int steps){
 
  /*
  * 0-7 clockwise
  * 7-0 counter clockwise
  */

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
  if(MOTOR_STATE==-1) return  -1; //stop

  if(MOTOR_STATE==0 || MOTOR_STATE==2){
    //assign STEPS_COUNT
    setDirectionByValue(no_of_rev);
    STEPS_COUNT = STEPS_IN_ONE_REV * abs(no_of_rev);

    if(MOTOR_STATE==2) stateContinue();
    else return -1; //reset but stop
  } 
  
  if(STEPS_COUNT==0){
    stateStop();
    return -1; //steps done && stop
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
  if(MOTOR_STATE==-1) return  -1; //stop
  
  if(MOTOR_STATE == 0 || MOTOR_STATE ==2){
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
      STEPS_COUNT--;
    }
    return 1;
  }
  
  
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
