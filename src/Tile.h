#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#define FONT_OFFSET 50

class Tile {
private:
	SDL_Rect m_tile;
	SDL_Rect m_dstrect;
	bool m_active;

	SDL_Surface *m_surface = NULL;
	SDL_Texture *m_texture = NULL;
public:
	Tile(SDL_Rect tile);
	~Tile();
	SDL_Rect query_text();
	void resize(SDL_Rect rect);

	bool has_surface() const;
	bool active() const;
	bool is_clicked(int x, int y) const;
	void activate(TTF_Font *font);
	void update(int x, int y, char c, TTF_Font *font);
	void render(SDL_Renderer *renderer);
};
