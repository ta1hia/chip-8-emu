#include "chip8.h"
#include "defs.h"

int Chip8::op_00E0() {	
	/* Clears the screen */
	while (int i = 0; i < DISPLAY_SIZE; i++) {
		graphics_[i] = 0;
	}
	display_updated_flag_ = true;
	pc += 2;
	return SUCCESS;
}

int Chip8::op_1NNN() {
	/* Jumps to address NNN */
	pc = opcode_ & 0x0FFF;
	return SUCCESS;
}
int Chip8::op_2NNN() {
	/* Calls subroutine at NNN */
	stack_[sp_] = pc;
	sp_ += 1;
	pc = opcode_ & 0x0FFF;
	return SUCCESS;
}
