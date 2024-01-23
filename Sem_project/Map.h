#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class Map {
	int m_rows, m_cols;
	SDL_Renderer* m_renderer;
	SDL_Rect m_src, m_dst;
	SDL_Texture* m_white_stars;
	SDL_Texture* m_clear_space;
	SDL_Texture* m_colourful_stars;
	SDL_Texture* m_asteroids;
	std::vector<std::vector<int>> m_map;
public:
	Map(int rows, int cols, SDL_Renderer* renderer, std::vector<std::vector<int>>* preset_map = nullptr);
	~Map();
	void loadMap(std::vector<std::vector<int>> coded_map);
	void drawMap();
};

