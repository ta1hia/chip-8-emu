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

	return 0;
}
