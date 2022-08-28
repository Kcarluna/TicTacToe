#include <iostream>
#include "Tile.h"

Tile::Tile(SDL_Rect tile)
	: m_tile(tile) {
		m_active = false;
	}

Tile::~Tile() {
	if (m_surface) SDL_FreeSurface(m_surface);
	if (m_texture) SDL_DestroyTexture(m_texture);
}

SDL_Rect Tile::query_text() {
	int w;
	int h;
	SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
	return {m_tile.x + (FONT_OFFSET - 5), m_tile.y - FONT_OFFSET, w, h};
}

void Tile::resize(SDL_Rect rect) {
	m_tile.x = rect.x;
	m_tile.y = rect.y;
	m_tile.w = rect.w;
	m_tile.h = rect.h;
	m_dstrect = query_text();
}

bool Tile::has_surface() const {
	return m_surface != NULL;
}

bool Tile::active() const {
	return m_active;
}

bool Tile::is_clicked(int x, int y) const {
	SDL_Point point = {x, y};
	if (SDL_PointInRect(&point, &m_tile)) {
		return true;
	}
	return false;
}

void Tile::activate(TTF_Font *font) {
	m_surface = TTF_RenderText_Solid(font, "o", {0 ,0, 255});
	m_active = true;
}

void Tile::update(int x, int y, char c, TTF_Font *font) {
	const char *txt = new char(c);
	SDL_Point point = {x, y};
	if (SDL_PointInRect(&point, &m_tile) && !m_active) {
		m_active = true;
	}
	if (m_active && !m_surface && c == 'x') {
		m_surface = TTF_RenderText_Solid(font, txt, {255 ,0, 0});
	} else if (m_active && !m_surface && c == 'o') {
		m_surface = TTF_RenderText_Solid(font, txt, {0 ,0, 255});
	}
	delete txt;
}

void Tile::render(SDL_Renderer *renderer) {
	if (m_surface && !m_texture) {
		m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
		m_dstrect = query_text();
	}
	SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_tile);
	SDL_RenderCopy(renderer, m_texture, NULL, &m_dstrect);
}
