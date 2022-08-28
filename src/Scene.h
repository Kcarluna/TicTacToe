#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#define TITLE_WIDTH 1000
#define TITLE_HEIGHT 500
#define TITLE_PADDING 12

#define MENU_WIDTH 300
#define MENU_HEIGHT 100

#define FONT_SMALL 50
#define TITLE_FONT 200

#define END_FONT 150

typedef enum {
	TWO_PLAYER = 2,
	ONE_PLAYER = 1,
	QUIT = 0
} State;

class Scene {
	friend TTF_Font *init_font(int size);
	friend SDL_Rect query_text(const SDL_Rect *rect, SDL_Texture *texture, std::string text);
private:
	int m_w;
	// NOTE(__LUNA__): START
	SDL_Rect m_title;
	SDL_Rect m_single;
	SDL_Rect m_double;
	SDL_Rect m_quit;

	TTF_Font *m_font_small = NULL;
	TTF_Font *m_title_font = NULL;
	TTF_Font *m_end_font = NULL;

	SDL_Surface *m_surface = NULL;
	SDL_Texture *m_title_t = NULL;
	SDL_Rect m_title_dstrect;
	SDL_Texture *m_single_t = NULL;
	SDL_Rect m_single_dstrect;
	SDL_Texture *m_double_t = NULL;
	SDL_Rect m_double_dstrect;
	SDL_Texture *m_quit_t = NULL;
	SDL_Rect m_quit_dstrect;
	// NOTE(__LUNA__): END
	SDL_Rect m_winner;
	SDL_Rect m_play;
	SDL_Texture *m_winner_t = NULL;
	SDL_Texture *m_play_t = NULL;
	SDL_Rect m_winner_dstrect;
	SDL_Rect m_play_dstrect;

	bool m_hover;
	SDL_Rect m_hover_rect;
public:
	Scene() = default;
	Scene(int w);
	~Scene();
	void init(SDL_Renderer *renderer);
	void resize(int w);

	int clicked(int x, int y) const;
	void state(int x, int y, int guide);
	void render_start(SDL_Renderer *renderer) const;
	void render_end(SDL_Renderer *renderer, char c);
};
