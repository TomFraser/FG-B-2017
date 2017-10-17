import sensor, machine, pyb, utime
from pyb import *

spi = SPI(2)
spi.init(SPI.MASTER, firstbit=SPI.MSB, baudrate=600000, polarity=0, phase=0)

csPin = Pin('P3', Pin.OUT_PP)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames()

while(True):
    img = sensor.snapshot()

    csPin.value(0)
    pyb.delay(1)
    spi.send(85)
    print("sent")
    pyb.delay(1)
    csPin.value(1)

    pyb.delay(500)


