#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
private:
    int rows, cols;
    double** data;

    void allocateMemory();
    void deallocateMemory();

public:
    // Конструкторы
    Matrix(int rows = 1, int cols = 1);
    Matrix(const Matrix& other);

    // Деструктор
    ~Matrix();

    // Оператор присваивания
    Matrix& operator=(const Matrix& other);

    // Операторы доступа
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    // Арифметические операторы
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;

    // Логические операторы
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    // Методы
    void print() const;
    int getRows() const;
    int getCols() const;

    // Заполнение случайными значениями
    void fillRandom(double min = 0.0, double max = 10.0);
};

#endif // MATRIX_H
