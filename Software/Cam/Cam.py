import sensor, image, time, math, pyb
from pyb import SPI, Pin, LED, delay, ExtInt
from math import atan2, sqrt, pi

#Ball Thresholds
thresholds = [(55, 83, 0, 22, 44, 127)]

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
#Init Bus as Slave
#spi = SPI(2, SPI.SLAVE, baudrate=600000, polarity=1, phase=0, crc=0x7)

#spi.init(SPI.SLAVE, )

#Interupt Function
#def spiSend():
#    print("called")
#    spi.send(52,timeout=200)

#Attach Interupt
#Interupt = ExtInt(Pin('P4'), pyb.ExtInt.IRQ_FALLING, pyb.Pin.PULL_UP, spiSend)



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
sensor.skip_frames(time = 500) #Start Delay
sensor.set_auto_gain(False) #Must remain false for blob tracking
sensor.set_auto_whitebal(False) #Must remain false for blob tracking
clock = time.clock()

#LED's all turn off after boot up is done
ledRed.off()
ledGreen.off()
ledBlue.off()

#Main Loop
while(True):
    clock.tick()

    #Reset Variables
    x = 0
    y = 0
    strength = 0

    #Find Ball
    img = sensor.snapshot()
    for blob in img.find_blobs([thresholds[0]], pixels_threshold=10, area_threshold=10, merge=True):
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

    #Prints
    print("Angle:")
    print(angle)
    print()
    print("Strength:")
    print(strength)
    print()
    print("Orbit Angle:")
    print(orbitAngle)
    print(clock.fps())
