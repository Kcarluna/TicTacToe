#include <iostream>
#include "Scene.h"

TTF_Font *init_font(int size) {
	TTF_Font *font = TTF_OpenFont("../fonts/Roboto-Regular.ttf", size);
	if (!font) {
		std::cerr << "ERROR: " << TTF_GetError() << std::endl;
		exit(1);
	}
	return font;
}

Scene::Scene(int w)
	: m_w(w),  m_font_small(init_font(FONT_SMALL)), m_title_font(init_font(TITLE_FONT)), m_end_font(init_font(END_FONT)) {
	m_title = {(w / 2) - (TITLE_WIDTH / 2), TITLE_PADDING, TITLE_WIDTH, TITLE_HEIGHT};
	m_single = {m_title.x, (m_title.y + m_title.h) + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
	m_double = {(w / 2) - (MENU_WIDTH / 2), (m_title.y + m_title.h) + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
	m_quit = {(m_title.x + m_title.w) - MENU_WIDTH, (m_title.y + m_title.h) + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
	m_winner = {(w / 2) - (TITLE_WIDTH / 2), TITLE_PADDING, TITLE_WIDTH, TITLE_HEIGHT};
	m_play = m_single;
}

Scene::~Scene() {
	if (m_title_t) SDL_DestroyTexture(m_title_t);
	if (m_single_t) SDL_DestroyTexture(m_single_t);
	if (m_double_t) SDL_DestroyTexture(m_double_t);
	if (m_quit_t) SDL_DestroyTexture(m_quit_t);
	if (m_winner_t) SDL_DestroyTexture(m_quit_t);
}

SDL_Rect query_text(const SDL_Rect *rect, SDL_Texture *texture, std::string text) {
	int x = 0, y = 0, w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	if (text == "TicTacToe") {
		x = 25;
		y = 100;
	} else if (text == "Single Player") {
		x = 8;
		y = 15;
	} else if (text == "Two Player") {
		x = 25;
		y = 15;
	} else if (text == "Quit") {
		x = 90;
		y = 15;
	} else if (text == "Play again") {
		x = 35;
		y = 15;
	} else if (text == "Player 'x' wins" || text == "Player 'o' wins") {
		x = 40;
		y = 125;
	} else if (text == "It's a tie!") {
		x = 215;
		y = 125;
	}
	return {rect->x + x, rect->y + y, w, h};
}

void Scene::init(SDL_Renderer *renderer) {
	SDL_Color color = {0, 0, 0};
	m_surface = TTF_RenderText_Solid(m_title_font, "TicTacToe", color);
	m_title_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_title_dstrect = query_text(&m_title, m_title_t, "TicTacToe");

	m_surface = TTF_RenderText_Solid(m_font_small, "Single Player", color);
	m_single_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_single_dstrect = query_text(&m_single, m_single_t, "Single Player");

	m_surface = TTF_RenderText_Solid(m_font_small, "Two Player", color);
	m_double_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_double_dstrect = query_text(&m_double, m_double_t, "Two Player");

	m_surface = TTF_RenderText_Solid(m_font_small, "Quit", color);
	m_quit_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_quit_dstrect = query_text(&m_quit, m_quit_t, "Quit");

	m_surface = TTF_RenderText_Solid(m_font_small, "Play again", color);
	m_play_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_play_dstrect = query_text(&m_play, m_play_t, "Play again");
}

void Scene::resize(int w) {
	m_w = w;

	m_title = {(w / 2) - (TITLE_WIDTH / 2), TITLE_PADDING, TITLE_WIDTH, TITLE_HEIGHT};
	m_title_dstrect = query_text(&m_title, m_title_t, "TicTacToe");

	m_single = {m_title.x, (m_title.y + m_title.h) + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
	m_single_dstrect = query_text(&m_single, m_single_t, "Single Player");

	m_double = {(w / 2) - (MENU_WIDTH / 2), (m_title.y + m_title.h) + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
	m_double_dstrect = query_text(&m_double, m_double_t, "Two Player");

	m_quit = {(m_title.x + m_title.w) - MENU_WIDTH, (m_title.y + m_title.h) + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
	m_quit_dstrect = query_text(&m_quit, m_quit_t, "Quit");

	m_winner = {(w / 2) - (TITLE_WIDTH / 2), TITLE_PADDING, TITLE_WIDTH, TITLE_HEIGHT};

	m_play = m_single;
	m_play_dstrect = query_text(&m_play, m_play_t, "Play again");
}

int Scene::clicked(int x, int y) const {
	SDL_Point point = {x, y};
	if (SDL_PointInRect(&point, &m_single)) {
		return ONE_PLAYER;
	} else if (SDL_PointInRect(&point, &m_double)) {
		return TWO_PLAYER;
	} else if (SDL_PointInRect(&point, &m_quit)) {
		return QUIT;
	}
	return -1;
}

void Scene::state(int x, int y, int guide) {
	SDL_Point point = {x, y};
	if (guide == 0 || guide == 2) {
		if (SDL_PointInRect(&point, &m_single) || SDL_PointInRect(&point, &m_play)) {
			m_hover = true;
			m_hover_rect = m_single;
		} else if (SDL_PointInRect(&point, &m_double) && guide == 0) {
			m_hover = true;
			m_hover_rect = m_double;
		} else if (SDL_PointInRect(&point, &m_quit)) {
			m_hover = true;
			m_hover_rect = m_quit;
		} else {
			m_hover = false;
			m_hover_rect = {};
		}
	}
}

void Scene::render_start(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 43, 73, 138, SDL_ALPHA_OPAQUE);

	SDL_RenderFillRect(renderer, &m_title);
	SDL_RenderFillRect(renderer, &m_single);
	SDL_RenderFillRect(renderer, &m_double);
	SDL_RenderFillRect(renderer, &m_quit);
	if (m_hover) {
		SDL_SetRenderDrawColor(renderer, 60, 80, 145, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &m_hover_rect);
	}
	SDL_RenderCopy(renderer, m_single_t, NULL, &m_single_dstrect);
	SDL_RenderCopy(renderer, m_double_t, NULL, &m_double_dstrect);
	SDL_RenderCopy(renderer, m_title_t, NULL, &m_title_dstrect);
	SDL_RenderCopy(renderer, m_quit_t, NULL, &m_quit_dstrect);
}

void Scene::render_end(SDL_Renderer *renderer, char c) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 43, 73, 138, SDL_ALPHA_OPAQUE);
	SDL_Color color = {0, 0, 0};
	if (c == 'x') {
		m_surface = TTF_RenderText_Solid(m_end_font, "Player 'x' wins", color);
		m_winner_t = SDL_CreateTextureFromSurface(renderer, m_surface);
		SDL_FreeSurface(m_surface);
		m_winner_dstrect = query_text(&m_winner, m_winner_t, "Player 'x' wins");
	} else if (c == 'o') {
		m_surface = TTF_RenderText_Solid(m_end_font, "Player 'o' wins", color);
		m_winner_t = SDL_CreateTextureFromSurface(renderer, m_surface);
		SDL_FreeSurface(m_surface);
		m_winner_dstrect = query_text(&m_winner, m_winner_t, "Player 'o' wins");
	} else if (c == 't') {
		m_surface = TTF_RenderText_Solid(m_end_font, "It's a tie!", color);
		m_winner_t = SDL_CreateTextureFromSurface(renderer, m_surface);
		SDL_FreeSurface(m_surface);
		m_winner_dstrect = query_text(&m_winner, m_winner_t, "It's a tie!");
	}
	SDL_RenderFillRect(renderer, &m_winner);
	SDL_RenderFillRect(renderer, &m_quit);
	SDL_RenderFillRect(renderer, &m_play);
	if (m_hover) {
		SDL_SetRenderDrawColor(renderer, 60, 80, 145, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &m_hover_rect);
	}
	SDL_RenderCopy(renderer, m_winner_t, NULL, &m_winner_dstrect);
	SDL_RenderCopy(renderer, m_quit_t, NULL, &m_quit_dstrect);
	SDL_RenderCopy(renderer, m_play_t, NULL, &m_play_dstrect);
}
