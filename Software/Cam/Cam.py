import sensor, image, time, math, pyb
from pyb import SPI, Pin, LED, delay
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
spi = SPI(2, SPI.SLAVE, baudrate=600000, polarity=1, phase=0, crc=0x7)

#Interupt Function
def spiSend():
    ledRed.on()
    recv = spi.recv()
    spi.send(angle,timeout=200)
    delay(100)
    ledRed.off()

#Attach Interupt
Interupt = pyb.ExtInt(Pin('P3'), pyb.ExtInt.IRQ_FALLING, pyb.Pin.PULL_NONE, spiSend)

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

    #Prints
    print("angle:")
    print(angle)
    print()
    print("strength")
    print(strength)
    print()
    print(clock.fps())
