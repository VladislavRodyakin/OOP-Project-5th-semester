#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

class TextureManager {
public:
	static const int w_texture_dimension = 50;
	static const int h_texture_dimension = 50;
	static SDL_Texture* loadTexture(std::string image_path, SDL_Renderer* renderer);
	static void Draw(SDL_Texture* texture, SDL_Rect srcR, SDL_Rect dstR, SDL_Renderer* renderer);
};