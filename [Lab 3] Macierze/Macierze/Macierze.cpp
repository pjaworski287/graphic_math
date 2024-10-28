#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <iomanip>

#define M_PI 3.14159

class Matrix {
public:
    float matrix[4][4];
    int rows = 4, columns = 4;
    int vectorSize = 4;

    // Deafult constructor
    Matrix() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                matrix[i][j] = 0;
    }

    // Constructor with direct data
    Matrix(float init[4][4]) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                matrix[i][j] = init[i][j];
    }

    // Create identity matrix
    static Matrix identity() {
        Matrix matrix;
        for (int i = 0; i < 4; i++)
            matrix.matrix[i][i] = 1;
        return matrix;
    }

    // Add matrix
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        return result;
    }

    // Sub matrix
    Matrix operator-(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        return result;
    }

    // Mul matrix by scalar
    Matrix operator*(float scalar) const {
        Matrix result;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.matrix[i][j] = matrix[i][j] * scalar;
        return result;
    }

    // Mul matrix by other matrix
    Matrix operator*(const Matrix& other) const {
        Matrix result;

        if (columns != other.rows) throw std::invalid_argument("Niepoprawne wymiary do mnożenia macierzy");

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.columns; j++) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < columns; k++)
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        return result;
    }

    // Mul by vector
    std::vector<float> multiplyVector(const std::vector<float>& vec) const {
        if (vec.size() != vectorSize)
            throw std::invalid_argument("Wektor ma niepoprawny rozmiar");

        std::vector<float> result(vectorSize, 0.0f);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result[i] += matrix[i][j] * vec[j];
        return result;
    }

    // Transpose matrix
    Matrix transpose() const {
        Matrix result;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.matrix[i][j] = matrix[j][i];
        return result;
    }

    // Translation
    static Matrix translation(float tx, float ty, float tz) {
        Matrix matrix = identity();
        matrix.matrix[0][3] = tx;
        matrix.matrix[1][3] = ty;
        matrix.matrix[2][3] = tz;
        return matrix;
    }

    // Scale
    static Matrix scaling(float sx, float sy, float sz) {
        Matrix matrix = identity();
        matrix.matrix[0][0] = sx;
        matrix.matrix[1][1] = sy;
        matrix.matrix[2][2] = sz;
        return matrix;
    }

   
    // Rotate X
    static Matrix rotationX(float angle) {
        Matrix matrix = identity();
        float rad = angle * M_PI / 180.0f;
        matrix.matrix[1][1] = cos(rad);
        matrix.matrix[1][2] = -sin(rad);
        matrix.matrix[2][1] = sin(rad);
        matrix.matrix[2][2] = cos(rad);
        return matrix;
    }

    // Rotate Y
    static Matrix rotationY(float angle) {
        Matrix matrix = identity();
        float rad = angle * M_PI / 180.0f;
        matrix.matrix[0][0] = cos(rad);
        matrix.matrix[0][2] = sin(rad);
        matrix.matrix[2][0] = -sin(rad);
        matrix.matrix[2][2] = cos(rad);
        return matrix;
    }

    // Combine matriexes
    Matrix combine(const Matrix& other) const {
        return *this * other;
    }

    // Print matrix on terminal
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

int main() {

    std::cout << "Macierz jednostkowa:\n";
    Matrix identity = Matrix::identity();
    identity.print();

    Matrix matrixI = Matrix::identity();

    float dataA[4][4] = {
     {1, 2, 3, 4},
     {2, 0, -1, 2},
     {-1, 1, 1, 2},
     {0, 4, 2, 1}
    };

    float dataB[4][4] = {
       {2, -2, 3, 4},
       {-1, 2, -1, 2},
       {1, 3, 1, 3},
       {2, 3, 2, 4}
    };

    Matrix matrixA(dataA);
    Matrix matrixB(dataB);

    std::cout << "\nMatrixA:\n";
    matrixA.print();
    std::cout << "MatrixB:\n";
    matrixB.print();

    std::cout << "\nDodawanie macierzy:\n";
    Matrix resultAdd = matrixA + matrixB;
    resultAdd.print();

    std::cout << "\nOdejmowanie macierzy:\n";
    Matrix resultSub = matrixA - matrixB;
    resultSub.print();

    std::cout << "\nMnożenie macierzy przez macierz:\n";
    Matrix resultMul = matrixA * matrixB;
    resultMul.print();

    std::cout << "\nMnożenie macierzy przez skalar:\n";
    Matrix resultMulS = matrixA * 4;
    resultMulS.print();

    std::cout << "\nTranslacja macierzy:\n";
    Matrix translationMatrix = Matrix::translation(1, 2, 3);
    translationMatrix.print();

    std::cout << "\nSkalowanie macierzy:\n";
    Matrix scalingMatrix = Matrix::scaling(2, 2, 2);
    scalingMatrix.print();

    Matrix rotationY = Matrix::rotationY(90);
    std::vector<float> vector = { 1, 0, 0, 1 };
    std::vector<float> rotatedVector = rotationY.multiplyVector(vector);
    std::cout << "\nObrot wektora [1, 0, 0, 1] o 90 stopni wokol osi Y:\n";
    for (float value : rotatedVector) std::cout << value << " ";
    
    std::cout << "\nTest na brak przemienności macierzy:\n";
    Matrix matrixAB = matrixA * matrixB;
    Matrix matrixBA = matrixB * matrixA;
    std::cout << "\nMnozenie macierzy A * B:\n";
    matrixAB.print();
    std::cout << "\nMnozenie macierzy B * A:\n";
    matrixBA.print();

    return 0;
}
