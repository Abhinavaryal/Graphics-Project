#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#include "vector.h"

using namespace std;

float *importObj(string filepath, unsigned int* numVertices, vector<unsigned int>& indices, vector<vector3D>& vertexNormal, int &yn , int &yt, unsigned int* numIndices)
{
    fstream file(filepath);
    if (!file.is_open())
    {
        throw 69;
    }

    // Initialize vectors for vertices and faces
    vector<vector3D> vertices;
    vector<vector3D> vertices1;
    //for scaling
    vector3D avgVertex(0,0,0);
    vector3D maxMagVertex(0,0,0);
    //vector to store texture data
    vector<vector3D> vertexTextures;

    string line;
    do
    {
        if (line.substr(0, 1) == "#" ||line.substr(0, 1) == "u"|| line.substr(0, 1) == "s" || line.substr(0, 1) == "g" || line.substr(0, 1) == "u" ||line.empty() || line.substr(0, 1) == "l")
        {
            continue;
        }
        if (line.substr(0, 2) == "ze")
            break;
        if (line.substr(0, 2) == "v ")
        {

            string word;
            stringstream ss(line);
            ss >> word; // pull off "v " prefix
            ss >> word;
            float num1 = stof(word);
            ss >> word;
            float num2 = stof(word);
            ss >> word;
            float num3 = stof(word);
            vector3D temp(num1, num2, num3);
            vertices.push_back(temp);
            avgVertex = avgVertex.add(temp);
            if (temp.magnitude() > maxMagVertex.magnitude()) {
                maxMagVertex = temp;
            }
        }
        else if (line.substr(0,2) == "vn")
        {
            yn = 1;
            //store vertex normal
            string word;
            stringstream ss(line);
            ss >> word;
            ss >> word;
            float num1 = stof(word);
            ss >> word;
            float num2 = stof(word);
            ss >> word;
            float num3 = stof(word);
            vector3D temp(num1, num2, num3);
            vertexNormal.push_back(temp);
        }
        else if (line.substr(0,2) == "vt")
        {
            yt = 1;
            //store vertex normal
            string word;
            stringstream ss(line);
            ss >> word;
            ss >> word;
            float num1 = stof(word);
            ss >> word;
            float num2 = stof(word);
            //texture are only x,y coords, but for consistency, using 3D vector
            vector3D temp(num1, num2, 0.0f);
            vertexTextures.push_back(temp);
        }
        else if (line.substr(0, 2) == "f ")
        {
            // Store face data
            string word;
            stringstream ss(line);
            vector<int> v;
            ss >> word; // pull off "f " prefix
            while (ss >> word)
            {
                v.push_back((float)stoi(word.substr(0, word.find('/'))));
            }

            // Decompose face into triangles
            for (int i = 1; i < v.size() - 1; i++)
            {
                vector3D temp(v[0] - 1, v[i] - 1, v[i + 1] - 1);
                indices.push_back(temp.x);
                indices.push_back(temp.y);
                indices.push_back(temp.z);
            }
        }


    }while (getline(file, line));
    
    avgVertex = avgVertex.scale(1.0f/vertices.size());

    //translate obj to center
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = vertices[i].subtract(avgVertex);
    }

    //scale obj to optimum size
    float scale = 1.0f / maxMagVertex.subtract(avgVertex).magnitude();
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = vertices[i].scale(scale);
    }

    for(int i = 0; i < vertices.size(); i++){
        vertices1.push_back(vertices[i]);
        vertices1.push_back(vector3D(0.3f, 0.3f, 0.3f));
        if (yn == 1) {
            vertices1.push_back(vertexNormal[i]);
        }
        if (yt == 1) {
            vertices1.push_back(vertexTextures[i]);
        }
    }

    std::cout << "faces size: " << indices.size() << endl;

    float* verticesArr = new float[vertices1.size() * 3];

    *numVertices = vertices1.size() * 24;
    *numIndices = indices.size() * 4;

    for (int i = 0; i < vertices1.size(); i++) {
        verticesArr[i * 3 + 0] = vertices1[i].x;
        verticesArr[i * 3 + 1] = vertices1[i].y;
        verticesArr[i * 3 + 2] = vertices1[i].z;
    }
    // Print the elements using a for loop
    return verticesArr;

}