#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
using namespace std;

typedef struct Model {
    int vertices;
    int positions;
    int texels;
    int normals;
    int faces;
} Model;

Model getOBJinfo(string fp) {
    Model model = {0};
    
    ifstream inOBJ;
    inOBJ.open(fp);
    if(!inOBJ.good()) {
        cout << "ERROR OPENING OBJ FILE" << endl;
        exit(1);
    }
    
    while(!inOBJ.eof()) {
        string line;
        getline(inOBJ, line);
        string type = line.substr(0,2);
        
        if(type.compare("v ") == 0)
            model.positions++;
        else if(type.compare("vt") == 0)
            model.texels++;
        else if(type.compare("vn") == 0)
            model.normals++;
        else if(type.compare("f ") == 0)
            model.faces++;
    }
    
    model.vertices = model.faces*3;
    
    inOBJ.close();
    
    return model;
}

void extractOBJdata(string fp, float positions[][3], float texels[][2], float normals[][3], int faces[][9]) {
    int p = 0;
    int t = 0;
    int n = 0;
    int f = 0;
    
    ifstream inOBJ;
    inOBJ.open(fp);
    if(!inOBJ.good()) {
        cout << "ERROR OPENING OBJ FILE" << endl;
        exit(1);
    }

    while(!inOBJ.eof()) {
        string line;
        getline(inOBJ, line);
        string type = line.substr(0,2);
        
        if(type.compare("v ") == 0) {
            char* l = new char[line.size()+1];
            memcpy(l, line.c_str(), line.size()+1);
                    
            strtok(l, " ");
            for(int i=0; i<3; i++)
                positions[p][i] = atof(strtok(NULL, " "));
                    
            delete[] l;
            p++;
        } else if(type.compare("vt") == 0) {
            char* l = new char[line.size()+1];
            memcpy(l, line.c_str(), line.size()+1);
                    
            strtok(l, " ");
            for(int i=0; i<2; i++)
                texels[t][i] = atof(strtok(NULL, " "));
                    
            delete[] l;
            t++;
        } else if(type.compare("vn") == 0) {
            char* l = new char[line.size()+1];
            memcpy(l, line.c_str(), line.size()+1);
                    
            strtok(l, " ");
            for(int i=0; i<3; i++)
                normals[n][i] = atof(strtok(NULL, " "));
                    
            delete[] l;
            n++;
        } else if(type.compare("f ") == 0) {
            char* l = new char[line.size()+1];
            memcpy(l, line.c_str(), line.size()+1);
                    
            strtok(l, " ");
            for(int i=0; i<9; i++)
                faces[f][i] = atof(strtok(NULL, " /"));
                    
            delete[] l;
            f++;
        }
    }
    
    inOBJ.close();
}

void writeH(string fp, string name, Model model) {
    ofstream outH;
    outH.open(fp);
    if(!outH.good()) {
        cout << "ERROR CREATING H FILE" << endl;
        exit(1);
    }
    
    outH << "// This is a .h file for the model: " << name << endl;
    outH << endl;

    // Write statistics
    outH << "// Positions: " << model.positions << endl;
    outH << "// Texels: " << model.texels << endl;
    outH << "// Normals: " << model.normals << endl;
    outH << "// Faces: " << model.faces << endl;
    outH << "// Vertices: " << model.vertices << endl;
    outH << endl;
        
    // Write declarations
    outH << "const int " << name << "Vertices;" << endl;
    outH << "const float " << name << "Positions[" << model.vertices*3 << "];" << endl;
    outH << "const float " << name << "Texels[" << model.vertices*2 << "];" << endl;
    outH << "const float " << name << "Normals[" << model.vertices*3 << "];" << endl;
    outH << endl;
    
    outH.close();
}

void writeCvertices(string fp, string name, Model model) {
    ofstream outC;
    outC.open(fp);
    if(!outC.good()) {
        cout << "ERROR CREATING C FILE" << endl;
        exit(1);
    }
    
    outC << "// This is a .c file for the model: " << name << endl;
    outC << endl;
    
    outC << "#include " << "\"" << name << ".h" << "\"" << endl;
    outC << endl;
    
    outC << "const int " << name << "Vertices = " << model.vertices << ";" << endl;
    outC << endl;
    
    outC.close();
}

