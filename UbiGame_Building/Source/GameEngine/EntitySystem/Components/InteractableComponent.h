#pragma once

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <vector>

namespace GameEngine
{
	class InteractableComponent : public CollidableComponent
	{
	public: 
		InteractableComponent();
		virtual ~InteractableComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Interact();

		virtual void Update() override;

		virtual bool IsActive();

	protected:
		bool m_active;

		float m_timeSinceLastActive;
	};
}