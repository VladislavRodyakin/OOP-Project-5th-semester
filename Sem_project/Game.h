#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "EntityComponentSystem.h"
#include "Components.h"
#include <string>

class Game {
	std::string m_title;
	bool m_isRunning, m_fullscreen;
	int m_x_window_pos, m_y_window_pos, m_window_width, m_window_height;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	GameObject* m_gameObj;
	Map* m_map;
	//Manager m_manager;
	//Entity m_newPlayer;
	long long cnt;
	SDL_Event m_event;
public:
	Game(const std::string title = "Game", int x_window_pos = SDL_WINDOWPOS_CENTERED, int y_window_pos = SDL_WINDOWPOS_CENTERED, 
		int window_width = 1600, int window_height = 900, bool fullscreen = false);
	~Game();
	void init();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return m_isRunning; }
};
