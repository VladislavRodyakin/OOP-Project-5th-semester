#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <array>
#include <bitset>

class Component;
class Entity;
class Manager;
using ComponentID = std::size_t;
constexpr std::size_t maxComponents = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}


class Component {
protected:
	Entity* m_entity;
public:
	Entity* getEntity() { return m_entity; }
	void setEntity(Entity* entity) { m_entity = entity; }
	
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Component() {};
};

class Entity {
protected:
	bool m_active = true;
	std::vector<std::unique_ptr<Component>> m_components;
	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
public:
	void update() {
		for (auto& c : m_components)
			c->update();
		for (auto& c : m_components)
			c->draw();
	}
	void draw();
	bool isActive() const {
		return m_active;
	}
	void destroy() {
		m_active = false;
	}

	template<typename T> bool hasComponent() const {
		return m_componentBitSet[getComponentTypeID<T>];
	}

	template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		T* comp(new T(std::forward<TArgs>(mArgs)...));
		comp->setEntity(this);
		std::unique_ptr<Component> uPtr{ comp };
		m_components.emplace_back(std::move(uPtr));
		m_componentArray[getComponentTypeID<T>()] = comp;
		m_componentBitSet[getComponentTypeID<T>()] = true;
		comp->init();
		return *comp;
	}

	template<typename T> T& getComponent() const {
		auto ptr(m_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager {
protected:
	std::vector<std::unique_ptr<Entity>> m_entities;
public:
	void update() {
		for (auto& entity : m_entities)
			entity->update();
	}
	void draw() {
		for (auto& entity : m_entities)
			entity->draw();
	}
	void refresh() {
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity>& mEntity) { return !mEntity->isActive(); }),
			std::end(m_entities));
	}
	Entity& addEntity() {
		Entity* entity = new Entity();
		std::unique_ptr<Entity> entityPtr{ entity };
		m_entities.emplace_back(std::move(entityPtr));
		return *entity;
	}
};