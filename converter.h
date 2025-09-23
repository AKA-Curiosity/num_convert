#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

int charToVal(char c);
char valToChar(int val);
double toDecimal(const std::string &num, int base);
std::string fromDecimal(double num, int base, int precision = 10);

#endif