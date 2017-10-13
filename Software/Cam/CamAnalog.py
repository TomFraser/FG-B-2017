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


#SPI
spi = pyb.SPI(2, pyb.SPI.SLAVE, polarity=0, phase=0)
#pin = pyb.Pin("P3", pyb.Pin.IN, pull=pyb.Pin.PULL_UP)
print("Waiting for Arduino...")

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

    #If not seeing ball, angle = 65506, else calculate ball angle
    if strength == 0:
        angle = 65506
    else:
        angle = float((atan2(y,x) * (180 / pi) - 90)%360)

    if angle == 0: angle = 360

    ##### Communication ######
    send = int((255/360)*angle)
    dac.write(send)
    #print(angle)
    #Prints
    #print("Angle:")
    #print(angle)
    #print()
    #print("Strength:")
    #print(strength)
    #print()
    #print("Orbit Angle:")
    #print(orbitAngle)
    print(clock.fps())

################# TEENSY CODE ####################
#   int val = analogRead(A2);
#   float direction = val * 0.3515625;
#   Serial.println(direction);
