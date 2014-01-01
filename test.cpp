#include <cstdlib>
#include <iostream>
#include <string>

#include "chip-8.h"
#include "defs.h"

using namespace std;

void Chip8::testPrintV() {
    
    for( int i = 0; i < REGISTER_SIZE_16; i++) {
        cout << V_[i] << ", ";
    }
        cout << endl;
}

void Chip8::testPrintRegisters() {
    
        cout << "pc: " << pc_ << ", ";
        cout << "sp: " << sp_ << ", ";
        cout << "I: " << I_ << ", ";
        cout << "opcode: " << opcode_ << ", ";

        cout << endl;
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
