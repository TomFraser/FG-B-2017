from math import sin, cos, radians as rad


out = "[{0}]"
addto = ""
numSensors = 20

for i in range(0, 360, 18):
    temp = "[{0}, {1}],\n"
    addto += temp.format(sin(rad(i)), cos(rad(i)))

print(out.format(addto))
