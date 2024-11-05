#include "Register.h"
#include <iostream>
#include <iomanip>
void Register::setCell(const int& address, const int& value) {
    registerCells[address] = value;
}

int Register::getCell(const int& address) {
    return registerCells[address];
}

void Register::clear() {
    for (auto& cell : registerCells) {
        cell = 0;
    }
}

void Register::display() {
    std::cout<<std::endl;
    for(int i = 0 ; i< 16; i++) {
        std::cout<<"R"<<std::setw(3)<<std::left<<std::setfill(' ')<<std::uppercase<<std::hex<<i<<std::setw(2)<<std::setfill('0')
        <<registerCells[i]<<std::endl;
    }
}
