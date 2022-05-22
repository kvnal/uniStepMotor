#ifndef uni
#define uni

#include "Arduino.h"

class UniStepMotor{
  public:
    UniStepMotor(int IN1_ , int IN2_, int N3_, int IN4_);

    int rotateFirst(int degree);
    int revolutionFirst(int no_of_rev);

    private:
      int STEPS_INTERVAL_GAP = 1000; //900-1000 for speed
      int STEPS_IN_ONE_REV = 4096; // (360/step angle(5.625) * reduction ratio(64))


      int IN1;
      int IN2;
      int IN3;
      int IN4;
      
      int STEPS = 0;
      bool DIRECTION = true;
      unsigned long LAST_TIME;
      
      void stepCase(int steps);
      void setSteps();
      void setDirection(bool clockwise);
      void setDirectionByValue(int value);
};
#endif
