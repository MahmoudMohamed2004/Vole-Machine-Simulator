//
// Created by mmh20 on 10/6/2024.
//

#ifndef CPU_H
#define CPU_H

#include <string>
#include "MainMemory.h"
#include "Register.h"
#include <iostream>
#include <format>
#include <iomanip>
#include <cmath>
#include "conversion.h"
#include <fstream>
#include <vector>

class CPU {
    int programCounter{0};
    std::string instructionRegister;
    MainMemory mmry;
    Register rgstr;
    std::vector<int> screen     ;
    bool reachedTheEnd = false;

    void incrementProgramCounter();

public:
    void setPC(const int& programCounter);
    int getPC();
    std::string getIR();
    void fetchInstruction();
    bool exectueInstruction();
    void loadProgram(std::istream& cin, const int& startAddress = 16);
    void loadProgram(std::ifstream& file, const int&startAddress = 16);
    void runProgram();
    void resetProgram();
    void displayMemory();
    void displayRegister();
    void displayScreen();
    void instruction1();
    void instruction2();
    void instruction3();
    void instruction3R00();
    void instruction4();
    void instruction5();
    void instruction6();
    void instruction7();
    void instruction8();
    void instruction9();
    void instructionA();
    void instructionB();
};

#endif // CPU_H
