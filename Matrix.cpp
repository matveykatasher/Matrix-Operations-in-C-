#include "Matrix.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Конструкторы, деструкторы и управление памятью
void Matrix::allocateMemory() {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols]();
    }
}

void Matrix::deallocateMemory() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }
    allocateMemory();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    deallocateMemory();
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    deallocateMemory();
    rows = other.rows;
    cols = other.cols;
    allocateMemory();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Индексы вне диапазона");
    }
    return data[i][j];
}

const double& Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Индексы вне диапазона");
    }
    return data[i][j];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Размеры матриц должны совпадать для сложения");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Размеры матриц должны совпадать для вычитания");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            result(i, j) = 0;
            for (int k = 0; k < cols; ++k) {
                result(i, j) += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] * scalar;
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

// Заполнение случайными значениями
void Matrix::fillRandom(double min, double max) {
    srand(static_cast<unsigned>(time(nullptr))); // Устанавливаем случайное начальное значение
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = min + static_cast<double>(rand()) / RAND_MAX * (max - min);
        }
    }
}
