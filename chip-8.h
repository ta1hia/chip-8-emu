#ifndef CHIP8_H
#define CHIP8_H

class Chip8 {

private:
	unsigned short pc_;
	unsigned short sp_;
	unsigned short I_;
	unsigned short opcode_;
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned char graphics_[64 * 32];
	unsigned char V_[16];
	unsigned short stack_[16];
	unsigned char key_[16];

public:
	Chip8();
	~Chip8();

	void initialize();
	void emulate_cycle();

};

#endif 
