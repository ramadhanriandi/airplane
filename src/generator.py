def generate(vertex_temp,file_output):
    file_output.write(str(vertex_temp[0][0])+","+str(vertex_temp[0][1])+","+str(vertex_temp[0][2])+",")
    file_output.write(str(vertex_temp[1][0])+","+str(vertex_temp[1][1])+","+str(vertex_temp[1][2])+",")
    file_output.write(str(vertex_temp[2][0])+","+str(vertex_temp[2][1])+","+str(vertex_temp[2][2])+",")
    file_output.write(str(vertex_temp[3][0])+","+str(vertex_temp[3][1])+","+str(vertex_temp[3][2])+",")

    file_output.write(str(vertex_temp[0][0])+","+str(vertex_temp[0][1])+","+str(vertex_temp[0][2])+",")
    file_output.write(str(vertex_temp[1][0])+","+str(vertex_temp[1][1])+","+str(vertex_temp[1][2])+",")
    file_output.write(str(vertex_temp[5][0])+","+str(vertex_temp[5][1])+","+str(vertex_temp[5][2])+",")
    file_output.write(str(vertex_temp[4][0])+","+str(vertex_temp[4][1])+","+str(vertex_temp[4][2])+",")

    file_output.write(str(vertex_temp[2][0])+","+str(vertex_temp[2][1])+","+str(vertex_temp[2][2])+",")
    file_output.write(str(vertex_temp[3][0])+","+str(vertex_temp[3][1])+","+str(vertex_temp[3][2])+",")
    file_output.write(str(vertex_temp[7][0])+","+str(vertex_temp[7][1])+","+str(vertex_temp[7][2])+",")
    file_output.write(str(vertex_temp[6][0])+","+str(vertex_temp[6][1])+","+str(vertex_temp[6][2])+",")

    file_output.write(str(vertex_temp[0][0])+","+str(vertex_temp[0][1])+","+str(vertex_temp[0][2])+",")
    file_output.write(str(vertex_temp[3][0])+","+str(vertex_temp[3][1])+","+str(vertex_temp[3][2])+",")
    file_output.write(str(vertex_temp[7][0])+","+str(vertex_temp[7][1])+","+str(vertex_temp[7][2])+",")
    file_output.write(str(vertex_temp[4][0])+","+str(vertex_temp[4][1])+","+str(vertex_temp[4][2])+",")

    file_output.write(str(vertex_temp[1][0])+","+str(vertex_temp[1][1])+","+str(vertex_temp[1][2])+",")
    file_output.write(str(vertex_temp[2][0])+","+str(vertex_temp[2][1])+","+str(vertex_temp[2][2])+",")
    file_output.write(str(vertex_temp[6][0])+","+str(vertex_temp[6][1])+","+str(vertex_temp[6][2])+",")
    file_output.write(str(vertex_temp[5][0])+","+str(vertex_temp[5][1])+","+str(vertex_temp[5][2])+",")

    file_output.write(str(vertex_temp[4][0])+","+str(vertex_temp[4][1])+","+str(vertex_temp[4][2])+",")
    file_output.write(str(vertex_temp[5][0])+","+str(vertex_temp[5][1])+","+str(vertex_temp[5][2])+",")
    file_output.write(str(vertex_temp[6][0])+","+str(vertex_temp[6][1])+","+str(vertex_temp[6][2])+",")
    file_output.write(str(vertex_temp[7][0])+","+str(vertex_temp[7][1])+","+str(vertex_temp[7][2])+",")


counter = 0
vertex_temp = []
file_output = open("plane.c", "w")
file_output.write('#include "plane.h"')
file_output.write('extern const float planePositions[576]) = ')
file_output.write('{')
with open("input.txt") as f:
    for line in f:
        line = line.rstrip()
        if line == "//":
            continue
        if counter == 0:
            vertex_temp = []
            counter += 1
            vertex_temp.append([float(x) for x in line.split(',')])
        if (counter == 8):
            generate(vertex_temp, file_output)
            counter = 0
file_output.write('};')
file_output.close()
file_output2 = open("plane.h","w")
file_output2.write("extern const float planev2Positions[540];")
file_output2.close()