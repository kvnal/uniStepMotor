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
#### 1. Full-Stepping <sup>BETA</sup>
> To enable or disable [full-stepping]() in stepper motor.

__By default__ its configured as [half-stepping]() at __4096__ steps.

```cpp
    myStepper.enableFullStepping(); // to enable
    myStepper.disableFullStepping(); // to disable
```

_**Note**: No. of steps will be reduced to 1/2 of no. of steps it takes in half-stepping. i.e **by default: **2048** steps in one revolution_

**⚠ Note** : full-stepping is currently in beta stage. i might not perform like its expected to be.

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

- _Get state of motor (moving or stopped)_ 
```cpp
  myStepper.getState()
  ```
**Returns**
**int value 1** : when motor is moving.
**int value 0** : when motor is not moving. It could be motor have completed its no. or steps of its state being stopped using ```setStateStop()```.

<br>

- _Set States of motor_

```cpp
  myStepper.setStateContinue() // to start motor
  ```
```cpp
   myStepper.setStateStop() // to pause moving motor
   ```

<br>

#### 3. Revolutions
> Set no. of revolutions perform by the motor.

**Methods()**
- set revolution
    
  ```cpp
  myStepper.setRevolution(int no_of_Revolutions);
  ```

- set revolution and put motor in continue state.
  ```cpp
  myStepper.setRevolutionAndContinue(int no_of_Revolutions);
  ```

- get number of revolutions left by the motor.
  ```cpp
  myStepper.getRevolutionLeft();
  ```
  **note**: directions of motor will depend on the value in the arguments i.e -ve value will lead to counter-clockwise direction, while +ve will lead motor to clockwise direction. also, motor direction could be controlled dynamically by using Direction methods stated further in the documentation.

  <br>

  **Returns**
  **double (datatype value)** : no of revolutions left is **_no_of_steps_left / no_of_steps_in_1_revolution_**.

  <br>
  
<br>


#### 4. Angle
>Set angle in degree to perform by stepper motor.


**Methods()**
- set angle
  ```cpp
  myStepper.setAngle(int degree);
  ```
- set angle and put motor in continue state.
  ```cpp
  myStepper.setAngleAndContinue(int degree);
  ```
- get no of degree left that needs to perfomed by the motor.
  ```cpp
  myStepper.getAngleLeft();
  ```
  **Returns**
  no. of angle in degree left in **double datatype** from setAngle() or setAngleAndContinue().

<br>

#### 5. Steps
>Set steps to be perform by stepper motor.


**Methods()**
- set steps
  ```cpp
  myStepper.setSteps(int no_of_steps);
  ```
- set steps and put motor in continue state.
  ```cpp
  myStepper.setStepsAndContinue(int no_of_steps);
  ```
- get no of Steps left that needs to perfomed by the motor.
  (*__Note__ : ```myStepper.getStepsLeft();``` could be with revolutions or angle methods() too* )
  ```cpp
  myStepper.getStepsLeft();
  ```
  **Returns**
  **int (datatype value)**


<br>

#### 6. Perform stepping (motion)
>put stepper motor in to perfrom steps.

>**_Consider it like a car_**: you must first insert the keys, rotate the key to start the engine, and then accelerate the cars using the paddle. Similarly, you must first set the angle/revolutions or steps to be performed by the stepper motor, then put the motor in a continuous state, and then take steps (it could be async or sync depending on the method you use below).

**Methods()**
- **Synchronous** - Complete all the steps first. _note: it stops the below code/sketch functionality._
  
  example:
  ```cpp
  
  ```

- **Asynchronous** - used when you need to perform other operations in the code/sketch as well.
-  Take steps
  example:
  ```cpp
  
  ```

-  Take infinte steps.
  example:
  ```cpp
  
  ```

  all the async functions ***returns*** the state of the motor i.e 1 for continue state, 0 for stop/paused states
 

##### Example
get 
```cpp
 
```

<br>

#### 7. Directions
>Get or set stepper motor direction.

**Methods()**
- set direction
  ```cpp
  code.code();
  ```
 
- get direction
  ```cpp
  code.code();
  ```
  
  **Returns**
  **return 1** : explain
 

#### 7. Calculation helpers
>perfrom various calculation using convertors provided it the library.

**Methods()**
- degree to steps
  ```cpp
  code.code();
  ```
  
  **Returns**
  **return 1** : explain
 
- steps to degree
  ```cpp
  code.code();
  ```
  
  **Returns**
  **return 1** : explain
 

##### Example
get 
```cpp
 
```
emergency stop - on pressing button stop motor
change direction after one revolution
working without stopping below code functionality 
working with two or more motors at same time
start motor 2 steps after motor 1 completed its steps.

