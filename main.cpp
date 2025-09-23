#include <iostream>
#include "converter.h"
using namespace std;

int main() {
    string num;
    int fromBase, toBase;

    cout << "Введите число: ";
    cin >> num;
    cout << "Введите основание исходной системы (2, 8, 10, 16): ";
    cin >> fromBase;
    cout << "Введите основание целевой системы (2, 8, 10, 16): ";
    cin >> toBase;

    const double decimal = toDecimal(num, fromBase);
    const string result = fromDecimal(decimal, toBase);

    cout << "Результат: " << result << endl;
    return 0;
}

