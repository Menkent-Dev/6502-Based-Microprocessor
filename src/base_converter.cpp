#include <iostream>
#include <cstdint>
#include <bits/stdc++.h>

int binToDec(std::string number) {

	int dec_value = 0;
	int base = 1;
	int length = number.length();

	for (int i = length - 1; i >= 0; i--) {
		if (number[i] == '1') {
			dec_value += base;
		}
		base = base * 2;
	}

	return dec_value;
}

std::string decToBin(int number) {
	// Edge cases
    if (number == 0) {
		return "0";
	} else if (number < 0) {
	std::cerr << "[ERROR/Base_Converter] Input lesser than 0" << std::endl;
		return "-1";
	}

    int length = (int)(log2(number)); // Highest bit position
    return std::bitset<64>(number).to_string().substr(64 - length - 1);
}

int hexToDec(std::string number) {
    int decimal = 0;
    int pos = 1; 
    int length = number.length();
    
  
    for (int i = length - 1; i >= 0; i--) {
        char digit = number[i];

        int value;
        if (digit >= '0' && digit <= '9') {
            value = digit - '0';
        } else if (digit >= 'A' && digit <= 'F') {
            value = digit - 'A' + 10;
        } else if (digit >= 'a' && digit <= 'f') {
            value = digit - 'a' + 10;
        } else {
            std::cerr << "[ERROR/Base_Converter] Invalid input (Not a Base-16 Number)" << std::endl;
            return -1;
        }

        decimal += value * pos; // Multiply value by 16^(pos)
        pos *= 16; // Increase power of 16
    }

    return decimal;
}

std::string decToHex(int number) {

	// Stupid edge case
    if (number == 0) {
		return "0";
	}

    std::string hex = "";
    char hexDigits[] = "0123456789ABCDEF"; // Hexadecimal characters

    while (number > 0) {
        int remainder = number % 16; // Get remainder when divided by 16
        hex = hexDigits[remainder] + hex; // Prepend corresponding hex character
        number /= 16; // Reduce the number by dividing by 16
    }

    return hex;
}