#include <iostream>
#include "Game.h"

TTF_Font *init_font() {
	TTF_Font *font = TTF_OpenFont("../fonts/Roboto-Regular.ttf", FONT_SIZE);
	if (!font) {
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		exit(1);
	}
	return font;
}

Game::Game(int w, int h) 
	: m_w(w), m_h(h), m_font(init_font()) {
	m_board = Board(w, h);
	m_scene = Scene(w);
	m_guide = START;
}

void Game::init(SDL_Renderer *renderer) {
	m_scene.init(renderer);
}

void Game::resize(int w, int h) {
	m_w = w;
	m_h = h;
	m_board.resize(w, h);
	m_scene.resize(w);
}

void Game::check_state(int x, int y) {
	m_scene.state(x, y, m_guide);
	if (m_board.game_over() && !(m_guide == START)) {
		m_winner = m_board.winner();
		m_guide = END;
	}
}

void Game::update(int x, int y) {
	if (m_guide != PLAYING) {
		if (m_scene.clicked(x, y) == 1 && m_guide == START) {
			m_players = 1;
			m_guide = PLAYING;
		} else if (m_scene.clicked(x, y) == 1 && m_guide == END) {
			m_board.reset();
			m_guide = START;
		} else if (m_scene.clicked(x, y) == 2) {
			m_players = 2;
			m_guide = PLAYING;
		} else if (m_scene.clicked(x, y) == 0) {
			exit(0);
		}
	} else {
		if (m_board.clicked(x, y)) {
			m_board.update(x, y, m_players, m_font);
		}
	}
}

void Game::render(SDL_Renderer *renderer) {
	if (m_guide == START) {
		m_scene.render_start(renderer);
	} else if (m_guide == PLAYING) {
		m_board.render(renderer);
	} else if (m_guide == END) {
		m_scene.render_end(renderer, m_winner);
	}
	SDL_RenderPresent(renderer);
}
