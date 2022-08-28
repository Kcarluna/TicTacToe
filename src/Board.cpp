#include <iostream>
#include "Board.h"

std::vector<Tile> Board::generate_tiles() {
	std::vector<Tile> temp;
	temp.push_back(Tile({m_bars[2].x, m_bars[0].y, (m_bars[0].x - m_bars[2].x), (m_bars[2].y - m_bars[0].y)}));
	temp.push_back(Tile({(m_bars[0].x + m_bars[0].w), m_bars[0].y, m_bars[1].x - (m_bars[0].x + m_bars[0].w), (m_bars[2].y - m_bars[0].y)}));
	temp.push_back(Tile({(m_bars[1].x + m_bars[1].w), m_bars[1].y, (m_bars[2].x + m_bars[2].w) - (m_bars[1].x + m_bars[1].w), (m_bars[2].y - m_bars[0].y)}));
	temp.push_back(Tile({m_bars[3].x, (m_bars[2].y + m_bars[2].h), (m_bars[0].x - m_bars[3].x), m_bars[3].y - (m_bars[2].y + m_bars[2].h)}));
	temp.push_back(Tile({(m_bars[0].x + m_bars[0].w), (m_bars[2].y + m_bars[2].h), m_bars[1].x - (m_bars[0].x + m_bars[0].w), m_bars[3].y - (m_bars[2].y + m_bars[2].h)}));
	temp.push_back(Tile({(m_bars[1].x + m_bars[1].w), (m_bars[2].y + m_bars[2].h), (m_bars[3].x + m_bars[3].w) - (m_bars[1].x + m_bars[1].w), m_bars[3].y - (m_bars[2].y + m_bars[2].h)}));
	temp.push_back(Tile({m_bars[3].x, (m_bars[3].y + m_bars[3].h), (m_bars[0].x - m_bars[3].x), (m_bars[0].y + m_bars[0].h) - (m_bars[3].y + m_bars[3].h)}));
	temp.push_back(Tile({(m_bars[0].x + m_bars[0].w), (m_bars[3].y + m_bars[3].h), m_bars[1].x - (m_bars[0].x + m_bars[0].w), (m_bars[0].y + m_bars[0].h) - (m_bars[3].y + m_bars[3].h)}));
	temp.push_back(Tile({(m_bars[1].x + m_bars[1].w), (m_bars[3].y + m_bars[3].h), (m_bars[3].x + m_bars[3].w) - (m_bars[1].x + m_bars[1].w), (m_bars[0].y + m_bars[0].h) - (m_bars[3].y + m_bars[3].h)}));
	return temp;
}

Board::Board(int w, int h)
	: m_w(w), m_h(h), m_padding(h - BOARD_SIZE) {
		m_board = {(w / 2) - BOARD_SIZE / 2, (m_padding / 2), BOARD_SIZE, BOARD_SIZE};

		m_bars[0] = {m_board.x + (m_board.w / 3) - BOARD_BAR_CENTERPOINT, m_board.y + (m_padding / 2), BOARD_BAR_WIDTH, (m_board.h - m_padding)};
		m_bars[1] = {m_board.x + (2 * m_board.w / 3) - BOARD_BAR_CENTERPOINT, m_board.y + (m_padding / 2), BOARD_BAR_WIDTH, (m_board.h - m_padding)};
		m_bars[2] = {m_board.x + (m_padding / 2), m_board.y + (m_board.w / 3) - BOARD_BAR_CENTERPOINT, (m_board.w - m_padding), BOARD_BAR_WIDTH};
		m_bars[3] = {m_board.x + (m_padding / 2), m_board.y + (2 * m_board.w / 3) - BOARD_BAR_CENTERPOINT, (m_board.w - m_padding), BOARD_BAR_WIDTH};

		m_tiles = generate_tiles();
	}

