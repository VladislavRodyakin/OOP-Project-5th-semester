#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

struct ImageHandling {
	SDL_Texture* texture;
	SDL_Rect srcR, dstR;
};

class GameObject {
	int m_xpos = 0, m_ypos = 0;
	ImageHandling m_image;
	SDL_Renderer* m_renderer;
public:
	GameObject(std::string texture_path, SDL_Renderer* renderer, int x, int y);
	~GameObject();
	void update();
	void render();
};

