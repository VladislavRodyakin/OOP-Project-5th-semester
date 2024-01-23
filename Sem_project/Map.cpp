#include "Map.h"
#include "TextureManager.h"

std::vector<std::vector<int>> mapFill(int rows, int cols, int code = 0) {
	std::vector<std::vector<int>> map;
	std::vector<int> tmp;
	for (int row = 0; row < rows; row++) {
		map.push_back(tmp);
		for (int col = 0; col < cols; col++) {
			map[row].push_back(code);
		}
	}
	return map;
}

Map::Map(int rows, int cols, SDL_Renderer* renderer, std::vector<std::vector<int>>* preset_map) : m_rows(rows), m_cols(cols), m_renderer(renderer) {
	if (!preset_map)
		m_map = mapFill(m_rows, m_cols, 2);
	else
		m_map = *preset_map;

	m_src.x = 0;
	m_src.y = 0;
	m_src.w = TextureManager::w_texture_dimension;
	m_src.h = TextureManager::h_texture_dimension;
	m_dst.x = 0;
	m_dst.y = 0;
	m_dst.h = TextureManager::h_texture_dimension;
	m_dst.w = TextureManager::w_texture_dimension;

	m_white_stars = TextureManager::loadTexture("assets/white_stars_tile.png", m_renderer);
	m_clear_space = TextureManager::loadTexture("assets/clear_space_tile.png", m_renderer);
	m_colourful_stars = TextureManager::loadTexture("assets/colourful_stars_tile.png", m_renderer);
	m_asteroids = TextureManager::loadTexture("assets/asteroids_tile.png", m_renderer);

}

void Map::drawMap() {
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {
			m_dst.x = col * TextureManager::w_texture_dimension;
			m_dst.y = row * TextureManager::h_texture_dimension;
			//change to patterns usage asap
			switch (m_map[row][col]) {
				case 0:
					TextureManager::Draw(m_clear_space, m_src, m_dst, m_renderer);
					break;
				case 1:
					TextureManager::Draw(m_white_stars, m_src, m_dst, m_renderer);
					break;
				case 2:
					TextureManager::Draw(m_colourful_stars, m_src, m_dst, m_renderer);
					break;
				case 3:
					TextureManager::Draw(m_asteroids, m_src, m_dst, m_renderer);
					break;
			}
		}
	}
}
