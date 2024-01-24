#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <string>

class SpriteComponent :public Component {
	SDL_Renderer* m_renderer;
	PositionComponent* m_position;
	ImageHandling m_image;
public:
	SpriteComponent() = default;
	SpriteComponent(std::string path, SDL_Renderer* renderer) : m_renderer(renderer) {
		m_image.texture = TextureManager::loadTexture(path.c_str(), m_renderer);
	}
	void init() override {
		m_position = &m_entity->getComponent<PositionComponent>();
		m_image.srcR.x = m_image.srcR.y = 0;
		m_image.srcR.w = TextureManager::w_texture_dimension;
		m_image.srcR.h = TextureManager::h_texture_dimension;
		m_image.dstR.w = TextureManager::w_texture_dimension;
		m_image.dstR.h = TextureManager::h_texture_dimension;
	}

	void resetTexture(std::string path) {
		m_image.texture = TextureManager::loadTexture(path.c_str(), m_renderer);
	}

	void update(SDL_Event* m_event) override {
		m_image.dstR.x = static_cast<int>(m_position->getPosition().x);
		m_image.dstR.y = static_cast<int>(m_position->getPosition().y);
		m_image.dstR.w = m_position->getwidth() * m_position->getscale();
		m_image.dstR.h = m_position->getheight() * m_position->getscale();
	}
	void draw(SDL_Renderer* renderer) override {
		TextureManager::Draw(m_image.texture, m_image.srcR, m_image.dstR, m_renderer);
	}
};