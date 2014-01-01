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
