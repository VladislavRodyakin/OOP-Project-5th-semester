#include "TextureManager.h"
#include "GameObject.h"

GameObject::GameObject(std::string texture_path, SDL_Renderer* renderer, int x, int y) : m_renderer(renderer), m_xpos(x), m_ypos(y) {
	m_image.texture = TextureManager::loadTexture(texture_path, m_renderer);
	m_image.srcR.h = TextureManager::h_texture_dimension;
	m_image.srcR.w = TextureManager::w_texture_dimension;
	m_image.srcR.x = 0;
	m_image.srcR.y = 0;
	m_image.dstR.w = TextureManager::w_texture_dimension;
	m_image.dstR.h = TextureManager::h_texture_dimension;
}

GameObject::~GameObject()
{
}

void GameObject::update() {
	m_xpos++;
	m_ypos++;

	m_image.dstR.x = m_xpos;
	m_image.dstR.y = m_ypos;
}

void GameObject::render() {
	SDL_RenderCopy(m_renderer, m_image.texture, &m_image.srcR, &m_image.dstR);
}
