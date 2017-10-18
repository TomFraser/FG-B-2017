import sensor, image, time, math, pyb
from pyb import *
import ustruct, utime
from math import atan2, sqrt, pi, log

#Thresholds     Ball                   Goal 1 (Attack)  Goal 2 (Defend)
thresholds = [(81, 38, 35, 63, -25, 69),(0,0,0,0,0,0),(0,0,0,0,0,0)]

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
ORBIT_SIDE_RATIO = 50
ORBIT_FORWARD_LOWER = 90
ORBIT_FORWARD_UPPER = 270
STRENGTH_MAX = 61


#Orbit Function
def calcOrbit(ang, strength):
    if strength < strengthThreshold or ang == 65506 or strength == 0:
        return ang
    elif ang < ORBIT_FORWARD_LOWER:
        return ang + (ang / ORBIT_FRONT_DENOMINATOR) * ORBIT_FRONT_RATIO * (STRENGTH_MAX/strength)**5
    elif ang > ORBIT_FORWARD_UPPER:
        return ang - ((360 - ang) / ORBIT_FRONT_DENOMINATOR) * ORBIT_FRONT_RATIO * (STRENGTH_MAX/strength)**5
    elif ang <= 180:
        return ang + ORBIT_SIDE_RATIO * (STRENGTH_MAX/strength)**5
    elif ang > 180:
        return ang - ORBIT_SIDE_RATIO * (STRENGTH_MAX/strength)**5
    else:
        return 65506

#UART Init
uart = UART(3, 9600)

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
        angle = (atan2(y,x) * (180 / pi) - 90)%360

    #If not seeing ball, angle = 65506, else calculate ball angle
    if strength == 0:
        angle = 500

    if angle == 0: angle = 360

    ballData = [calcOrbit(angle, strength), strength]

    goal1Data = [1,2]
    goal2Data = [3,4]



    ##### Create Buffer to Send over Serial #####

    sendBuff = [42,0,0,0,0,0,0,0,0,72]
    sendBuff[0] = 42
    sendBuff[9] = 72

    if ballData[0] <= 255:
        sendBuff[1] = int(ballData[0])
        sendBuff[2] = 0
    else:
        sendBuff[1] = 255
        sendBuff[2] = int(ballData[0] % 255)

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

    print(sendBuff)

    pyb.delay(1)

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
