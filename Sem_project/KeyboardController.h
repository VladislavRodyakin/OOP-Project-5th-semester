#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	PositionComponent* m_position;
	SpriteComponent* m_sprite;

	void init() override
	{
		m_position = &m_entity->getComponent<PositionComponent>();
		m_sprite = &m_entity->getComponent<SpriteComponent>();
	}

	void update(SDL_Event* m_event) override
	{
		if (m_event->type == SDL_KEYDOWN)
		{
			switch (m_event->key.keysym.sym)
			{
			case SDLK_w:
				m_position->getVelocity().y = -1;
				//m_sprite->Play("Walk");
				break;
			case SDLK_a:
				m_position->getVelocity().x = -1;
				/*m_sprite->Play("Walk");
				m_sprite->m_spriteFlip = SDL_FLIP_HORIZONTAL;*/
				break;
			case SDLK_d:
				m_position->getVelocity().x = 1;
				//m_sprite->Play("Walk");
				break;
			case SDLK_s:
				m_position->getVelocity().y = 1;
				//m_sprite->Play("Walk");
				break;
			default:
				break;
			}
		}

		if (m_event->type == SDL_KEYUP)
		{
			switch (m_event->key.keysym.sym)
			{
			case SDLK_w:
				m_position->getVelocity().y = 0;
				//m_sprite->Play("Idle");
				break;
			case SDLK_a:
				m_position->getVelocity().x = 0;
				/*m_sprite->Play("Idle");
				m_sprite->m_spriteFlip = SDL_FLIP_NONE;*/
				break;
			case SDLK_d:
				m_position->getVelocity().x = 0;
				//m_sprite->Play("Idle");
				break;
			case SDLK_s:
				m_position->getVelocity().y = 0;
				//m_sprite->Play("Idle");
				break;
			//case SDLK_ESCAPE:
			//	Game::isRunning = false;
			default:
				break;
			}
		}
	}
	void draw(SDL_Renderer* renderer) { return; }
};