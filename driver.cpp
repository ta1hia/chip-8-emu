#include <iostream>
#include <iomanip>

#include "SDL2/SDL.h"
#include "chip-8.h"
#include "defs.h"

using namespace std;

Chip8 chip8;

uint8_t keymap[16] = {
    SDLK_x,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_q,
    SDLK_w,
    SDLK_e,
    SDLK_a,
    SDLK_s,
    SDLK_d,
    SDLK_z,
    SDLK_c,
    SDLK_4,
    SDLK_r,
    SDLK_f,
    SDLK_v,
};

int main(int argc, char **argv) {

    /* Tests */
    chip8.testPrintV();
    chip8.testPrintRegisters();
    chip8.testLoadV();
    chip8.testPrintV();
    chip8.test8XYN();

    /* SDL initialization */
    SDL_Window* window = NULL;


    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(FAILURE);
    }

    /* Window */
    window = SDL_CreateWindow(
            "CHIP-8 Emulator",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    /* Renderer */
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    /* Texture */
    SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
	    SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            64, 32);

    /* Load ROM (hardcoded for now!) */
    if (chip8.load())
        return FAILURE;

    /* Emulation cycle */
    while (true) {
        chip8.emulate_cycle();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
		exit(SUCCESS);
	    }

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    exit(SUCCESS);

		/* Load triggered */
                if (e.key.keysym.sym == SDLK_F1)
                    goto load;      

                for (int i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i]) {
                        chip8.key[i] = 1;
                    }
                }
            }

            if (e.type == SDL_KEYUP) {
                for (int i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i]) {
                        chip8.key[i] = 0;
                    }
                }
            }
        }
    }
}
