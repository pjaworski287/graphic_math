#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <iomanip>

#define M_PI 3.14159

class Matrix4x4 {
public:
    float data[4][4];

    // Deafult constructor (matrix with 0s)
    Matrix4x4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = 0;
    }

    // Constructor with direct data
    Matrix4x4(float init[4][4]) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = init[i][j];
    }

    // Create identity matrix
    static Matrix4x4 identity() {
        Matrix4x4 matrix;
        for (int i = 0; i < 4; ++i)
            matrix.data[i][i] = 1;
        return matrix;
    }

    // Add matrix
    Matrix4x4 operator+(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Sub matrix
    Matrix4x4 operator-(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    // Mul matrix by scalar
    Matrix4x4 operator*(float scalar) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.data[i][j] = data[i][j] * scalar;
        return result;
    }

    // Mul matrix by other matrix
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < 4; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    // Mul by vector
    std::vector<float> multiplyVector(const std::vector<float>& vec) const {
        if (vec.size() != 4)
            throw std::invalid_argument("Wektor musi mieć rozmiar 4!");
        std::vector<float> result(4, 0.0f);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i] += data[i][j] * vec[j];
        return result;
    }

    // Transpose matrix
    Matrix4x4 transpose() const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.data[i][j] = data[j][i];
        return result;
    }

    // Translation
    static Matrix4x4 translation(float tx, float ty, float tz) {
        Matrix4x4 matrix = identity();
        matrix.data[0][3] = tx;
        matrix.data[1][3] = ty;
        matrix.data[2][3] = tz;
        return matrix;
    }

    // Scale
    static Matrix4x4 scaling(float sx, float sy, float sz) {
        Matrix4x4 matrix = identity();
        matrix.data[0][0] = sx;
        matrix.data[1][1] = sy;
        matrix.data[2][2] = sz;
        return matrix;
    }

    // Rotate Z
    static Matrix4x4 rotationZ(float angle) {
        Matrix4x4 matrix = identity();
        float rad = angle * M_PI / 180.0f;
        matrix.data[0][0] = cos(rad);
        matrix.data[0][1] = -sin(rad);
        matrix.data[1][0] = sin(rad);
        matrix.data[1][1] = cos(rad);
        return matrix;
    }

    // Rotate Y
    static Matrix4x4 rotationY(float angle) {
        Matrix4x4 matrix = identity();
        float rad = angle * M_PI / 180.0f;
        matrix.data[0][0] = cos(rad);
        matrix.data[0][2] = sin(rad);
        matrix.data[2][0] = -sin(rad);
        matrix.data[2][2] = cos(rad);
        return matrix;
    }

    // Obrót wokół osi X
    static Matrix4x4 rotationX(float angle) {
        Matrix4x4 matrix = identity();
        float rad = angle * M_PI / 180.0f;
        matrix.data[1][1] = cos(rad);
        matrix.data[1][2] = -sin(rad);
        matrix.data[2][1] = sin(rad);
        matrix.data[2][2] = cos(rad);
        return matrix;
    }

    // Combine matriexes
    Matrix4x4 combine(const Matrix4x4& other) const {
        return *this * other;
    }

    // Print matrix on terminal
    void print() const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

int main() {

    // Jednostkowa
    Matrix4x4 identity = Matrix4x4::identity();
    std::cout << "Macierz jednostkowa:\n";
    identity.print();

    // Dodawanie macierzy
    Matrix4x4 matrixA = Matrix4x4::identity();
    matrixA = matrixA * 2;
    Matrix4x4 matrixB = Matrix4x4::identity();
    Matrix4x4 resultAdd = matrixA + matrixB;
    std::cout << "\nDodawanie macierzy:\n";
    resultAdd.print();

    // Obrót wektora
    Matrix4x4 rotationY = Matrix4x4::rotationY(90);
    std::vector<float> vector = { 1, 0, 0, 1 };
    std::vector<float> rotatedVector = rotationY.multiplyVector(vector);
    std::cout << "\nObrot wektora [1, 0, 0, 1] o 90 stopni wokol osi Y:\n";
    for (float value : rotatedVector) std::cout << value << " ";
    std::cout << "\n";

    // Brak przemiennosci macierzy
    Matrix4x4 matrixC = matrixA * matrixB;
    Matrix4x4 matrixD = matrixB * matrixA;
    std::cout << "\nMnozenie macierzy A * B:\n";
    matrixC.print();
    std::cout << "\nMnozenie macierzy B * A:\n";
    matrixD.print();

    return 0;
}
