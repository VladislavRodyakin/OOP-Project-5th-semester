#pragma once
#include "EntityComponentSystem.h"
class PositionComponent : public Component {
private:
	int m_xpos = 0, m_ypos = 0;
public:
	PositionComponent() = default;
	~PositionComponent() = default;
	int x() { return m_xpos; }
	int y() { return m_ypos; }
	void init() override {
		m_xpos = 0;
		m_ypos = 0;
	}
	void update() override {
		m_xpos++;
		m_ypos++;
	}
	void setPos(int x, int y) {
		m_xpos = x;
		m_ypos = y;
	}
	void draw() { return; }
};

