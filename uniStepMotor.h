#ifndef uni
#define uni

#include "Arduino.h"

class UniStepMotor{
  public:
    UniStepMotor(int IN1_ , int IN2_, int N3_, int IN4_);

    void rotate(int degree);
    void rotateFirst(int degree);

    private:
      int IN1;
      int IN2;
      int IN3;
      int IN4;
      int STEPS = 0;
      unsigned long lastTime;
      void stepCase(int steps);
};
#endif
