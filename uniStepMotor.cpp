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
  stepPinCase(8);
}

int UniStepMotor::getState(){
  return motor_state;
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


//get step count left func
double UniStepMotor::getAngleLeft(){
  return (double) 360.0*step_count/STEPS_IN_ONE_REV;
}

double UniStepMotor::getRevolutionLeft(){
  return ((double) step_count)/STEPS_IN_ONE_REV;
}

int UniStepMotor::getStepsLeft(){
  return step_count;
}


// take - move stepper motor
void UniStepMotor::completeStepsFirst(){

  if(motor_state==1){
    while(step_count){
      if(micros()-last_time>=STEPS_INTERVAL_GAP){
        last_time = micros();
        stepPinCase(step_for_step_pin_case);
        setStepForStepPinCase();
        step_count--;
      }
    }
    stepPinCase(8);
  }
}

int UniStepMotor::takeSteps(){
  if(motor_state==0 || step_count==0){  
    stepPinCase(8);
    return 0; //stopped or steps completed;
  }

  if(micros()-last_time >= STEPS_INTERVAL_GAP){
    last_time=micros();
    stepPinCase(step_for_step_pin_case);
    setStepForStepPinCase();
    step_count--;
  }
  return 1; //moving
}

int UniStepMotor::takeNonStopSteps(){
  if(motor_state == 0) return 0; //stop
  if(micros()-last_time >= STEPS_INTERVAL_GAP){
    last_time = micros();
    stepPinCase(step_for_step_pin_case);
    setStepForStepPinCase();
  }
  return 1;
}