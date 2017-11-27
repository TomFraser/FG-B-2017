# serial imports
import serial
import serial.tools.list_ports

#turtle imports
from turtle import *
from math import sin, cos, radians as rad

for port in serial.tools.list_ports.comports():
    print(port)

device = "/dev/ttyACM" + input("Device name: /dev/ttyACM")

teensy = serial.Serial(device)

# send connection
teensy.write(bytes([200]))

#turtle setup
screen = Screen()
tracer(False)
penup()
hideturtle()
pensize(10)

#sensordata
sensor_data = [0 for i in range(20)]

#radius of circle
radius = 200

sensor_coords = [[1.0,0.0],
                [0.9510565162951535, 0.3090169943749474],
                [0.8090169943749475, 0.5877852522924731],
                [0.587785252292473, 0.8090169943749475],
                [0.30901699437494745, 0.9510565162951535],
                [0.0, 1.0],
                [-0.30901699437494756, 0.9510565162951535],
                [-0.587785252292473, 0.8090169943749475],
                [-0.8090169943749473, 0.5877852522924732],
                [-0.9510565162951535, 0.3090169943749475],
                [-1.0, 0.0],
                [-0.9510565162951536, -0.3090169943749473],
                [-0.8090169943749472, -0.5877852522924734],
                [-0.5877852522924732, -0.8090169943749473],
                [-0.30901699437494756, -0.9510565162951535],
                [0.0, -1.0],
                [0.30901699437494723, -0.9510565162951536],
                [0.5877852522924737, -0.809016994374947],
                [0.8090169943749473, -0.5877852522924734],
                [0.9510565162951535, -0.3090169943749476]]

sensor_color = {0:"grey", 1:"red"}
sensor_size = 20




while True:
    data = teensy.readline()
    clear()

    try:
        data = float(data)
        if(data != 65506):
            print(data)
            data = (90-data)%360
            data = rad(data)
            penup()
            goto(0, 0)
            pendown()
            goto(radius * cos(data), radius * sin(data))
            penup()
    except ValueError:
        try:
            #not an angle number - must be sensor data
            sensor_data = [int(i) for i in data.decode("utf-8").split()]
        except ValueError:
            #if serial shat itself
            pass



    try:
        for sensor_num in range(len(sensor_coords)):
            coords = sensor_coords[sensor_num]
            goto(coords[0]*radius, coords[1]*radius)
            dot(sensor_size, sensor_color[sensor_data[sensor_num]])
    except KeyError:
        # print("key error") #if the serial fucks up dont wanna break shit
        pass
    except IndexError:
        # print("index error")
        pass

    update()
