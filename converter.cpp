#include "converter.h"
#include <cmath>
#include <algorithm>

int charToVal(const char c) {
    if (isdigit(c)) return c - '0';
    return toupper(c) - 'A' + 10;
}

char valToChar(const int val) {
    if (val < 10) return '0' + val;
    return 'A' + (val - 10);
}

double toDecimal(const std::string &num, const int base) {
    const size_t dotPos = num.find('.');
    double result = 0.0;
    int power = (dotPos == std::string::npos) ? num.size() - 1 : dotPos - 1;

    for (const char i : num) {
        if (i == '.') continue;
        const int val = charToVal(i);
        result += val * pow(base, power);
        power--;
    }
    return result;
}

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

    // Дробная часть
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