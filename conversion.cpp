#include "conversion.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>

std::string decimalToBinaryLimitedBits(int num) {
    std::string binary;

    while (num>0) {
        binary = (num%2==0?"0":"1") + binary;
        num/=2;
    }

    return binary;
}
std::string hexToBinary(int num) {

    std::string binary;

    while (num>0) {
            binary = (num%2==0?"0":"1") + binary;
            num/=2;
       }

    while (binary.length()<8) {
        binary = "0" + binary;
    }
    return binary.substr(binary.length()-8);
}

std::string decimalToBinaryTwosComp(int num) {
    std::string binary;
    bool isNeg = (num < 0);
    num = abs(num);
    while (num>0) {
        binary = (num%2==0?"0":"1") + binary;
        num/=2;
    }

    while (binary.length()<8) {
        binary = "0" + binary;
    }

    if(isNeg) {
        bool foundFirstOne = false;
        for(int i = binary.length()-1;i>=0;i--) {
            if(foundFirstOne) {
                binary[i] = (binary[i]=='0'?'1':'0');
            }
            if(binary[i]=='1') {
                foundFirstOne = true;
            }
        }
    }
    return binary;

}

int binaryToDecimal(std::string binary) {
    int num = 0;
    int exp = 0;
    for(int i = binary.length()-1;i>=0;i--) {
        if(binary[i]=='1') {
            num += pow(2,exp);
        }
        exp++;
    }
    return num;
}

int binaryToDecimalTwosComp(std::string binary) {
    int num = 0;
    int exp = 0;

    bool isNeg = (binary[0]=='1'?true:false);
    if(isNeg) {
        bool foundFirstOne = false;
        for(int i = binary.length()-1;i>=0;i--) {
            if(foundFirstOne) {
                binary[i] = (binary[i]=='0'?'1':'0');
            }
            if(binary[i]=='1') {
                foundFirstOne = true;
            }
        }
    }

    for(int i = binary.length()-1;i>=0;i--) {
        if(binary[i]=='1') {
            num += pow(2,exp);
        }
        exp++;
    }
    if(isNeg) {
        num*=-1;
    }
    return num;
}

std::string pureFloatToBinary(double flt) {
    std::string floatBinary;

    for(int i = 0 ;i<8;i++) {
        if(flt * 2 >=1) {
            floatBinary += "1";
            flt = flt * 2 - 1;
        } else {
            floatBinary += "0";
            flt = flt * 2;
        }
    }
    return floatBinary;
}

std::string floatToBinary(double flt){

    bool isNeg = false;
    if(flt < 0) {
        flt *= -1;
        isNeg = true;
    }

    int realPart = flt;
    double floatPart = flt - realPart;



   std::string realPartString = decimalToBinaryLimitedBits(realPart);
   std::string floatPartString = pureFloatToBinary(floatPart);

   std::string floatString = (isNeg? "1": "0");
   std::string addToFloatString;
    int mantissa = 0;
   std::string mantString;

    if(realPartString.length()>0) {
        mantissa = realPartString.length();
        mantString = decimalToBinaryLimitedBits(mantissa + 4);
        addToFloatString = realPartString + floatPartString;

        if(addToFloatString.length() > 4) {
            addToFloatString = addToFloatString.substr(0,4);
        }
        while (addToFloatString.length() < 4) {
            addToFloatString += "0";
        }
        while(mantString.length()<3) {
            mantString = "0" + mantString;
        }


    } else {

        for(int i = 0 ; i <floatPartString.length();i++) {
            if(floatPartString[i]=='1') {
                break;
            }
            mantissa --;
        }
        mantString = decimalToBinaryLimitedBits(mantissa + 4);
        while(mantString.length()<3) {
            mantString = "0" + mantString;
        }
        addToFloatString = floatPartString.substr(abs(mantissa),4);




    }
    floatString +=  mantString + addToFloatString;
    return floatString;

}

double binaryToFloat(std::string binary) {
    int sign = (binary[0]=='0'?1:-1);
    int exp = binaryToDecimal(binary.substr(1,3)) - 4;

    double num = 0;
   std::string mantissa = binary.substr(4);
    int p = -1;
    int p2 = 0;
   std::string realPart = (exp > 0? mantissa.substr(0,exp):"");
   std::string fracPart;
    if(exp >= 0) {
        fracPart = mantissa.substr(exp);
    } else {
        fracPart = mantissa;
        while (exp++) {
            fracPart = "0" + fracPart;
        }
    }

    for(int i = 0; i <fracPart.length() ; i++) {
        if(fracPart[i]!='0') {
            num += pow(2,p);
        }
        p--;
    }

    for(int i = realPart.length()-1; i >=0;i--) {
        if(realPart[i]!='0') {
            num += pow(2,p2);
        }
        p2++;
    }

    num *= sign;
    return num;

}

double decimalToFloat(int num) {
   std::string binary = hexToBinary(num);
    return binaryToFloat(binary);
}

int decimalToTwosComp(int num) {
   std::string binary = decimalToBinaryTwosComp(num);
    num = binaryToDecimalTwosComp(binary);
    return num;
}

int twosCompToDecimal(int num) {
   std::string binary = decimalToBinaryTwosComp(num);
    return binaryToDecimal(binary);
}

