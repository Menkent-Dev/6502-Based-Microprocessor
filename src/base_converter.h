#pragma once
#include <iostream>

/**
 * @brief Converts binary numbers to decimal
 * @param number Base-2 number to convert it to base-10
 */
int binToDec(std::string number);

/**
 * @brief Converts decimal numbers to binary
 * @param number Base-16 number to convert it to base-2
 */
std::string decToBin(int number);

/**
 * @brief Converts hexadecimal numbers to decimal
 * @param number Base-16 number to convert it to base-10
 */
int hexToDec(std::string number);

/**
 * @brief Converts decimal numbers to hexadecimal
 * @param number Base-16 number to convert it to base-2
 */
std::string decToHex(int number);
