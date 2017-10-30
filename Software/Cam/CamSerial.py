import sensor, image, time, math, pyb
from pyb import *
import ustruct, utime
from math import atan2, sqrt, pi, log

#Thresholds
thresholds = [(12, 65, 16, 76, 16, 58), #Ball
(36, 51, -12, 21, 3, 44), #Goal 1
(0,0,0,0,0,0)] # Goal 2

#LED's
ledRed = LED(1)
ledRed.off()
ledGreen = LED(2)
ledGreen.off()
ledBlue = LED(3)
ledBlue.off()
ledIR = LED(4)
ledIR.off()

global lastTime
global currentTime
lastTime = 500
ledRed.on()

def blink():
    global lastTime
    global currentTime
    currentTime = pyb.millis()
    if currentTime > (lastTime):
        ledGreen.toggle()
        lastTime = currentTime + 500

#UART Init
uart = UART(3, 9600, timeout_char=1000)

#Image Sensor Stuff
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) #Resolution, QVGA = 42FPS,QQVGA = 85FPS
sensor.skip_frames(time = 1000) #Start Delay
sensor.set_auto_gain(False) #Must remain false for blob tracking
sensor.set_auto_whitebal(False) #Must remain false for blob tracking
sensor.set_contrast(3)
clock = time.clock()

#LED's all turn off after boot up is done
ledRed.off()
ledGreen.off()
ledBlue.off()

#Main Loop
while(True):
    clock.tick()
    blink()

    #Reset Variables
    x = 0
    y = 0
    strength = 0
    Goal1size = 0
    Goal2size = 0

    #Find Ball
    img = sensor.snapshot()



    for ball in img.find_blobs([thresholds[0]], x_stride=2, y_stride=2, area_threshold=1, pixel_threshold=1, merge=False):
        img.draw_cross(ball.cx(), ball.cy())
        x = -(ball.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
        y = ball.cy() - (img.height() / 2)
        angle = (atan2(y,x) * (180 / pi) - 90)%360
        strength = sqrt(x**2 + y**2)

    for goal in img.find_blobs(thresholds, x_stride=10, y_stride=10, area_threshold=50, pixel_threshold=50, merge=True):
        x = -(goal.cx() - (img.width() / 2)) #Calculate Coordinates of Ball
        y = goal.cy() - (img.height() / 2)
        s = sqrt(goal.pixels())
        if goal.code() == 2 and s > 10: #2^1
            img.draw_rectangle(goal.rect())
            img.draw_cross(goal.cx(), goal.cy())
            Goal1size =  sqrt(goal.pixels())
            Goal1angle = (atan2(y,x) * (180 / pi) - 90)%360

        if goal.code() == 4 and s > 10: #2^2
            img.draw_cross(goal.cx(), goal.cy())
            Goal2size =  sqrt(goal.pixels())
            Goal2angle = (atan2(y,x) * (180 / pi) - 90)%360

    #If not seeing ball, angle = 65506, else calculate ball angle
    if strength == 0: angle = 500
    if angle == 0: angle = 360
    if Goal1size == 0: Goal1angle = 500
    if Goal2size == 0: Goal2angle = 500

    ballData = [angle, strength]
    goal1Data = [Goal1angle,int(Goal1size)]
    goal2Data = [Goal2angle,int(Goal2size)]

    #print(Goal1size)



    ##### Create Buffer to Send over Serial #####

    sendBuff = [42,0,0,0,0,0,0,0,0,72]
    sendBuff[0] = 42
    sendBuff[9] = 72

    if angle <= 255:
        sendBuff[1] = int(angle)
        sendBuff[2] = 0
    else:
        sendBuff[1] = 255
        sendBuff[2] = int(angle % 255)

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
    for buf in sendBuff:
        while True:
            try:
                uart.writechar(buf)
                break
            except Exception as e:
                print(e)
                pass

    # uart.writechar(sendBuff[0])
    # uart.writechar(sendBuff[1])
    # uart.writechar(sendBuff[2])
    # uart.writechar(sendBuff[3])
    # uart.writechar(sendBuff[4])
    # uart.writechar(sendBuff[5])
    # uart.writechar(sendBuff[6])
    # uart.writechar(sendBuff[7])
    # uart.writechar(sendBuff[8])
    # uart.writechar(sendBuff[9])

    print(sendBuff)

    pyb.delay(1)

    #Prints
    #print("Angle:")
    #print(angle)
    #print(angleOrbit)
    #print()
    #print("Strength:")
    #print(strength)
    #print()
    #print("Orbit Angle:")
    #print(orbitAngle)
    #print(clock.fps())
