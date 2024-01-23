#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(std::string image_path, SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(image_path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcR, SDL_Rect dstR, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &srcR, &dstR);
}
