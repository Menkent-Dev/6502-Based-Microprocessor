#ifndef BASE_CONVERTER_H
#define BASE_CONVERTER_H
#include <iostream>

//* Converts binary numbers to decimal
int binToDec(std::string number);

//* Converts decimal numbers to binary
std::string decToBin(int number);

//* Converts hexadecimal numbers to decimal
int hexToDec(std::string number);

//* Converts decimal numbers to hexadecimal
std::string decToHex(int number);

#endif