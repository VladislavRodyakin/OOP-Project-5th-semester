#pragma once
#include <SDL.h>
#include "ColliderComponent.h"

class Collision {
public:
	static bool AABB(SDL_Rect& recA, SDL_Rect& recB);
	static bool AABB(ColliderComponent& colA, ColliderComponent& colB);
};
