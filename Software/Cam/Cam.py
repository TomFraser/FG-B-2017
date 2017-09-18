import sensor, image, time, math
threshold_index = 0
thresholds = [(36, 69, 39, 89, 9, 43),
              (30, 100, -64, -8, -32, 32),
              (0, 30, 0, 64, -128, 0)]
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
while(True):
    clock.tick()
    x = 0
    y = 0
    strength = 0
    angle = 0
    img = sensor.snapshot()
    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=20, area_threshold=20, merge=True):
        img.draw_cross(blob.cx(), blob.cy())
        x = -(blob.cx() - 160)
        y = blob.cy() - 120
        strength = math.sqrt(x*x + y*y)
    angle = math.atan2(y,x) * (180 / math.pi) - 90
    angle = angle%360
    print("angle:")
    print(angle)
    print()
    print("strength")
    print(strength)
    print()
    print(clock.fps())
