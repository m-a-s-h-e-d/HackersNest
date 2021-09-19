#pragma once

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace GameEngine
{
	class InteractorComponent : public CollidableComponent
	{
	public:
		InteractorComponent();
		virtual ~InteractorComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;
	};
}
