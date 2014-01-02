#include <iostream>
#include <iomanip>

#include <GL/glut.h>
#include "chip-8.h"
#include "defs.h"

using namespace std;

Chip8 chip8;

int main(int argc, char **argv) {

    chip8.testPrintV();
    chip8.testPrintRegisters();

    chip8.testLoadV();
    chip8.testPrintV();

    chip8.test8XYN();


    char x,y;
    x = 5;
    y = 2;

    cout << x << " : 0x" << hex << x << endl;
    cout << y << " : 0x" << hex << y << endl;

	return 0;
}
