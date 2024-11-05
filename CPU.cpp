#include "CPU.h"
#include <fstream>
void CPU::incrementProgramCounter() {
    programCounter += 2;
    if (programCounter == 256) {
        reachedTheEnd = true;
        programCounter = 0;
    }
}

void CPU::setPC(const int& programCounter) {
    this->programCounter = programCounter;
}

int CPU::getPC() {
    return programCounter;
}

void CPU::fetchInstruction() {
    std::cout << "\nFetching the instruction in memory address " <<std::hex<<std::uppercase<< programCounter << " and " << programCounter + 1 << ": ";
    int instruction = mmry.getCell(programCounter);
    std::string hexStr;
    std::string part1 = std::format("{:x}", instruction);

    if (part1.length() == 1) {
        part1 = '0' + part1;
    }
    hexStr += part1;

    instruction = mmry.getCell(programCounter + 1);
    std::string part2 = std::format("{:x}", instruction);

    if (part2.length() == 1) {
        part2 = '0' + part2;
    }

    hexStr += part2;

    for (int i = 0; i < hexStr.length(); i++) {
        if (isalpha(hexStr[i])) {
            hexStr[i] = toupper(hexStr[i]);
        }
    }

    instructionRegister = hexStr;

    std::cout << instructionRegister << std::endl;
}

bool CPU::exectueInstruction() {
    std::string XY = instructionRegister.substr(2, 2);

    switch (instructionRegister[0]) {
        case '1':
            instruction1();
            break;
        case '2':
            instruction2();
            break;
        case '3':
            if (XY == "00") {
                instruction3R00();
            } else {
                instruction3();
            }
            break;
        case '4':
            instruction4();
            break;
        case '5':
            instruction5();
            break;
        case '6':
            instruction6();
            break;
        case '7':
            instruction7();
            break;
        case '8':
            instruction8();
            break;
        case '9':
            instruction9();
            break;
        case 'A':
            instructionA();
            break;
        case 'B':
            instructionB();
            break;
        case 'C':
            std::cout << "\nHALT.\n";
            return false;
        default:
            break;
    }
    incrementProgramCounter();
    if (reachedTheEnd) {
        std::cout << "\nYou have reached the end of the program.\n";
        return false;
    }
    return true;
}

std::string CPU::getIR() {
    return instructionRegister;
}


void CPU::loadProgram(std::istream& cin, const int& startAddress) {
    resetProgram();
    mmry.loadInstructions(cin, startAddress);
    programCounter = startAddress;
}

void CPU::loadProgram(std::ifstream& file, const int &startAddress) {
    resetProgram();
    mmry.loadInstructions(file, startAddress);
    programCounter = startAddress;
}


void CPU::runProgram() {
    fetchInstruction();
    while (exectueInstruction()) {
        fetchInstruction();
    }
}

void CPU::resetProgram() {
    programCounter = 0;
    mmry.clear();
    rgstr.clear();
    screen.clear();
    instructionRegister = "";
}

void CPU::displayMemory() {
    std::cout << std::endl;
    std::cout << "   ";
    for (int i = 0; i < 16; i++) {
        std::cout << std::right << std::hex << i;
        if (i != 15) {
            std::cout << std::setw(6) << std::setfill(' ');
        }
    }
    std::cout << std::endl;

    for (int i = 0; i < 16; i++) {
        std::cout << std::hex << i << "  ";
        for (int j = i * 16; j < (i + 1) * 16; j++) {
            std::cout << std::setw(2) << std::setfill('0') << std::right << std::hex << mmry.getCell(j);
            std::cout << "    ";
        }
        std::cout << std::endl;
    }
    displayRegister();
    displayScreen();
}

void CPU::displayRegister() {
    rgstr.display();
}

void CPU::displayScreen() {
    std::cout<<std::endl;
    std::cout<<"Screen: ";
    if(screen.empty()) {
        return;
    }
    for(const auto& it : screen) {
        std::cout<<char(it);
    }
    std::cout<<std::endl;
}


void CPU::instruction1() {
    int r = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    int memoryAddress = std::stoi(instructionRegister.substr(2, 2), nullptr, 16);
    int value = mmry.getCell(memoryAddress);
    rgstr.setCell(r, value);

    std::cout<<"-> copying the contents of memory address "<<std::hex<<std::uppercase<<memoryAddress<<" to register "<<r<<".."<<std::endl;
}

void CPU::instruction2() {
    int r = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    int value = std::stoi(instructionRegister.substr(2, 2), nullptr, 16);
    std::cout << "\n-> assinging the value " <<std::hex<<std::uppercase<< value << " to the register " << r <<".."<< std::endl;
    rgstr.setCell(r, value);
}

void CPU::instruction3() {
    int r = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    int value = rgstr.getCell(r);
    int memoryAddress = std::stoi(instructionRegister.substr(2, 2), nullptr, 16);
    std::cout << "\n-> copying the contents of register " << std::hex<<std::uppercase<<r<<" to memory address "<<memoryAddress<<".."<<std::endl;
    mmry.setCell(memoryAddress, value);
}

