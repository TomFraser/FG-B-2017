# Cam - By: Thomas - Fri Sep 8 2017
from pyb import SPI
from machine import Pin
import sensor

interruptPin = Pin(0, Pin.IN)

interruptPin.irq(trigger=Pin.IQR_FALLING, handler=hasSPIRequest)

spi = SPI(1, SPI.SLAVE, baudrate=600000, polarity=1, phase=0, crc=None)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames()

def getBallDirection(input=None):
    if input == None:
        return ballLoc
    else:
        #Do some cheeky calulation stuff
        ballLoc = input

def hasSPIRequest():
    ballDirection = getBallDirection()
    spi.send(ballDirection, timeout=100)

while(True):
    img = sensor.snapshot()
    for block in img.find_blobs([ball_thresholds]):
        ballCentre = [b.cx(), b.cy()]
        getBallDirection(input=ballCentre)
