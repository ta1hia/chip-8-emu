#include <iostream>
#include <GL/glut.h>
#include "chip-8.h"

using namespace std;

Chip8 chip8;

int main(int argc, char **argv) {

    chip8.testPrintV();
    chip8.testPrintRegisters();

    chip8.testLoadV();
    chip8.testPrintV();
    chip8.testPrintStack();

	return 0;
}
