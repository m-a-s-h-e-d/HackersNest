#pragma once

#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/InteractableComponent.h"

namespace Game
{
	class HoleEntity : public GameEngine::Entity
	{
	public:
		HoleEntity();
		~HoleEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;

	private:
		GameEngine::SpriteRenderComponent* m_renderComponent;
		GameEngine::InteractableComponent* m_interactableComponent;

		int m_health;

		float m_timeActive;
	};
}