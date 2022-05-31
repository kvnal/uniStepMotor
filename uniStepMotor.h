#ifndef uni
#define uni

#include "Arduino.h"

class UniStepMotor{
  public:
    UniStepMotor(int IN1_ , int IN2_, int N3_, int IN4_);

    //config
    void configRevSteps(int no_of_steps_in_1_rev); //default 4096
    void enableFullStepping();
    void disableFullStepping();

    //finish first
    void completeStepsFirst();

    //async motion
    int takeSteps(); //return state
    int takeNonStopSteps(); //infinite move

    //async rotation 
    void setAngle(int degree);
    void setAngleAndContinue(int degree);
    double getAngleLeft();
    
    //async revolution
    void setRevolution(int no_of_rev);
    void setRevolutionAndContinue(int no_of_rev);
    double getRevolutionLeft(); //returns no of rev left from setRevolution();

    //async step move
    void setSteps(int no_of_steps);
    void setStepsAndContinue(int no_of_steps);
    int getStepsLeft(); //return step_count

    
    //direction
    void setDirection(int clockwise); // 1 for cw 0 ccw;
    int getDirection();

  

    //states
    void setStateStop();
    void setStateContinue();
    int getState(); 


    //calc func
    int degreeToSteps(int degree);
    double stepsToDegree(int steps);


    private:
      int STEPS_INTERVAL_GAP = 1000; //900-1000 for speed (half-stepping) 1100-1200 (full-stepping)
      int STEPS_IN_ONE_REV = 4096; // (360/step angle(5.625) * reduction ratio(64))

      int IN1;
      int IN2;
      int IN3;
      int IN4;
      
      int step_for_step_pin_case = 0; // 0-7 for switch step case 

      bool direction = true;  // true - cw
      unsigned long last_time;
      
      int motor_state = 0;  // 1 move 0 stop
      
      unsigned int step_count =0;

      bool full_stepping = false;
      //func
      void stepPinCase(int steps); //stepper pin controller
      void setStepForStepPinCase(); //steps for step case
      void setDirectionByValue(int value);
      void checkAndSetStepsForFullStepping();
      
};
#endif
