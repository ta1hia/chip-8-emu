#include <cstdlib>
#include <iostream>
#include <string>

#include <iomanip>

#include "chip-8.h"
#include "defs.h"

using namespace std;

void Chip8::testPrintV() {
    
    for( int i = 0; i < REGISTER_SIZE_16; i++) {
        cout << hex << V_[i] << ", ";
    }
        cout << endl;
}

void Chip8::testPrintRegisters() {
    
        char h = 0x0d;

        cout << "pc: " << pc_ << endl;
        cout << "sp: " << sp_ << endl;
        cout << "I: " << I_ << endl;
        cout << "opcode: " << opcode_ << endl;
        cout << "hex 13: " << hex << h << endl;

        cout << endl;
}

void Chip8::testLoadV() {
    
    for( int i = 0; i < REGISTER_SIZE_16; i++) {
        V_[i] = 0x0d;
    }
}
/*
    test methods
    void testPrintV();
    void testPrintRegisters();
    void testPrintStack();
    
    unsigned short 	pc_;
	unsigned short 	sp_;
	unsigned short 	I_;
	unsigned short 	opcode_;

	unsigned char 	delay_timer_;
	unsigned char 	sound_timer_;

	unsigned char 	V_[REGISTER_SIZE_16];
	unsigned short 	stack_[STACK_SIZE];
	unsigned char 	memory_[RAM_SIZE];


*/
