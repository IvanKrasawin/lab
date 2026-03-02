import numpy as np
import sys

def read_matrix_from_file(filename):
    """
    Чтение матрицы из текстового файла
    """
    try:
        matrix = []
        with open(filename, 'r') as file:
            for line in file:
                row = list(map(int, line.strip().split()))
                if row:  # Пропускаем пустые строки
                    matrix.append(row)
        return np.array(matrix)
    except Exception as e:
        print(f"Ошибка при чтении файла {filename}: {e}")
        return None

def save_matrix_to_file(matrix, filename):
    """
    Сохранение матрицы в файл
    """
    try:
        with open(filename, 'w') as file:
            for row in matrix:
                file.write(' '.join(map(str, row)) + '\n')
        print(f"Результат Python сохранен в файл: {filename}")
        return True
    except Exception as e:
        print(f"Ошибка при сохранении файла {filename}: {e}")
        return False

def verify_multiplication():
    """
    Основная функция верификации
    """
    print("\n" + "="*50)
    print("Python скрипт верификации (NumPy)")
    print("="*50)

    # Читаем матрицы из файлов
    matrix1 = read_matrix_from_file('matrix1_for_python.txt')
    matrix2 = read_matrix_from_file('matrix2_for_python.txt')

    if matrix1 is None or matrix2 is None:
        print("❌ Ошибка: Не удалось прочитать входные матрицы")
        return False

    print(f"\nРазмер матриц: {matrix1.shape}")
    print(f"Тип данных: {matrix1.dtype}")

    # Выполняем умножение с помощью NumPy
    try:
        result_python = np.dot(matrix1, matrix2)
        print("✅ Умножение матриц в Python выполнено успешно")
    except Exception as e:
        print(f"❌ Ошибка при умножении матриц: {e}")
        return False

    # Сохраняем результат
    if not save_matrix_to_file(result_python, 'result_python.txt'):
        return False

    # Дополнительная информация о результате
    print(f"\nСтатистика результата:")
    print(f"  Минимальное значение: {np.min(result_python)}")
    print(f"  Максимальное значение: {np.max(result_python)}")
    print(f"  Среднее значение: {np.mean(result_python):.2f}")
    print(f"  Сумма всех элементов: {np.sum(result_python)}")

    print("\n✅ Верификация в Python завершена успешно")
    return True

def main():
    """
    Точка входа в программу
    """
    try:
        # Проверяем наличие NumPy
        try:
            import numpy as np
        except ImportError:
            print("❌ Ошибка: Библиотека NumPy не установлена.")
            print("Установите её командой: pip install numpy")
            sys.exit(1)

        # Выполняем верификацию
        success = verify_multiplication()

        if success:
            print("\n✅ Скрипт верификации выполнен успешно")
            sys.exit(0)
        else:
            print("\n❌ Скрипт верификации завершился с ошибкой")
            sys.exit(1)

    except Exception as e:
        print(f"\n❌ Непредвиденная ошибка: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
