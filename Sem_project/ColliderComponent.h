#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <string>
#include <SDL.h>

class ColliderComponent : public Component
{
	SDL_Rect m_collider;
	std::string m_tag;
	SDL_Renderer* m_renderer;
	ImageHandling m_image;

	PositionComponent* m_position;
public:
	ColliderComponent(std::string t, SDL_Renderer* renderer) : m_tag(t), m_renderer(renderer) {};

	ColliderComponent(std::string t, int xpos, int ypos, int size, SDL_Renderer* renderer) : m_tag(t), m_renderer(renderer) {
		m_collider.x = xpos;
		m_collider.y = ypos;
		m_collider.h = m_collider.w = size;
	}

	SDL_Rect& getcollider() { return m_collider; }
	void init() override
	{
		if (!m_entity->hasComponent<PositionComponent>())
		{
			m_entity->addComponent<PositionComponent>();
		}

		m_position = &m_entity->getComponent<PositionComponent>();

		m_image.texture = TextureManager::loadTexture("assets/coltex.png", m_renderer);
		m_image.srcR = { 0, 0, TextureManager::w_texture_dimension, TextureManager::h_texture_dimension };
		m_image.dstR = { m_collider.x, m_collider.y, m_collider.w, m_collider.h };

	}

	void update(SDL_Event* event) override
	{
		if (m_tag != "terrain")
		{
			m_collider.x = static_cast<int>(m_position->getPosition().x);
			m_collider.y = static_cast<int>(m_position->getPosition().y);
			m_collider.w = m_position->getwidth() * m_position->getscale();
			m_collider.h = m_position->getheight() * m_position->getscale();
		}

		/*destR.x = m_collider.x - Game::camera.x;
		destR.y = m_collider.y - Game::camera.y;*/
	}

	void draw(SDL_Renderer* renderer) override
	{
		//TextureManager::Draw(m_image.texture, m_image.srcR, m_image.dstR, m_renderer);
		return;
	}
};