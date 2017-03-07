#FG&B 2017

###Welcome to FG&B 2017

## Notable Achievements for 2017

##### Regionals:

##### States:

##### Nationals:

----------



![FG&B Logo](../images/FG&BFooter.png)

-----------------------

##### 

#### Documentation written by Thomas Fraser & Alistair English

[FG&B Website](fgb.bbcrobotics.org)

[Brisbane Boys college, Queensland Australia](bbc.qld.edu.au)



-----



# Buzzer

#### Contains (.h)

The Buzzer library is used to control an analog buzzer build into FG&B's 2017 robots.

To use the library, import it to your main c++ file

```c++
#include <buzzer.h>
```

To declare the buzzer

```c++
Buzzer audio = Buzzer();
```

To use the buzzer call the method

```c++
audio.playTone(200);
```



# Compass

#### Contains (.h, .cpp)

The Compass library is use to control the MPU9250 Compass, Gyro and Accelerometer package.

To use the library, import it into your main c++ file

```c++
#include <Compass.h>
```

To declare the compass

```c++
Compass compass = Compass();
```

To use the compass call these methods

```c++
compass.getUpdate();
double heading = compass.getFinalHeading();
```



# Config

#### Contains (.h)



## Config.h

Config contains configurable constants useful for modifying the behaviour of the robot.

## Defines.h

Defines contains set constants that shouldn't need to be changed

## Pins.h

Pins contains the constant definitions of pins for the teensy micro-controller.

To use these libraries import them using

```c++
#include <Config.h>
#include <Defines.h>
#include <Pins.h>
```



# Direction Controller

#### Contains (.h, .cpp)

The direction controller controls all all directional movement via four motors.

To use the library, import it into your main c++ file

```c++
#include <DirectionController.h>
```

To declare the direction controller

```c++
DirectionController direction = DirectionController();
```

To use primary methods

```c++
direction.calcMotors(angle, rotation);
//or
direction.calcMotors(angle, rotation, orbitNum);
//or
direction.setPWM(value/*-255 - 255*/)
```

