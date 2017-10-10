import sensor, image, time, math, pyb
from pyb import SPI, Pin, LED, delay, ExtInt, I2C
import ustruct
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

#I2C Stuff
i2c = pyb.I2C(2, pyb.I2C.MASTER, baudrate=20000)

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

#Image Sensor Stuff
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
sensor.skip_frames(time = 3000) #Start Delay
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
        x = -(blob.cx() - 80)
        y = blob.cy() - 60
        strength = sqrt(x*x + y*y) #Calculate Ball Distance

    #If not seeing ball, angle = 65506, else calculate ball angle
    if strength == 0:
        angle = 65506
    else:
        angle = (atan2(y,x) * (180 / pi) - 90)%360

    orbitAngle = calcOrbit(angle, strength)
    try:
        i2c.send(int(orbitAngle), timeout=100, addr=0x01)
    except OSError as err:
        print(err.args[0])

    #Prints
    #print("Angle:")
    #print(angle)
    #print()
    #print("Strength:")
    #print(strength)
    #print()
    #print("Orbit Angle:")
    #print(orbitAngle)
    #print(clock.fps())
