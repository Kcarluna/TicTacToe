#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <random>
#include "Tile.h"

#define BOARD_SIZE 750

#define BAR_COUNT 4
#define BOARD_BAR_WIDTH 25
#define BOARD_BAR_PADDING 45
#define BOARD_BAR_CENTERPOINT 15

#define ROWS 3
#define COLS 3

#define TILES (ROWS * COLS)

class Board {
	friend int random(int lbound, int ubound);
private:
	SDL_Rect m_board;
	SDL_Rect m_bars[BAR_COUNT];
	std::vector<Tile> m_tiles;

	int m_w;
	int m_h;
	int m_padding;

	char m_char = 'x';
	char m_winner;
	char m_ttt[ROWS][COLS] = {0};
public:
	Board() = default;
	Board(int w, int h);
	std::vector<Tile> generate_tiles();

	void resize_tiles();
	void resize(int w, int h);
	char winner() const;
	bool game_over();
	void reset();
	void random_tile(TTF_Font *font);
	bool clicked(int x, int y);
	void update_ttt(int players);
	void update(int x, int y, int players, TTF_Font *font);
	void render(SDL_Renderer *renderer);
};
