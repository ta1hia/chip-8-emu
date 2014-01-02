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

int Chip8::op_00EE() {
    /* Returns from a subroutine */

    if (sp_ == 0x0) return FAILURE;

    sp_ -= 1;
    pc_ = stack_[sp_] + 2;
    stack_[sp_] = 0;

    return SUCCESS;
}

int Chip8::op_1NNN() {
	/* Jumps to address NNN */
	pc_ = opcode_ & 0x0FFF;
	return SUCCESS;
}
int Chip8::op_2NNN() {
	/* Calls subroutine at NNN */

    if (sp_ + 1 > 0xF) return FAILURE;

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
    V_[x] = V_[y];
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_8XY1() {
    /* Sets VX to VX OR VY. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    V_[x] = x | y;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_8XY2() {
    /* Sets VX to VX AND VY. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    V_[x] = x & y;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_8XY3() {
    /* Sets VX to VX XOR VY. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    V_[x] = x ^ y;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_8XY4() {
    /* Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't. */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    NIBBLE buffer = V_[x] + V_[y];

    V_[CARRY_FLAG] = (buffer & 0x00F0) >> 4;
    V_[x] = (V_[x] + V_[y]) & 0x000F ;

    pc_ = pc_ +  2;
    return SUCCESS;
}

int Chip8::op_8XY5() {
 
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    NIBBLE y = (opcode_ & 0x00F0) >> 4;

    if ( V_[x] < V_[y] ) {
        V_[CARRY_FLAG] = 0;
    }

    else {
        V_[CARRY_FLAG] = 1;
    }

    V_[x] =  V_[x] - V_[y];

    return SUCCESS;

}

int Chip8::op_8XY6() {
    /*
     * Shifts VX right by one. VF is set to the value of the least 
     * significant bit of VX before the shift.[2]
     */

    NIBBLE x = 0;

    return SUCCESS;
}
int Chip8::op_8XY7() {
/*
 * Sets VX to VY minus VX. VF is set to 0 when there's a borrow, 
 * and 1 when there isn't.
 */

    return SUCCESS;
}

int Chip8::op_8XYE() {
/*
 * Shifts VX left by one. VF is set to the value of the most significant
 * bit of VX before the shift.[2]
 */

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

int Chip8::op_FX0A() {
    /* A key press is awaited. When key press detected,
     * it is stored in VX */

    bool is_key_pressed = false;

    for (int i = 0; i < REGISTER_SIZE_16 ; i ++) {

        if (key_[i] != 0) {
            NIBBLE x = (opcode_ & 0x0F00) >> 8;
            is_key_pressed = true;
            V_[x] = key_[i];
            break;
        }
    }

    /* Advance PC if key press detected. Otherwise try again
     * next cycle
     */
    if (is_key_pressed) {
        pc_ = pc_ + 2;
    }

    return SUCCESS;
}

int Chip8::op_FX15() {
    /* Sets the delay timer to VX */
    NIBBLE time = (opcode_ & 0x0F00) >> 8;
    delay_timer_ = time;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_FX18() {
    /* Sets the delay timer to VX */
    NIBBLE time = (opcode_ & 0x0F00) >> 8;
    sound_timer_ = time;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_FX1E() {
    /* Adds VX to I */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;
    I_ += x;
    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_FX29() {
    /* Sets I to the location of the sprite for the character in VX
     * Characters 0-F (in hexadecimal) are represented by a 4x5 font
     */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;

    pc_ = pc_ + 2;

    if (V_[x] >= 0x0 && V_[x] < 0xF) {
        /* Set I to the start index in chip8_fontset */
        I_ = x * 5;
        return SUCCESS;
    } else {
        return FAILURE;
    }

}

int Chip8::op_FX33() {
    /* Store BCD representation of Vx in memory locations I, I+1, and I+2 */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;

    memory_[I_] =       V_[x] / 100;        /* MSD */
    memory_[I_ + 1] =   (V_[x] / 10) % 10;
    memory_[I_ + 2] =   V_[x] % 10;         /* LSD */

    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_FX55() {
    /* Stores V0 to VX in memory starting at address I */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;

    for (int i = 0; i < x + 1 ; i++) {
        memory_[I_ + i] = V_[x];
    }

    pc_ = pc_ + 2;
    return SUCCESS;
}

int Chip8::op_FX65() {
    /* Fills V0 to VX with values from memory starting at address I */
    NIBBLE x = (opcode_ & 0x0F00) >> 8;

    for (int i = 0; i < x + 1 ; i++) {
        V_[x] = memory_[I_ + i];
    }

    pc_ = pc_ + 2;
    return SUCCESS;
}
