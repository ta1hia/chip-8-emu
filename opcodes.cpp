#include <cstdlib>
#include "chip-8.h"
#include "defs.h"

int Chip8::op_00E0() {	
	/* Clears the screen */
	for (int i = 0; i < DISPLAY_SIZE; i++) {
		graphics_[i] = 0;
	}
	display_updated_flag_ = true;
	pc_ += 2;
	return SUCCESS;
}

int Chip8::op_1NNN() {
	/* Jumps to address NNN */
	pc_ = opcode_ & 0x0FFF;
	return SUCCESS;
}
int Chip8::op_2NNN() {
	/* Calls subroutine at NNN */
	stack_[sp_] = pc_;
	sp_ += 1;
	pc_ = opcode_ & 0x0FFF;
	return SUCCESS;
}

int Chip8::op_3XNN() {
	/* Skips the next instruction if VX equals NN */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	BYTE condition = (opcode_ & 0x00FF);
	if (V_[x] == condition) {
		pc_ = pc_ + 4;
	} else {
		pc_ = pc_ + 2;
	}
	return SUCCESS;
}

int Chip8::op_4XNN() {
	/* Skips the next instruction if VX doesn't equal NN */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	BYTE condition = (opcode_ & 0x00FF);
	if (V_[x] != condition) {
		pc_ = pc_ + 4;
	} else {
		pc_ = pc_ + 2;
	}
	return SUCCESS;
}

int Chip8::op_5XY0() {
	/* Skips the next instruction if VX equals VY */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	NIBBLE y = (opcode_ & 0x00F0) >> 4;
	if (V_[x] == V_[y]) {
		pc_ = pc_ + 4;
	} else {
        pc_ = pc_ + 2;
	}
	return SUCCESS;
}

int Chip8::op_6XNN() {
	/* Sets VX to NN */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	V_[x] = (opcode_ & 0x00FF);
	pc_ = pc_ + 2;
	return SUCCESS;
}

int Chip8::op_7XNN() {
	/* Adds NN to VX */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	V_[x] += (opcode_ & 0x00FF);
	pc_ = pc_ + 2;
	return SUCCESS;
}

int Chip8::op_8XY0() {
    /* Sets VX to the value of VY.*/
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;
    V_[y] = V_[x];
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip::op_8XY1() {
    /* Sets VX to VX OR VY. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    V_[x] = x | y;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip::op_8XY2() {
    /* Sets VX to VX AND VY. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    V_[x] = x & y;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip::op_8XY3() {
    /* Sets VX to VX XOR VY. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    V_[x] = x ^ y;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip::op_8XY4() {
    /* Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    NIBBLE buffer = V_[x] + V_[y];

    V_[CARRY_FLAG] = (buffer & 0xF0) >> 4;
    V_[x] = V_[x] + V_[y];

    pc_ = pc_ +  2;
    return SUCCESS;
}

int Chip8::op_9XY0() {
    /* Skips the next instruction if VX doesn't equal VY */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	NIBBLE y = (opcode_ & 0x00F0) >> 4;
	
	if (V_[x] != V_[y]) {
		pc_ = pc_ + 4;
	} else {
		pc_ = pc_ + 2;
	}
	return SUCCESS;
}

int Chip8::op_ANNN() {
	/* Sets I to the address NNN */
	I_ = (opcode_ & 0x0FFF);
	pc_ = pc_ + 2;
	return SUCCESS;
}

int Chip8::op_BNNN() {
	/* Jumps to the address NNN plus V0 */
	pc_ = V_[0] + (opcode_ & 0x0FFF);
	return SUCCESS;
}

int Chip8::op_CXNN() {
	/* Sets VX to a random number and NN */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
	BYTE data = (opcode_ & 0x00FF);
	V_[x] = (rand() % 0xFF) & data;
	pc_ = pc_ + 2;
	return SUCCESS;
}

// DXYN here

int Chip8::op_EX9E() {
	/* Skips the next instruction if the key stored in VX is pressed */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;

	if (key_[V_[x]] != 0) {
		pc_ = pc_ + 4;
	} else {
		pc_ = pc_ + 2;
	} 
	
	return SUCCESS;
}

int Chip8::op_EXA1() {
	/* Skips the next instruction if the key stored in VX isn't pressed */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;

	if (key_[V_[x]] == 0) {
		pc_ = pc_ + 4;
	} else {
		pc_ = pc_ + 2;
	} 
	
	return SUCCESS;
}

int Chip8::op_FX07() {
    /* Sets VX to the value of the delay timer */
	NIBBLE x = (opcode_ & 0x0F00) >> 8;
    
    V_[x] = delay_timer_;
    pc_ = pc_ + 2;

    return SUCCESS;
}
