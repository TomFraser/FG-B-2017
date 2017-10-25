#turtle imports
from turtle import *
from math import sin, cos, radians as rad

#turtle setup
screen = Screen()
# tracer(0, 0)
penup()
# hideturtle()
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
                [0.9510565162951535, -0.3090169943749476],
                ]

sensor_color = {0:"grey", 1:"red"}
sensor_size = 20

# sensor_data = [0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

def updateSensorVals(x, y):
    print(x, y)
    for sensor_num in range(len(sensor_coords)):
        coords = sensor_coords[sensor_num]
        coords[0] *= radius
        coords[1] *= radius
        if(coords[0]-sensor_size <= x <= coords[0]+sensor_size and coords[1]-sensor_size <= y <= coords[1]+sensor_size):
            #clicked in the button
            sensor_data[sensor_num] = int(not sensor_data[sensor_num])
    updateScreen()
    return

def updateScreen():
    clear()
    for sensor_num in range(len(sensor_coords)):
        coords = sensor_coords[sensor_num]
        goto(coords[0]*radius, coords[1]*radius)
        dot(sensor_size, sensor_color[sensor_data[sensor_num]])
    update()

onscreenclick(updateSensorVals)
updateScreen()
# sensor_data = [0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
# updateScreen()
mainloop()
