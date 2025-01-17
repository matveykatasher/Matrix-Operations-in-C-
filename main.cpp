#include "Matrix.h"
#include <iostream>

void fillMatrix(Matrix& matrix) {
    std::cout << "Введите элементы матрицы построчно:\n";
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> matrix(i, j);
        }
    }
}

void printMenu() {
    std::cout << "\nВыберите операцию:\n"
              << "1. Сложение матриц (+)\n"
              << "2. Вычитание матриц (-)\n"
              << "3. Умножение матриц (*)\n"
              << "4. Умножение матрицы на скаляр (* scalar)\n"
              << "5. Сравнение матриц (==)\n"
              << "6. Сравнение матриц (!=)\n"
              << "7. Завершить программу\n"
              << "Введите номер операции: ";
}

int main() {
    try {
        int rows, cols;

        std::cout << "Введите количество строк и столбцов для матрицы 1:\n";
        std::cout << "Строки: ";
        std::cin >> rows;
        std::cout << "Столбцы: ";
        std::cin >> cols;
        Matrix m1(rows, cols);

        std::cout << "Введите количество строк и столбцов для матрицы 2:\n";
        std::cout << "Строки: ";
        std::cin >> rows;
        std::cout << "Столбцы: ";
        std::cin >> cols;
        Matrix m2(rows, cols);

        char fillChoice;
        std::cout << "Заполнить матрицы случайными значениями? (y/n): ";
        std::cin >> fillChoice;

        if (fillChoice == 'y' || fillChoice == 'Y') {
            m1.fillRandom();
            m2.fillRandom();
        } else {
            std::cout << "\nВведите данные для первой матрицы:\n";
            fillMatrix(m1);

            std::cout << "\nВведите данные для второй матрицы:\n";
            fillMatrix(m2);
        }

        std::cout << "\nМатрица 1:\n";
        m1.print();
        std::cout << "\nМатрица 2:\n";
        m2.print();

        int choice = 0;
        do {
            printMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: { // Сложение матриц
                    if (m1.getRows() == m2.getRows() && m1.getCols() == m2.getCols()) {
                        Matrix result = m1 + m2;
                        std::cout << "Результат сложения:\n";
                        result.print();
                    } else {
                        std::cout << "Ошибка: размеры матриц не совпадают!\n";
                    }
                    break;
                }
                case 2: { // Вычитание матриц
                    if (m1.getRows() == m2.getRows() && m1.getCols() == m2.getCols()) {
                        Matrix result = m1 - m2;
                        std::cout << "Результат вычитания:\n";
                        result.print();
                    } else {
                        std::cout << "Ошибка: размеры матриц не совпадают!\n";
                    }
                    break;
                }
                case 3: { // Умножение матриц
                    if (m1.getCols() == m2.getRows()) {
                        Matrix result = m1 * m2;
                        std::cout << "Результат умножения матриц:\n";
                        result.print();
                    } else {
                        std::cout << "Ошибка: количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы!\n";
                    }
                    break;
                }
                case 4: { // Умножение на скаляр
                    double scalar;
                    std::cout << "Введите скаляр: ";
                    std::cin >> scalar;
                    Matrix result = m1 * scalar;
                    std::cout << "Результат умножения первой матрицы на " << scalar << ":\n";
                    result.print();
                    break;
                }
                case 5: { // Сравнение (==)
                    if (m1 == m2) {
                        std::cout << "Матрицы равны.\n";
                    } else {
                        std::cout << "Матрицы не равны.\n";
                    }
                    break;
                }
                case 6: { // Сравнение (!=)
                    if (m1 != m2) {
                        std::cout << "Матрицы не равны.\n";
                    } else {
                        std::cout << "Матрицы равны.\n";
                    }
                    break;
                }
                case 7: {
                    std::cout << "Завершение программы.\n";
                    break;
                }
                default:
                    std::cout << "Некорректный выбор. Попробуйте снова.\n";
            }
        } while (choice != 7);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
