#Documenation

__Installation__


__circuit diagram__


#### 1. Import Library
```#include<uniStepMotor.h>```
  
#### 2. Initiate Stepper Motor
```UniStepMotor = myStepper(int IN1, int IN2, int IN3, int IN4);``` 
  <br>

  _example:_

    UniStepMotor = myStepper1(8,9,10,11);
    
    //*driver name**'s pin for IN1 to IN4 is connected to 8 to 11 on arduino board*
    
<br>

#### 3. Stepper motor configration *(optional)*

_configration required only if half stepping steps differs_

__default__ pre-configured at __4096__

_configure by calling:_ ```myStepper.configRevSteps(int no_of_steps_in_1_rev);```


<br>
#### 4. Full-Stepping configration
to enable/disable full stepping

    myStepper.enableFullStepping(); // to enable
    myStepper.disableFullStepping(); // to disable


_note: stepper will take 1/2 of total steps if full stepping is enabled. i.e by default **2048** (4096÷2) steps in one revolution_

__when to use?__
when you need speed (faster revolution) and can compromise precision angle of the stepper.

<br>

#### 5. Motor States
In this library motor is divided into two states - 
- **Continue / moving**  _(denoted by int value 1)_
- **Stop / pause** _(denoted by int value 0)
  




