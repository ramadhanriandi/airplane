def generate(vertex_temp):
    file_output.writelines(str(vertex_temp[0][0])+","+str(vertex_temp[0][1])+","+str(vertex_temp[0][2])+",\n")
    file_output.writelines(str(vertex_temp[1][0])+","+str(vertex_temp[1][1])+","+str(vertex_temp[1][2])+",\n")
    file_output.writelines(str(vertex_temp[2][0])+","+str(vertex_temp[2][1])+","+str(vertex_temp[2][2])+",\n")
    file_output.writelines(str(vertex_temp[3][0])+","+str(vertex_temp[3][1])+","+str(vertex_temp[3][2])+",\n")

    file_output.writelines(str(vertex_temp[0][0])+","+str(vertex_temp[0][1])+","+str(vertex_temp[0][2])+",\n")
    file_output.writelines(str(vertex_temp[1][0])+","+str(vertex_temp[1][1])+","+str(vertex_temp[1][2])+",\n")
    file_output.writelines(str(vertex_temp[5][0])+","+str(vertex_temp[5][1])+","+str(vertex_temp[5][2])+",\n")
    file_output.writelines(str(vertex_temp[4][0])+","+str(vertex_temp[4][1])+","+str(vertex_temp[4][2])+",\n")

    file_output.writelines(str(vertex_temp[2][0])+","+str(vertex_temp[2][1])+","+str(vertex_temp[2][2])+",\n")
    file_output.writelines(str(vertex_temp[3][0])+","+str(vertex_temp[3][1])+","+str(vertex_temp[3][2])+",\n")
    file_output.writelines(str(vertex_temp[7][0])+","+str(vertex_temp[7][1])+","+str(vertex_temp[7][2])+",\n")
    file_output.writelines(str(vertex_temp[6][0])+","+str(vertex_temp[6][1])+","+str(vertex_temp[6][2])+",\n")

    file_output.writelines(str(vertex_temp[0][0])+","+str(vertex_temp[0][1])+","+str(vertex_temp[0][2])+",\n")
    file_output.writelines(str(vertex_temp[3][0])+","+str(vertex_temp[3][1])+","+str(vertex_temp[3][2])+",\n")
    file_output.writelines(str(vertex_temp[7][0])+","+str(vertex_temp[7][1])+","+str(vertex_temp[7][2])+",\n")
    file_output.writelines(str(vertex_temp[4][0])+","+str(vertex_temp[4][1])+","+str(vertex_temp[4][2])+",\n")

    file_output.writelines(str(vertex_temp[1][0])+","+str(vertex_temp[1][1])+","+str(vertex_temp[1][2])+",\n")
    file_output.writelines(str(vertex_temp[2][0])+","+str(vertex_temp[2][1])+","+str(vertex_temp[2][2])+",\n")
    file_output.writelines(str(vertex_temp[6][0])+","+str(vertex_temp[6][1])+","+str(vertex_temp[6][2])+",\n")
    file_output.writelines(str(vertex_temp[5][0])+","+str(vertex_temp[5][1])+","+str(vertex_temp[5][2])+",\n")

    file_output.writelines(str(vertex_temp[4][0])+","+str(vertex_temp[4][1])+","+str(vertex_temp[4][2])+",\n")
    file_output.writelines(str(vertex_temp[5][0])+","+str(vertex_temp[5][1])+","+str(vertex_temp[5][2])+",\n")
    file_output.writelines(str(vertex_temp[6][0])+","+str(vertex_temp[6][1])+","+str(vertex_temp[6][2])+",\n")
    file_output.writelines(str(vertex_temp[7][0])+","+str(vertex_temp[7][1])+","+str(vertex_temp[7][2])+",\n")


counter = 0
vertex_temp = []
file_output = open("plane.c", "w")
file_output.writelines('#include "plane.h"\n')
file_output.writelines('extern const float planePositions[576] = \n')
file_output.writelines('{')
with open("vertex.txt") as f:
    for line in f:
        line = line.rstrip()
        if line == "//":
            continue
        if counter == 0:
            vertex_temp = []
        vertex_temp.append([float(x.rstrip()) for x in line.split(',')])
        counter += 1
        if (counter == 8):
            generate(vertex_temp)
            counter = 0
file_output.writelines('};')
file_output.close()
file_output2 = open("plane.h","w")
file_output2.writelines("extern const float planev2Positions[576];\n")
file_output2.close()