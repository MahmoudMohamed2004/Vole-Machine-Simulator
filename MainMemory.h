//
// Created by mmh20 on 10/6/2024.
//

#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

class MainMemory {
    int memoryCells[256]{0};

public:
    void setCell(const int& address, const int& value);
    int getCell(const int& address);
    void clear();
    void loadInstructions(std::istream& cin, const int& startAddress);
    void loadInstructions(std::ifstream& file, const int& startAddress);
    bool validateInstruction(std::string instruction);
};

#endif //MAINMEMORY_H