void Board::resize_tiles() {
	m_tiles[0].resize({m_bars[2].x, m_bars[0].y, (m_bars[0].x - m_bars[2].x), (m_bars[2].y - m_bars[0].y)});
	m_tiles[1].resize({(m_bars[0].x + m_bars[0].w), m_bars[0].y, m_bars[1].x - (m_bars[0].x + m_bars[0].w), (m_bars[2].y - m_bars[0].y)});
	m_tiles[2].resize({(m_bars[1].x + m_bars[1].w), m_bars[1].y, (m_bars[2].x + m_bars[2].w) - (m_bars[1].x + m_bars[1].w), (m_bars[2].y - m_bars[0].y)});
	m_tiles[3].resize({m_bars[3].x, (m_bars[2].y + m_bars[2].h), (m_bars[0].x - m_bars[3].x), m_bars[3].y - (m_bars[2].y + m_bars[2].h)});
	m_tiles[4].resize({(m_bars[0].x + m_bars[0].w), (m_bars[2].y + m_bars[2].h), m_bars[1].x - (m_bars[0].x + m_bars[0].w), m_bars[3].y - (m_bars[2].y + m_bars[2].h)});
	m_tiles[5].resize({(m_bars[1].x + m_bars[1].w), (m_bars[2].y + m_bars[2].h), (m_bars[3].x + m_bars[3].w) - (m_bars[1].x + m_bars[1].w), m_bars[3].y - (m_bars[2].y + m_bars[2].h)});
	m_tiles[6].resize({m_bars[3].x, (m_bars[3].y + m_bars[3].h), (m_bars[0].x - m_bars[3].x), (m_bars[0].y + m_bars[0].h) - (m_bars[3].y + m_bars[3].h)});
	m_tiles[7].resize({(m_bars[0].x + m_bars[0].w), (m_bars[3].y + m_bars[3].h), m_bars[1].x - (m_bars[0].x + m_bars[0].w), (m_bars[0].y + m_bars[0].h) - (m_bars[3].y + m_bars[3].h)});
	m_tiles[8].resize({(m_bars[1].x + m_bars[1].w), (m_bars[3].y + m_bars[3].h), (m_bars[3].x + m_bars[3].w) - (m_bars[1].x + m_bars[1].w), (m_bars[0].y + m_bars[0].h) - (m_bars[3].y + m_bars[3].h)});
}


void Board::resize(int w, int h) {
	m_w = w;
	m_h = h;

	m_board = {(w / 2) - BOARD_SIZE / 2, (m_padding / 2), BOARD_SIZE, BOARD_SIZE};
	m_board.y += (h / 2) - (BOARD_SIZE / 2);

	m_bars[0] = {m_board.x + (m_board.w / 3) - BOARD_BAR_CENTERPOINT, m_board.y + (m_padding / 2), BOARD_BAR_WIDTH, (m_board.h - m_padding)};
	m_bars[1] = {m_board.x + (2 * m_board.w / 3) - BOARD_BAR_CENTERPOINT, m_board.y + (m_padding / 2), BOARD_BAR_WIDTH, (m_board.h - m_padding)};
	m_bars[2] = {m_board.x + (m_padding / 2), m_board.y + (m_board.w / 3) - BOARD_BAR_CENTERPOINT, (m_board.w - m_padding), BOARD_BAR_WIDTH};
	m_bars[3] = {m_board.x + (m_padding / 2), m_board.y + (2 * m_board.w / 3) - BOARD_BAR_CENTERPOINT, (m_board.w - m_padding), BOARD_BAR_WIDTH};

	resize_tiles();
}

char Board::winner() const {
	return m_winner;
}

