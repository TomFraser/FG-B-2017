import sensor, image, time, math, pyb
from pyb import SPI, Pin, LED

#Ball Thresholds
thresholds = [(20, 30, 14, 31, 21, 45)]

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
    ledRed.off()

#Attach Interupt
Interupt = pyb.ExtInt(Pin('P3'), pyb.ExtInt.IRQ_FALLING, pyb.Pin.PULL_NONE, spiSend)

spi.init(SPI.SLAVE)
Interupt.enable()

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

ledRed.off()
ledGreen.off()
ledBlue.off()

while(True):
    clock.tick()

    x = 0
    y = 0
    strength = 0

    img = sensor.snapshot()
    for blob in img.find_blobs([thresholds[0]], pixels_threshold=20, area_threshold=20, merge=True):
        img.draw_cross(blob.cx(), blob.cy())
        x = -(blob.cx() - 80)
        y = blob.cy() - 60
        strength = math.sqrt(x*x + y*y)

    calcAngle = (math.atan2(y,x) * (180 / math.pi) - 90)%360

    if strength == 0:
        angle = 65506
    else:
        angle = calcAngle

    print("angle:")
    print(angle)
    print()
    print("strength")
    print(strength)
    print()
    print(clock.fps())
