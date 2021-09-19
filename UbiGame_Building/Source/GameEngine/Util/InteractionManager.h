#pragma once

#include <vector>

namespace GameEngine
{
	class InteractableComponent;

	class InteractionManager
	{
	public:
		static InteractionManager* GetInstance() { if (!sm_instance) sm_instance = new InteractionManager(); return sm_instance; }
		~InteractionManager();

		void RegisterInteractable(InteractableComponent* interactable);
		void UnregisterInteractable(InteractableComponent* interactable);

		std::vector<InteractableComponent*>& GetInteractables() { return m_collidables; }

	private:
		InteractionManager();
		static InteractionManager* sm_instance;

		std::vector<InteractableComponent*> m_collidables;
	};
}