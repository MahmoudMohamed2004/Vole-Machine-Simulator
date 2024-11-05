#include <iostream>
#include <string>
#include <format>
#include <iomanip>
#include "CPU.h"
#include <cmath>
#include <regex>
#include <fstream>
using namespace std;

enum choice{ LOAD = 1, RUN,RUNONE, DISPLAY, RESET,SET_STARTADDRESS, EXIT};

CPU prg;

string currentIR;
string currentPC;

string startAddress = "10";


int getChoice() {
    currentIR = prg.getIR();
    currentPC = format("{:x}", prg.getPC());
    for(auto& it : currentPC) {
        it = std::toupper(it);
    }
    for(auto& it : currentIR) {
        it = std::toupper(it);
    }
    if(currentIR.empty()) {
        currentIR = "0000";
    }
    if(currentPC.length()<2) {
        currentPC = currentPC = "0";
    }
    cout<<"\nPC: "<< currentPC<<"\nIR: "<<currentIR<<"\n";
    cout<<"\n1- Load new program\n2- Run program\n3- Run one cycle\n"
    <<"4- Display memory, registers and screen\n5- Reset program\n6- Set Start Address (Current = "<<startAddress<<")\n7- Exit\n\n-";
    string s;
    cin>>s;
    while (s!= "1" && s!= "2" &&s!= "3" && s!= "4" &&s!= "5" && s!= "6"&& s!= "7") {
        cout<<"\nInvalid choice\nRe-Enter input: ";
        cin>>s;
    }
    return stoi(s);

}

bool isValidHexadecimal(const std::string& str) {
    // Regular expression for a two-digit hexadecimal number
    std::regex hexPattern("^[0-9A-Fa-f]{2}$");
    return std::regex_match(str, hexPattern);
}

int main() {


    int choice = getChoice();
    while (choice!=choice::EXIT) {
        string inChoice;

        switch (choice) {
            case 1:
                cin.ignore();
            cout<<"\n1- Load from a file\n2- Load from input stream\n\n-";
            cin>>inChoice;
            while (inChoice!= "1" && inChoice!="2") {
                cout<<"Invalid choice\nRe-Enter choice: ";
                cin>>inChoice;
            }
            if(inChoice== "1") {
                string fileName;
                cout<<"\nEnter file name: ";
                cin>>fileName;
                ifstream inputFile (fileName, ios::in);
                prg.loadProgram(inputFile,stoi(startAddress, nullptr, 16));

            } else {
                cout<<"\nLoad program: ";
                cin.ignore();
                prg.loadProgram(cin,stoi(startAddress, nullptr, 16));

            }

            break;
            case 2:
                prg.runProgram();
            break;
            case 3:
                prg.fetchInstruction();
                prg.exectueInstruction();
            break;
            case 4:
                prg.displayMemory();
            break;
            case 5:
                prg.resetProgram();
            break;
            case 6:
                cout<<"\nSet Program Counter: ";
                string hexStr;
                cin>>hexStr;
                 while(!isValidHexadecimal(hexStr)) {
                cout<<"\nInvalid Value\nRe-Enter:";
                cin>>hexStr;
                   }
            startAddress = hexStr;
            break;

        }
        choice = getChoice();
    }





    return 0;
}
