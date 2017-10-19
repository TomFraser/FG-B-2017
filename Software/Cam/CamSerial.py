import sensor, image, time, math, pyb
from pyb import *
import ustruct, utime
from math import atan2, sqrt, pi, log

#Thresholds
thresholds = [(32, 43, -4, 19, 10, 11), #Ball
(27, 73, 15, 64, 8, 35), #Goal 1
(0,0,0,0,0,0)] # Goal 2

#LED's
ledRed = LED(1)
ledRed.on()
ledGreen = LED(2)
ledGreen.on()
ledBlue = LED(3)
ledBlue.on()
ledIR = LED(4)
ledIR.off()



#Orbit Constants
strengthThreshold = 40
ORBIT_FRONT_DENOMINATOR = 120
ORBIT_FRONT_RATIO = 90
ORBIT_SIDE_RATIO = 75
ORBIT_FORWARD_LOWER = 90
ORBIT_FORWARD_UPPER = 270
STRENGTH_MAX = 51


#Orbit Function
def calcOrbit(ang, stre):
    if stre < strengthThreshold or ang == 65506 or stre == 0:
        return ang
    elif ang < ORBIT_FORWARD_LOWER:
        return ang + (ang / ORBIT_FRONT_DENOMINATOR) * ORBIT_FRONT_RATIO
    elif ang > ORBIT_FORWARD_UPPER:
        return ang - ((360 - ang) / ORBIT_FRONT_DENOMINATOR) * ORBIT_FRONT_RATIO
    elif ang <= 180:
        return ang + ORBIT_SIDE_RATIO
    elif ang > 180:
        return ang - ORBIT_SIDE_RATIO
    else:
        return 65506

#UART Init
uart = UART(3, 256000)

#Image Sensor Stuff
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
sensor.skip_frames(time = 500) #Start Delay
sensor.set_auto_gain(False) #Must remain false for blob tracking
sensor.set_auto_whitebal(True) #Must remain false for blob tracking
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
    Goal1size = 0
    Goal2size = 0

    #Find Ball
    img = sensor.snapshot()

    for blob in img.find_blobs(thresholds, x_stride=2, y_stride=2, merge=False):
        img.draw_cross(blob.cx(), blob.cy())
        x = -(blob.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
        y = blob.cy() - (img.height() / 2)
        if blob.code() == 1: #2^0
            strength = sqrt(x*x + y*y) #Calculate Ball Distance
            angle = (atan2(y,x) * (180 / pi) - 90)%360
        if blob.code() == 2: #2^1
            Goal1size = blob.area()
            Goal1angle = (atan2(y,x) * (180 / pi) - 90)%360
        if blob.code() == 4: #2^2
            Goal2size = blob.area()
            Goal2angle = (atan2(y,x) * (180 / pi) - 90)%360

    #If not seeing ball, angle = 65506, else calculate ball angle
    if strength == 0: angle = 500
    if angle == 0: angle = 360
    if Goal1size == 0: Goal1angle = 500
    if Goal2size == 0: Goal2angle = 500

    angleOrbit = calcOrbit(angle,strength)

    ballData = [angleOrbit, strength]
    goal1Data = [Goal1angle,Goal2size]
    goal2Data = [Goal2angle,Goal2size]



    ##### Create Buffer to Send over Serial #####

    sendBuff = [42,0,0,0,0,0,0,0,0,72]
    sendBuff[0] = 42
    sendBuff[9] = 72

    if angleOrbit <= 255:
        sendBuff[1] = int(angleOrbit)
        sendBuff[2] = 0
    else:
        sendBuff[1] = 255
        sendBuff[2] = int(angleOrbit % 255)

    if goal1Data[0] <= 255:
        sendBuff[3] = int(goal1Data[0])
        sendBuff[4] = 0
    else:
        sendBuff[3] = 255
        sendBuff[4] = int(goal1Data[0] % 255)

    sendBuff[5] = goal1Data[1]

    if goal2Data[0] <= 255:
        sendBuff[6] = int(goal2Data[0])
        sendBuff[7] = 0
    else:
        sendBuff[6] = 255
        sendBuff[7] = int(goal2Data[0] % 255)

    sendBuff[8] = goal2Data[1]

    for i in range(0,10):
        if sendBuff[i] == 42 and i != 0:
            sendBuff[i] = 43

    ##### Send Buffer Over Serial #####
    uart.writechar(sendBuff[0])
    uart.writechar(sendBuff[1])
    uart.writechar(sendBuff[2])
    uart.writechar(sendBuff[3])
    uart.writechar(sendBuff[4])
    uart.writechar(sendBuff[5])
    uart.writechar(sendBuff[6])
    uart.writechar(sendBuff[7])
    uart.writechar(sendBuff[8])
    uart.writechar(sendBuff[9])

    #print(sendBuff)

    pyb.delay(1)

    #Prints
    print("Angle:")
    print(angle)
    print(angleOrbit)
    #print()
    #print("Strength:")
    #print(strength)
    #print()
    #print("Orbit Angle:")
    #print(orbitAngle)
    #print(clock.fps())
