#include "converter.h"
#include <cmath>
#include <algorithm>

// Преобразует символ цифры/буквы (0-9, A-Z) в числовое значение
int charToVal(const char c) {
    if (isdigit(c)) return c - '0';
    return toupper(c) - 'A' + 10;
}

// Преобразует числовое значение (0..35) в соответствующий символ (0-9, A-Z)
char valToChar(const int val) {
    if (val < 10) return '0' + val;
    return 'A' + (val - 10);
}

// Перевод числа в виде строки из заданного основания в десятичный формат (double).
// Поддерживается дробная часть через точку '.'.
// Пример: "1A.3" с base=16 -> возвращает соответствующее значение в десятичных.
double toDecimal(const std::string &num, const int base) {
    // позиция точки (если есть)
    const size_t dotPos = num.find('.');
    double result = 0.0;
    // степень для первого символа слева от точки (или для последнего символа, если точки нет)
    int power = (dotPos == std::string::npos) ? num.size() - 1 : dotPos - 1;

    for (const char i : num) {
        if (i == '.') continue; // пропустить разделитель
        const int val = charToVal(i);
        // суммируем вклад цифры: val * base^power
        result += val * pow(base, power);
        power--;
    }
    return result;
}

// Преобразует десятичное число (double) в строковое представление в указанном основании.
// precision задаёт максимальное количество знаков дробной части в новом основании.
// Возвращает строку вида "INT.FRAC" (если есть дробная часть), иначе только "INT".
std::string fromDecimal(const double num, const int base, const int precision) {
    auto intPart = static_cast<long long>(num);
    double fracPart = num - intPart;

    // Целая часть
    std::string intStr;
    if (intPart == 0) intStr = "0";
    while (intPart > 0) {
        intStr.push_back(valToChar(intPart % base));
        intPart /= base;
    }

    std::reverse(intStr.begin(), intStr.end());

    std::string fracStr;
    if (fracPart > 1e-12) {
        fracStr.push_back('.');
        for (int i = 0; i < precision; i++) {
            fracPart *= base;
            const int digit = static_cast<int>(fracPart);
            fracStr.push_back(valToChar(digit));
            fracPart -= digit;
            if (fracPart < 1e-12) break;
        }
    }

    return intStr + fracStr;
}

// Задание для проверки Грачев Илья 1ИБ:
//1A 23,16(10) = 10111.0010100011(2)
//1B 118,13(10) = 166.1024365605(8)
//1C 98,19(10) = 62.30A3D70A3D(16)

//2A 36,733(8) = 30.927734375(10)
//2B 51A,35(16) = 1306.20703125(10)
//2C 101001,10001(2) = 41.53125(10)

//3A 11110001,10101(2) = 361.52(8)
//3B 3DC,A9B(16) = 1111011100.1010100110(2)
//3C 27,53(8) = 10111.101011(2)
//3D 10011111,10011(2) = 9F.98(16)