void writeCpositions(string fp, string name, Model model, int faces[][9], float positions[][3]) {    
    ofstream outC;
    outC.open(fp, ios::app);
    
    outC << "const float " << name << "Positions[" << model.vertices*3 << "] = " << endl;
    outC << "{" << endl;
    for(int i=0; i<model.faces; i++) {
        int vA = faces[i][0] - 1;
        int vB = faces[i][3] - 1;
        int vC = faces[i][6] - 1;
        
        outC << positions[vA][0] << ", " << positions[vA][1] << ", " << positions[vA][2] << ", " << endl;
        outC << positions[vB][0] << ", " << positions[vB][1] << ", " << positions[vB][2] << ", " << endl;
        outC << positions[vC][0] << ", " << positions[vC][1] << ", " << positions[vC][2] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
    
    outC.close();
}

void writeCtexels(string fp, string name, Model model, int faces[][9], float texels[][2]) {
    ofstream outC;
    outC.open(fp, ios::app);
    
    outC << "const float " << name << "Texels[" << model.vertices*2 << "] = " << endl;
    outC << "{" << endl;
    for(int i=0; i<model.faces; i++)
    {
        int vtA = faces[i][1] - 1;
        int vtB = faces[i][4] - 1;
        int vtC = faces[i][7] - 1;
        
        outC << texels[vtA][0] << ", " << texels[vtA][1] << ", " << endl;
        outC << texels[vtB][0] << ", " << texels[vtB][1] << ", " << endl;
        outC << texels[vtC][0] << ", " << texels[vtC][1] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
    
    outC.close();
}

void writeCnormals(string fp, string name, Model model, int faces[][9], float normals[][3]) {
    ofstream outC;
    outC.open(fp, ios::app);
    
    outC << "const float " << name << "Normals[" << model.vertices*3 << "] = " << endl;
    outC << "{" << endl;
    for(int i=0; i<model.faces; i++)
    {
        int vnA = faces[i][2] - 1;
        int vnB = faces[i][5] - 1;
        int vnC = faces[i][8] - 1;
        
        outC << normals[vnA][0] << ", " << normals[vnA][1] << ", " << normals[vnA][2] << ", " << endl;
        outC << normals[vnB][0] << ", " << normals[vnB][1] << ", " << normals[vnB][2] << ", " << endl;
        outC << normals[vnC][0] << ", " << normals[vnC][1] << ", " << normals[vnC][2] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
    
    outC.close();
}

int main(int argc, char *argv[]) {
    // Arguments
    cout << argc << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    
    // Files
    string nameOBJ = argv[2];
    string filepathOBJ = "../files/" + nameOBJ + ".obj";
    string filepathH = "./" + nameOBJ + ".h";
    string filepathC = "./" + nameOBJ + ".c";


    cout << filepathOBJ << endl;

    // Model Info
    Model model = getOBJinfo(filepathOBJ);
    cout << "Model Info" << endl;
    cout << "Positions: " << model.positions << endl;
    cout << "Texels: " << model.texels << endl;
    cout << "Normals: " << model.normals << endl;
    cout << "Faces: " << model.faces << endl;
    cout << "Vertices: " << model.vertices << endl;

    // Model Data
    float positions[model.positions][3];    // XYZ
    float texels[model.texels][2];          // UV
    float normals[model.normals][3];        // XYZ
    int faces[model.faces][9];              // PTN PTN PTN

    extractOBJdata(filepathOBJ, positions, texels, normals, faces);
    cout << "Model Data" << endl;
    cout << "P1: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
    cout << "T1: " << texels[0][0] << "u " << texels[0][1] << "v " << endl;
    cout << "N1: " << normals[0][0] << "x " << normals[0][1] << "y " << normals[0][2] << "z" << endl;
    cout << "F1v1: " << faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;

    // Write H file
    writeH(filepathH, nameOBJ, model);

    // Write C file
    writeCvertices(filepathC, nameOBJ, model);
    writeCpositions(filepathC, nameOBJ, model, faces, positions);
    writeCtexels(filepathC, nameOBJ, model, faces, texels);
    writeCnormals(filepathC, nameOBJ, model, faces, normals);
}