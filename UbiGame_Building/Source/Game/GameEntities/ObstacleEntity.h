#pragma once

#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/InteractableComponent.h"

namespace Game
{

	class ObstacleEntity : public GameEngine::Entity
	{
	public:
		ObstacleEntity();
		~ObstacleEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		float getTimer() const;

		virtual void Update() override;

	protected:
		int m_health;
		float m_timeActive;
		
		GameEngine::SpriteRenderComponent* m_renderComponent;
		GameEngine::InteractableComponent* m_interactableComponent;
	};
}

