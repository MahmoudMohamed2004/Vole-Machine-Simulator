#ifndef CONVERSION_UTILS_H
#define CONVERSION_UTILS_H

#include <string>

// Function declarations
std::string decimalToBinaryLimitedBits(int num);
std::string decimalToBinaryTwosComp(int num);
int binaryToDecimal( std::string binary);
int binaryToDecimalTwosComp( std::string binary);
std::string pureFloatToBinary(double flt);
std::string floatToBinary(double flt);
double binaryToFloat( std::string binary);
double decimalToFloat(int num);
int decimalToTwosComp(int num);
int twosCompToDecimal(int num);
std::string hexToBinary(int num);

#endif // CONVERSION_UTILS_H
