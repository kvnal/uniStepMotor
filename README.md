_Arduino Device Control Library_
## 28BYJ-48 Stepper Motor (_unipolar_)
> Allows Arduino boards to control a one or more of stepper motors.
> 
> This library can control one or more steppers both asynchronously and synchronously. It includes various state management methods for controlling multiple stepper motors individually, as well as methods for setting angles, revolutions, number of steps, and motor direction.

<br>
#### Releases
To use this library, open the **Library Manager** in the Arduino IDE and install it from there. OR
< < manual installation >>

- 1.0.0 (latest)

<br>

## Usage
To use this library:
```cpp
#include<uniStepMotor.h>
```

#### circuit
<< circuit img here >>

<br>

#### Examples
<< examples here >>
<br>

#### 1. Initiate Stepper Motor

```cpp
UniStepMotor = myStepper(int IN1, int IN2, int IN3, int IN4);
``` 
Parameters
: - **_mystepper_**: a object variable of type ```UniStepMotor```
: - **_IN1 - IN4_**: Arduino board pin connected from [ULN2003]() Driver Module's output PIN from  IN1 - IN4. 

<br>
  

#### 2. Stepper motor 1 revolution steps configration *(optional)*
```cpp
myStepper.configRevSteps(int no_of_steps_in_1_rev);
```

__By default__ its configured at __4096__ steps. [How to calculate no. of steps in one revolution?]()


<br>

## Methods
#### 1. Full-Stepping
> To enable or disable [full-stepping]() in stepper motor.

__By default__ its configured as [half-stepping]() at __4096__ steps.

```cpp
    myStepper.enableFullStepping(); // to enable
    myStepper.disableFullStepping(); // to disable
```

_**note**: No. of steps will be reduced to 1/2 of no. of steps it takes in half-stepping. i.e **by default: **2048** steps in one revolution_

__when to use?__
when you need speed and can compromise precision angle of the stepper.

<br>

#### 2. Motor States
> Get current state or control motor working using methods below.

In this library their are two types of motor states:

Start or Moving
: denoted by ```int value 1```

Stopped or paused
: denoted by ```int value 0```

**Methods()**

_Get state of motor (moving or stopped)_ 
```cpp
  myStepper.getState()
  ```
**Returns**
**int value 1** : when motor is moving.
**int value 0** : when motor is not moving. It could be motor have completed its no. or steps of its state being stopped using ```setStateStop()```.

<br>

_Set States of motor_

```cpp
  myStepper.setStateContinue() // to start motor
  ```
```cpp
   myStepper.setStateStop() // to pause moving motor
   ```

<br>

##### Example
get 
```cpp

```
emergency stop - on pressing button stop motor
change direction after one revolution
working without stopping below code functionality 
working with two or more motors at same time
start motor 2 steps after motor 1 completed its steps.

