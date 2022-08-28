#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"

static int width  = 1024;
static int height = 768;

typedef struct {
	int x;
	int y;
} Mouse;

void check_val(int val) {
	if (val < 0) {
		std::cerr << "ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

void *check_ptr(void *ptr) {
	if (ptr == NULL) {
		std::cerr << "ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
	return ptr;
}

int main() {
	check_val(SDL_Init(SDL_INIT_VIDEO));
	check_val(TTF_Init());
	SDL_Window *window = static_cast<SDL_Window *>(check_ptr(SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE)));
	SDL_Renderer *renderer = static_cast<SDL_Renderer *>(check_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

	Game game(width, height);
	game.init(renderer);
	Mouse mouse = {0};

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					quit = true;
				} break;
				case SDL_MOUSEMOTION: {
					SDL_GetMouseState(&mouse.x, &mouse.y);
				} break;
				case SDL_MOUSEBUTTONDOWN: {
					game.update(mouse.x, mouse.y);
				} break;
				case SDL_WINDOWEVENT: {
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED: {
							width  = event.window.data1;
							height = event.window.data2;
							game.resize(width, height);
						} break;
					}
				} break;
			}
		}
		game.check_state(mouse.x, mouse.y);
		game.render(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
