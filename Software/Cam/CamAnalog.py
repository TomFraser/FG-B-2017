import sensor, image, time, math, pyb
from pyb import *
import ustruct, utime
from math import atan2, sqrt, pi, log

#Ball Thresholds
thresholds = [(81, 38, 35, 63, -25, 69)]

#LED's
ledRed = LED(1)
ledRed.on()
ledGreen = LED(2)
ledGreen.on()
ledBlue = LED(3)
ledBlue.on()
ledIR = LED(4)
ledIR.off()

#SPI Stuff


#Orbit Constants
strengthThreshold = 40
ORBIT_FRONT_DENOMINATOR = 120
ORBIT_FRONT_RATIO = 90
ORBIT_SIDE_RATIO = 50
ORBIT_FORWARD_LOWER = 90
ORBIT_FORWARD_UPPER = 270


#Orbit Function
def calcOrbit(angle, strength):
    if strength > strengthThreshold or angle == 65506:
        return angle
    elif angle < ORBIT_FORWARD_LOWER:
        return angle + (angle / ORBIT_FRONT_DENOMINATOR) * ORBIT_FRONT_RATIO
    elif angle > ORBIT_FORWARD_UPPER:
        return angle - ((360 - angle) / ORBIT_FRONT_DENOMINATOR) * ORBIT_FRONT_RATIO
    elif angle <= 180:
        return angle + ORBIT_SIDE_RATIO
    elif angle > 180:
        return angle - ORBIT_SIDE_RATIO
    else:
        return 65506

#Analog
dac = DAC("P6")
digital1 = Pin("P0", pyb.Pin.OUT_PP)
digital2 = Pin("P1", pyb.Pin.OUT_PP)

#Image Sensor Stuff
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
sensor.skip_frames(time = 500) #Start Delay
sensor.set_auto_gain(False) #Must remain false for blob tracking
sensor.set_auto_whitebal(False) #Must remain false for blob tracking
clock = time.clock()

#LED's all turn off after boot up is done
ledRed.off()
ledGreen.off()
ledBlue.on()

#Main Loop
while(True):
    clock.tick()

    #Reset Variables
    x = 0
    y = 0
    strength = 0

    #Find Ball
    img = sensor.snapshot()

    for blob in img.find_blobs([thresholds[0]], pixels_threshold=2, area_threshold=2, merge=True):
        img.draw_cross(blob.cx(), blob.cy())
        x = -(blob.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
        y = blob.cy() - (img.height() / 2)
        strength = sqrt(x*x + y*y) #Calculate Ball Distance

    img.draw_cross(int(img.width() / 2), int(img.height() / 2))
    #If not seeing ball, angle = 65506, else calculate ball angle
    angle = float((atan2(y,x) * (180 / pi) - 90)%360)

    if strength == 0:
        digital1.value(0)
        digital2.value(0)
        mode = 0
    elif angle < 180:
        digital1.value(1)
        digital2.value(0)
        mode = 1
    elif angle > 180 and angle < 360:
        digital1.value(0)
        digital2.value(1)
        mode = 2
    else:
        digital1.value(0)
        digital2.value(0)
        mode = 0


    ##### Communication ######
    send = int((1.422222222222222)*(angle))
    dac.write(send)

    #Prints
    print("Angle:")
    print(angle)
    print()
    #print("Strength:")
    #print(strength)
    #print()
    print("Mode:")
    print(mode)
    #print("Orbit Angle:")
    #print(orbitAngle)
    #print(clock.fps())

################# TEENSY CODE ####################
#   int val = analogRead(A2);
#   float direction = val * 0.3515625;
#   Serial.println(direction);
