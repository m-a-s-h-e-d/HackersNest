#include "InteractorComponent.h"

#include "GameEngine/Util/InteractionManager.h"
#include "GameEngine/EntitySystem/Components/InteractableComponent.h"
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/Window/Keyboard.hpp>
#include <vector>

using namespace GameEngine;

InteractorComponent::InteractorComponent()
{

}

InteractorComponent::~InteractorComponent()
{

}


void InteractorComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void InteractorComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();
}

void InteractorComponent::Update()
{
	// Using collidables for their bounding boxes
	std::vector<InteractableComponent*>& interactables = InteractionManager::GetInstance()->GetInteractables();

	for (int a = 0; a < interactables.size(); ++a)
	{
		InteractableComponent* colComponent = interactables[a];

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				colComponent->Interact();
			}
		}
	}
}
