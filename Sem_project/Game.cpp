#include "Game.h"
#include <exception>

Game::Game(const std::string title, int x_window_pos, int y_window_pos, int window_width, int window_height, bool fullscreen) : 
	m_title(title), m_x_window_pos(x_window_pos), m_y_window_pos(y_window_pos),	m_window_width(window_width), m_window_height(window_height), m_fullscreen(fullscreen) {
	m_isRunning = false;
	m_renderer = nullptr;
	m_window = nullptr;
	cnt = 0;
	m_gameObj = nullptr;
	m_map = nullptr;
}
Game::~Game() {

}

void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw std::exception();

	int flag = 0;
	if (m_fullscreen) flag = SDL_WINDOW_FULLSCREEN;

	m_window = SDL_CreateWindow(m_title.c_str(), m_x_window_pos, m_y_window_pos, m_window_width, m_window_height, flag);
	if (!m_window) throw std::exception();

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if (!m_renderer) throw std::exception();
	SDL_SetRenderDrawColor(m_renderer, 20, 20, 20, 255);

	m_isRunning = true;

	m_gameObj = new GameObject("assets/test.png", m_renderer, 0, 0);
	m_map = new Map(10, 10, m_renderer);

}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		m_isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	cnt++;
	m_gameObj->update();
}

void Game::render() {
	SDL_RenderClear(m_renderer);
	//adding renderables
	m_map->drawMap();
	m_gameObj->render();

	SDL_RenderPresent(m_renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}