void CPU::instruction3R00() {
    int r = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    int value = rgstr.getCell(r);
    mmry.setCell(0,value);
    std::cout << "\n-> writing to the screen the value " << value << ".."<<std::endl;
    screen.push_back(value);
}

void CPU::instruction4() {
    int r1 = std::stoi(instructionRegister.substr(2, 1), nullptr, 16);
    int r2 = std::stoi(instructionRegister.substr(3, 1), nullptr, 16);
    rgstr.setCell(r2, rgstr.getCell(r1));
    std::cout<<"\n-> copying the contents of register "<<std::hex<<std::uppercase<<r1<<" to register "<<r2<<".."<<std::endl;
}

void CPU::instruction5() {
    int r1 = std::stoi(instructionRegister.substr(2, 1), nullptr, 16);
    int r2 = std::stoi(instructionRegister.substr(3), nullptr, 16);
    int r3 = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);

    int num1 = rgstr.getCell(r1), num2 = rgstr.getCell(r2);
    int sum = decimalToTwosComp(num1) + decimalToTwosComp(num2);
    sum = twosCompToDecimal(sum);

    std::cout << "\n-> assigning the result of adding registers " <<std::hex<<std::uppercase<< r1 << " and "<<r2 << " (2's Complememnt) to register " << r3 <<".."<<std::endl;
    rgstr.setCell(r3, sum);
}

void CPU::instruction6() {
    int r1 = std::stoi(instructionRegister.substr(2, 1), nullptr, 16);
    int r2 = std::stoi(instructionRegister.substr(3, 1), nullptr, 16);
    int r3 = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    double flt1 = decimalToFloat(rgstr.getCell(r1));
    double flt2 = decimalToFloat(rgstr.getCell(r2));
    double sum = flt1 + flt2;
    std::string fltString = floatToBinary(sum);
    int result = binaryToDecimal(fltString);
    std::cout << "\n-> assigning the result of adding registers " <<std::hex<<std::uppercase<< r1 << " and "<<r2 << " (Floating Point Notation) to register " << r3<<".." <<std::endl;
    rgstr.setCell(r3, result);
}

void CPU::instruction7() {
    int r1 = std::stoi(instructionRegister.substr(2, 1), nullptr, 16);
    int r2 = std::stoi(instructionRegister.substr(3, 1), nullptr, 16);
    int r3 = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);

    int sum = rgstr.getCell(r1) | rgstr.getCell(r2);
    std::cout<<"\n-> assigning the results of ORing registers "<<std::hex<<std::uppercase<<r1<<" and "<<r2<<" to register "<<r3<<".."<<std::endl;
    rgstr.setCell(r3, sum);
}

void CPU::instruction8() {
    int r1 = std::stoi(instructionRegister.substr(2, 1), nullptr, 16);
    int r2 = std::stoi(instructionRegister.substr(3, 1), nullptr, 16);
    int r3 = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    std::cout<<"\nassigning the results of ANDing registers "<<std::hex<<std::uppercase<<r1<<" and "<<r2<<" to register "<<r3<<".."<<std::endl;

    int sum = rgstr.getCell(r1) & rgstr.getCell(r2);
    rgstr.setCell(r3, sum);
}

void CPU::instruction9() {
    int r1 = std::stoi(instructionRegister.substr(2, 1), nullptr, 16);
    int r2 = std::stoi(instructionRegister.substr(3, 1), nullptr, 16);
    int r3 = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    std::cout<<"\nassigning the results of XORing registers "<<std::hex<<std::uppercase<<r1<<" and "<<r2<<" to register "<<r3<<".."<<std::endl;

    int sum = rgstr.getCell(r1) ^ rgstr.getCell(r2);
    rgstr.setCell(r3, sum);
}

void CPU::instructionA() {
    int r = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    int shift = std::stoi(instructionRegister.substr(3, 1), nullptr, 16);
    std::string binary = hexToBinary(rgstr.getCell(r));
    std::string result = binary.substr(binary.length()-shift);
    int j = 0;
    for(int i =result.length(); i<binary.length();i++) {
        result+= binary[j];
        j++;
    }
    rgstr.setCell(r,binaryToDecimal(result));
    std::cout<<"-> rotating the binary patterin in register "<<std::hex<<std::uppercase<<r<<" "<<shift<<" times\n";

}

void CPU::instructionB() {
    int r = std::stoi(instructionRegister.substr(1, 1), nullptr, 16);
    int memoryAddress = std::stoi(instructionRegister.substr(2, 2), nullptr, 16);
    std::cout<<"-> jumping to the memory address "<<std::hex<<std::uppercase<<memoryAddress<<" if the contents of register "<<r
    <<" is eqult to the contens of register 0..\n";
    if (rgstr.getCell(0) == rgstr.getCell(r)) {
        programCounter = memoryAddress;
        programCounter -= 2;
    }
}
