#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

// Константы для работы программы
const int MATRIX_SIZE = 5;  // Размер квадратных матриц (можно изменить)
const int MIN_VALUE = -100; // Минимальное значение для случайных чисел
const int MAX_VALUE = 100;  // Максимальное значение для случайных чисел

// Функция для создания и заполнения файла случайными числами
void createMatrixFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка создания файла: " << filename << endl;
        return;
    }
    
    srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            // Генерация случайного числа от MIN_VALUE до MAX_VALUE
            int num = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
            file << num << " ";
        }
        file << endl;
    }
    
    file.close();
    cout << "Файл " << filename << " успешно создан." << endl;
}

// Функция для чтения матрицы из файла
vector<vector<int>> readMatrixFromFile(const string& filename) {
    vector<vector<int>> matrix(MATRIX_SIZE, vector<int>(MATRIX_SIZE, 0));
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return matrix;
    }
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            file >> matrix[i][j];
            if (file.fail()) {
                cerr << "Ошибка чтения данных из файла: " << filename << endl;
                file.close();
                return matrix;
            }
        }
    }
    
    file.close();
    return matrix;
}

// Функция для перемножения двух матриц
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrixA, 
                                     const vector<vector<int>>& matrixB) {
    vector<vector<int>> result(MATRIX_SIZE, vector<int>(MATRIX_SIZE, 0));
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    
    return result;
                                     }
                                     
                                     // Функция для сохранения матрицы в файл в формате, удобном для Python
                                     void saveMatrixForPython(const vector<vector<int>>& matrix, const string& filename) {
                                         ofstream file(filename);
                                         if (!file.is_open()) {
                                             cerr << "Ошибка создания файла: " << filename << endl;
                                             return;
                                         }
                                         
                                         for (int i = 0; i < MATRIX_SIZE; i++) {
                                             for (int j = 0; j < MATRIX_SIZE; j++) {
                                                 file << matrix[i][j];
                                                 if (j < MATRIX_SIZE - 1) file << " ";
                                             }
                                             file << endl;
                                         }
                                         
                                         file.close();
                                     }
                                     
                                     // Функция для вызова Python-скрипта верификации
                                     bool verifyWithPython() {
                                         cout << "\n--- Запуск верификации с помощью Python ---" << endl;
                                         
                                         string command = "python verify_matrices.py";
                                         int result = system(command.c_str());
                                         
                                         if (result == 0) {
                                             cout << "Верификация успешно завершена!" << endl;
                                             return true;
                                         } else {
                                             cout << "Ошибка при выполнении верификации. Код ошибки: " << result << endl;
                                             return false;
                                         }
                                     }
                                     
                                     // Функция для вывода матрицы на экран
                                     void printMatrix(const vector<vector<int>>& matrix, const string& name) {
                                         cout << "\nМатрица " << name << ":" << endl;
                                         for (int i = 0; i < MATRIX_SIZE; i++) {
                                             for (int j = 0; j < MATRIX_SIZE; j++) {
                                                 cout << setw(8) << matrix[i][j] << " ";
                                             }
                                             cout << endl;
                                         }
                                     }
                                     
                                     // Функция для сравнения двух матриц
                                     bool compareMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
                                         for (int i = 0; i < MATRIX_SIZE; i++) {
                                             for (int j = 0; j < MATRIX_SIZE; j++) {
                                                 if (matrix1[i][j] != matrix2[i][j]) {
                                                     return false;
                                                 }
                                             }
                                         }
                                         return true;
                                     }
                                     
                                     // Функция для чтения результата верификации
                                     vector<vector<int>> readVerificationResult(const string& filename) {
                                         return readMatrixFromFile(filename);
                                     }
                                     
                                     int main() {
                                         setlocale(LC_ALL, "Russian");
                                         
                                         // Имена файлов
                                         string file1 = "matrix1.txt";
                                         string file2 = "matrix2.txt";
                                         string resultFile = "result_cpp.txt";
                                         string pythonResultFile = "result_python.txt";
                                         string verificationResultFile = "verification_result.txt";
                                         
                                         cout << "=== Программа для перемножения квадратных матриц с верификацией ===" << endl;
                                         cout << "Размер матриц: " << MATRIX_SIZE << "x" << MATRIX_SIZE << endl;
                                         cout << "Диапазон случайных чисел: от " << MIN_VALUE << " до " << MAX_VALUE << endl;
                                         
                                         // Создаем файлы со случайными матрицами
                                         cout << "\n--- Создание файлов с матрицами ---" << endl;
                                         createMatrixFile(file1);
                                         createMatrixFile(file2);
                                         
                                         // Читаем матрицы из файлов
                                         cout << "\n--- Чтение матриц из файлов ---" << endl;
                                         vector<vector<int>> matrix1 = readMatrixFromFile(file1);
                                         vector<vector<int>> matrix2 = readMatrixFromFile(file2);
                                         
                                         // Выводим матрицы на экран
                                         printMatrix(matrix1, "A");
                                         printMatrix(matrix2, "B");
                                         
                                         // Перемножаем матрицы (C++ реализация)
                                         cout << "\n--- Выполнение перемножения матриц (C++) ---" << endl;
                                         vector<vector<int>> result_cpp = multiplyMatrices(matrix1, matrix2);
                                         
                                         // Выводим результат на экран
                                         printMatrix(result_cpp, "Результат (C++)");
                                         
                                         // Сохраняем результат в файл
                                         saveMatrixForPython(result_cpp, resultFile);
                                         cout << "Результат C++ сохранен в файл: " << resultFile << endl;
                                         
                                         // Сохраняем исходные матрицы для Python
                                         saveMatrixForPython(matrix1, "matrix1_for_python.txt");
                                         saveMatrixForPython(matrix2, "matrix2_for_python.txt");
                                         
                                         // Запускаем верификацию с помощью Python
                                         bool verificationSuccess = verifyWithPython();
                                         
                                         if (verificationSuccess) {
                                             // Читаем результат верификации
                                             vector<vector<int>> result_python = readVerificationResult(pythonResultFile);
                                             printMatrix(result_python, "Результат (Python/NumPy)");
                                             
                                             // Сравниваем результаты
                                             bool matricesEqual = compareMatrices(result_cpp, result_python);
                                             
                                             if (matricesEqual) {
                                                 cout << "\n✅ ВЕРИФИКАЦИЯ ПРОЙДЕНА: Результаты C++ и Python совпадают!" << endl;
                                                 
                                                 // Сохраняем информацию о верификации
                                                 ofstream verificationFile(verificationResultFile);
                                                 verificationFile << "VERIFICATION_PASSED" << endl;
                                                 verificationFile << "Результаты C++ и Python совпадают." << endl;
                                                 verificationFile.close();
                                             } else {
                                                 cout << "\n❌ ОШИБКА ВЕРИФИКАЦИИ: Результаты C++ и Python НЕ совпадают!" << endl;
                                                 
                                                 // Сохраняем информацию об ошибке
                                                 ofstream verificationFile(verificationResultFile);
                                                 verificationFile << "VERIFICATION_FAILED" << endl;
                                                 verificationFile << "Результаты C++ и Python не совпадают." << endl;
                                                 verificationFile.close();
                                             }
                                         } else {
                                             cout << "\n⚠️ Верификация не была выполнена из-за ошибки в Python скрипте." << endl;
                                         }
                                         
                                         cout << "\nПрограмма успешно завершена!" << endl;
                                         
                                         return 0;
                                     }