bool Board::game_over() {
	int diag_count_x = 0, diag_count_o = 0;
	int inver_diag_count_x = 0, inver_diag_count_o = 0;
	int tie_count = 0;
	for (int i = 0; i < ROWS; i++) {
		if (m_ttt[i][i] == 'x') {
			diag_count_x++;
		} else if (m_ttt[i][i] == 'o') {
			diag_count_o++;
		}
		// NOTE(__LUNA__): 0 0 ^
		//				   1 1 |
		//				   2 2 |
		if (m_ttt[((ROWS - 1) - i)][i] == 'x') {
			inver_diag_count_x++;
		} else if (m_ttt[((ROWS - 1) - i)][i] == 'o') {
			inver_diag_count_o++;
		}
		// NOTE(__LUNA__): 0 2 ^
		//				   1 1 |
		//				   2 0 |
		int row_count_x = 0, row_count_o = 0;
		int col_count_x = 0, col_count_o = 0;
		for (int j = 0; j < COLS; j++) {
			if (m_ttt[i][j] == 'x') {
				row_count_x++;
				tie_count++;
			} else if (m_ttt[i][j] == 'o') {
				row_count_o++;
				tie_count++;
			}
			// NOTE(__LUNA__): 0 0 ^ 1 0 ^ 2 0 ^
			//				   0 1 | 1 1 | 2 1 |
			//				   0 2 | 1 2 | 2 2 |
			if (m_ttt[j][i] == 'x') {
				col_count_x++;
			} else if (m_ttt[j][i] == 'o') {
				col_count_o++;
			}
			// NOTE(__LUNA__): 0 0 ^ 0 1 ^ 0 2 ^
			//				   1 0 | 1 1 | 1 2 |
			//				   2 0 | 2 1 | 2 2 |
			if (row_count_x == 3 || col_count_x == 3 || diag_count_x == 3 || inver_diag_count_x == 3) {
				m_winner = 'x';
				return true;
			} else if (row_count_o == 3 || col_count_o == 3 || diag_count_o == 3 || inver_diag_count_o == 3) {
				m_winner = 'o';
				return true;
			} else if (tie_count == 9) {
				m_winner = 't';
				return true;
			}
		}
	}
	return false;
}

void Board::reset() {
	m_tiles.clear();
	m_tiles = generate_tiles();
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			m_ttt[i][j] = '\0';
		}
	}
}

int random(int lbound, int ubound) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist9(lbound, ubound);
	return dist9(rng);
}

void Board::random_tile(TTF_Font *font) {
	int random_num = random(0, m_tiles.size() - 1);
	while (m_tiles[random_num].has_surface()) {
		random_num = random(0, m_tiles.size() - 1);
	}
	m_tiles[random_num].activate(font);
}

bool Board::clicked(int x, int y) {
	for (auto &tile: m_tiles) {
		if (tile.is_clicked(x, y) && !tile.has_surface()) {
			return true;
		}
	}
	return false;
}

void Board::update_ttt(int players) {
	for (size_t i = 0; i < m_tiles.size(); i++) {
		if (m_tiles[i].active()) {
			switch (i) {
				case 0: {
					if (!m_ttt[0][0]) {
						m_ttt[0][0] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 1: {
					if (!m_ttt[0][1]) {
						m_ttt[0][1] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 2: {
					if (!m_ttt[0][2]) {
						m_ttt[0][2] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 3: {
					if (!m_ttt[1][0]) {
						m_ttt[1][0] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 4: {
					if (!m_ttt[1][1]) {
						m_ttt[1][1] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 5: {
					if (!m_ttt[1][2]) {
						m_ttt[1][2] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 6: {
					if (!m_ttt[2][0]) {
						m_ttt[2][0] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 7: {
					if (!m_ttt[2][1]) {
						m_ttt[2][1] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
				case 8: {
					if (!m_ttt[2][2]) {
						m_ttt[2][2] = m_char;
						m_char = (m_char == 'x') ? 'o' : 'x';
					}
				} break;
			}
		}
	}
	if (players == 1) {
		m_char = 'x';
	}
}

void Board::update(int x, int y, int players, TTF_Font *font) {
	int tie = 0;
	for (auto &tile: m_tiles) {
		tile.update(x, y, m_char, font);
		if (tile.has_surface()) {
			tie++;
		}
		if (players == 1) {
			update_ttt(players);
		}
	}
	if (players == 1 && tie < 9) {
		random_tile(font);
		m_char = 'o';
	}
	update_ttt(players);
}

void Board::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 125, 125, 125, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_board);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRects(renderer, m_bars, BAR_COUNT);
	for (auto &tile: m_tiles) {
		if (tile.active()) {
			tile.render(renderer);
		}
	}
}
