#pragma once
#include "EntityComponentSystem.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"

class PositionComponent : public Component {
private:
	Vector2D m_position, m_velocity;
	int m_height = TextureManager::h_texture_dimension;
	int m_width = TextureManager::w_texture_dimension;
	int m_scale = 1;
	int m_speed = 3;
	bool m_blocked = false;
public:
	PositionComponent() { m_position = Vector2D(); }
	PositionComponent(int sc): m_scale(sc) {
		m_position = Vector2D();
	}
	PositionComponent(float x, float y) {
		m_position.x = x;
		m_position.y = y;
	}
	PositionComponent(float x, float y, int h, int w, int sc) : m_height(h), m_width(w), m_scale(sc) {
		m_position.x = x;
		m_position.y = y;
	}
	~PositionComponent() = default;
	int posX() { return m_position.x; }
	int posY() { return m_position.y; }
	Vector2D& getPosition() { return m_position; }
	Vector2D& getVelocity() { return m_velocity; }
	int getwidth() { return m_width; }
	int getheight() { return m_height; }
	int& getscale() { return m_scale; }
	void init() override {
		m_velocity.Zero();
	}
	void update(SDL_Event* m_event) override {
		m_position.x += static_cast<int>(m_velocity.x * m_speed);
		m_position.y += static_cast<int>(m_velocity.y * m_speed);
	}
	void draw(SDL_Renderer* renderer) { return; }
};

