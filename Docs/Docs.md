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

To declare the buzzer object

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

To declare the compass object

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

To declare the direction controller object

```c++
DirectionController direction = DirectionController();
```

To use primary methods

```c++
direction.calcMotors(angle, rotation);
//or
direction.calcMotors(angle, rotation, orbitNum);
//or
direction.setPWM(value/*-255 - 255*/);
```



# FGB Common

#### Contains (.h)

The FGB Common header contains methods that are being globally used across multiple libraries and methods that don't belong to a class

To use the library, import it into your main c++ file

```c++
#include <fgbcommon.h>
```



# Kicker

#### Contains (.h)

The Kicker libary controls the actions of the solenoid and lightgate on each robot

To use the library, import it into your main c++ file

```c++
#include <Kicker.h>
```

To call the constructor and declare the kicker object

```c++
Kicker kicker = Kicker();
```

To use the kicker, the lightgate must first be triggered, then the code checks if the delay between kicks it long enough (this is to allow the caps for the solenoid to charge). If both criteria are met, the solenoid will kick.

```c++
kicker.kickerReady();
kicker.checkLightGate();
kicker.kick();
```



# Light

#### Contains (.h, .cpp)

The Light library controls all 20 lightsensors on the botom of the robot and keeps us from going out over the white line.

To use the Light library, import it into your main c++ file

```c++
#include <Kicker.h> //Do I really need to keep doing this for each libaray or do you get the jist?
```

To delcare the Light object

```c++
Light lightsensors = Light();
```

To be completely honest, the other programmer not writing this (Alistair) wrote the lightsensor code and the programmer writing this (Tom) has no damn idea how it works.



# Motor

#### Contains (.h, .cpp)

The motor library controls our 4 Maxon DCX Motors using the LMD18200T motor control chip

To use the Motor ibaray, import it into your main c++ file

```c++
#include <Motor.h>
```

To declare the Motor object

```c++
Motor motorA = Motor(pwm_pin, brk_pin, dir_pin, isRev);
Motor motorB = Motor(pwm_pin, brk_pin, dir_pin, isRev);
Motor motorC = Motor(pwm_pin, brk_pin, dir_pin, isRev);
Motor motorD = Motor(pwm_pin, brk_pin, dir_pin, isRev);
```

To use the motors

```c++
motorA.set(pwm_value);
//or
motorA.brake();
```



# Read TSOPs

#### Contains (.h, .cpp)

The Read TSOPs library reads and controls our TSOP infared sensors

To use the Read TSOPs library, import it into your main c++ file

```c++
#include <ReadTSOPS.h>
```

To declare the TSOP object

```c++
ReadTSOPS tsops;
```

To use the TSOPS

```c++
tsops.read();
//or
tsops.moveTangent();
```



# Rotation Controller

#### Contains (.h, .cpp)

The Rotation Controller library handles all rotational (non directional) movement

To use the Rotation Controller libaray, import it into your main c++ file

```c++
#include <RotationController.h>
```

To declare the Rotation Controller object

```c++
RotationController rotation = RoationController();
```

Unfortunately the Rotation Controller contains code that is very specific to our robots (being the compass MPU9250 and Pixy Camera) so I wont provide any sample use.

---

