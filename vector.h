#pragma once
#define PI 3.14159

#include <cmath>
#include <string>

using namespace std;

struct vector3D {
    float x;
    float y;
    float z;

    vector3D() {
        x = 0;
        y = 0;
        z = 0;
    }
    vector3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vector3D scale(float factor) {
        return vector3D(x * factor, y * factor, z * factor);
    }
    float dot(vector3D vec2) {
        return x * vec2.x + y * vec2.y + z * vec2.z;
    }
    vector3D cross(vector3D vec2) {
        vector3D output = vector3D();
        output.x = y * vec2.z - z * vec2.y;
        output.y = z * vec2.x - x * vec2.z;
        output.z = x * vec2.y - y * vec2.x;
        return output;
    }
    vector3D add(vector3D vec2) {
        return vector3D(x + vec2.x, y + vec2.y, z + vec2.z);
    }
    vector3D subtract(vector3D vec2) {
        return vector3D(x - vec2.x, y - vec2.y, z - vec2.z);
    }
    vector3D square() {
        return vector3D(x * x, y * y, z * z);
    }
    float magnitude() {
        return sqrt(x*x + y*y + z*z);
    }
    vector3D normalize() {
        float denominator = magnitude();
        return vector3D(x / denominator, y / denominator, z / denominator);
    }
    string toString() {
        return "<" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ">";
    }
    vector3D reflection(vector3D normal){
        return (*this).subtract(normal.scale(2).scale((this)->dot(normal)));
    }
};