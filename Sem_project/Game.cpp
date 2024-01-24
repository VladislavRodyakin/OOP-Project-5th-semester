#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "SDL.h"
#include "SDL_image.h"
#include <exception>
#include <iostream>

Game::Game(const std::string title, int x_window_pos, int y_window_pos, int window_width, int window_height, bool fullscreen) : 
	m_title(title), m_x_window_pos(x_window_pos), m_y_window_pos(y_window_pos),	m_window_width(window_width), m_window_height(window_height), m_fullscreen(fullscreen) {
	m_isRunning = false;
	m_renderer = nullptr;
	m_window = nullptr;
	cnt = 0;
	m_gameObj = nullptr;
	m_map = nullptr;
	m_event = SDL_Event();
	//m_manager = Manager();
	//m_newPlayer = Entity(m_manager.addEntity());
}
Game::~Game() {

}

//SDL_Event Game::m_event;
Manager m_manager;
auto& m_newPlayer(m_manager.addEntity()); // unresolvable problms with unique_ptr in Components otherwise
auto& m_wall(m_manager.addEntity());


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

	//m_gameObj = new GameObject("assets/test.png", m_renderer, 0, 0);
	m_map = new Map(10, 10, m_renderer);
	m_newPlayer.addComponent<PositionComponent>(2);
	m_newPlayer.addComponent<SpriteComponent>("assets/test.png", m_renderer);
	m_newPlayer.addComponent<KeyboardController>();
	m_newPlayer.addComponent<ColliderComponent>("player", m_renderer);

	m_wall.addComponent<PositionComponent>(200.0f, 200.0f, 100, 50, 1);
	m_wall.addComponent<SpriteComponent>("assets/asteroids_tile.png", m_renderer);
	m_wall.addComponent<ColliderComponent>("wall", m_renderer);
}

void Game::handleEvents() {
	//SDL_Event event;
	SDL_PollEvent(&m_event);
	switch (m_event.type) {
	case SDL_QUIT:
		m_isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	cnt++;
	Vector2D playerPos = m_newPlayer.getComponent<PositionComponent>().getPosition();
	//m_gameObj->update();
	m_manager.refresh();
	m_manager.update(&m_event);
	if (Collision::AABB(m_newPlayer.getComponent<ColliderComponent>().getcollider(), m_wall.getComponent<ColliderComponent>().getcollider())) {
		/*m_newPlayer.getComponent<PositionComponent>().getscale() = 1;
		m_newPlayer.getComponent<PositionComponent>().getVelocity() * -1;
		m_newPlayer.getComponent<PositionComponent>().getscale() = 2;*/
		m_newPlayer.getComponent<PositionComponent>().getPosition() = playerPos;
		std::cout << "player hit collider" << std::endl;
	}
}

void Game::render() {
	SDL_RenderClear(m_renderer);
	//adding renderables
	m_map->drawMap();
	//m_gameObj->render();
	m_manager.draw(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}