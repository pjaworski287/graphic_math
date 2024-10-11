﻿#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Vector{

    // Directions
    double x, y, z;

public:

    // Constructors and destructors
    Vector() : x(0.0), y(0.0), z(0.0) {}
    Vector(double xValue, double yValue, double zValue) : x(xValue), y(yValue), z(zValue) {}
    Vector(Vector p1, Vector p2) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}
    Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}
    ~Vector() = default;

    // Getters
    double getX() const {    return x;   }
    double getY() const {    return y;   }
    double getZ() const {    return z;   }
    string getInfo() const { 
        return "Directions [x,y,z] - [" +
            std::to_string(getX()) + ", " + 
            std::to_string(getY()) + ", " + 
            std::to_string(getX()) + "]";
    }

    // Setters
    void setX(double xValue) {   x = xValue; }
    void setY(double yValue) {   y = yValue; }
    void setZ(double zValue) {   z = zValue; }

    // Operator overloading (add, sub, mul-by-scalar)
    Vector operator+(const Vector& v) const {
        return Vector(x + v.x, y + v.y, z + v.z);       
    }
    Vector operator-(const Vector& v) const {
        return Vector(x - v.x, y - v.y, z - v.z);       
    }
    Vector operator*(double scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }
    Vector operator/(double scalar) const {
        if (scalar != 0)
            return Vector(x / scalar, y / scalar, z / scalar);
        else
            throw invalid_argument("Division by zero is not allowed!");
    }

    // Operations of dot-mul and cross-mul vectors with showing an angle between them
    double dotProduct(const Vector& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    double angleBetween(const Vector& v) const {
        double dot = dotProduct(v);
        double len1 = length();
        double len2 = v.length();

        if (len1 == 0 || len2 == 0)
            throw invalid_argument("To calculate angle between vectors, neither of them can have the lenght equal to zero!");

        double cosTheta = dot / (len1 * len2);
        return acos(cosTheta);
    }
    Vector crossProduct(const Vector& v) const {
        return Vector(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x 
        );
    }

    // Other methods (lenght of vector, normalize vector)
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }
    Vector normalize() const {
        double len = length();
        if (len != 0.0)
            return Vector(x / len, y / len, z / len);
        else
            throw invalid_argument("Cannot normalize a zero vector.");
    }
};



int main()
{

    Vector v5(4, 5, 1);
    Vector v6(4, 1, 3);
    Vector cross = v5.crossProduct(v6);

    cout << "Wektor prostopadly to: " << cross.getInfo() << "\n";

    return 0;
}