#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Scene.h"
#include "Board.h"

#define FONT_SIZE 250

typedef enum {
	START = 0,
	PLAYING,
	END
} Guide;

class Game {
	friend TTF_Font *init_font();
private:
	Board m_board;
	Scene m_scene;
	Guide m_guide;
	int m_w;
	int m_h;
	int m_players;
	char m_winner;

	TTF_Font *m_font = NULL;
	SDL_Surface *m_surface = NULL;
	SDL_Texture *m_texture = NULL;
public:
	Game(int w, int h);
	void init(SDL_Renderer *renderer);
	void resize(int w, int h);

	void check_state(int x, int y);
	void update(int x, int y);
	void render(SDL_Renderer *renderer);
};
