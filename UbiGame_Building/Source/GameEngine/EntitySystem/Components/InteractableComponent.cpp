#include "InteractableComponent.h"

#include "GameEngine/Util/InteractionManager.h"

#include <assert.h>
#include <GameEngine/GameEngineMain.h>

using namespace GameEngine;

InteractableComponent::InteractableComponent()
	: m_active(0),
	m_timeSinceLastActive(0.f)
{

}

InteractableComponent::~InteractableComponent()
{

}

void InteractableComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();

	InteractionManager::GetInstance()->RegisterInteractable(this);
}

void InteractableComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();

	InteractionManager::GetInstance()->UnregisterInteractable(this);
}

void InteractableComponent::Interact()
{
	m_active = 1;
	m_timeSinceLastActive = 0.f;
}

void InteractableComponent::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	m_timeSinceLastActive += dt;

	if (m_timeSinceLastActive > 0.2f)
	{
		m_active = 0;
		m_timeSinceLastActive = 0.f;
	}
}

bool InteractableComponent::IsActive()
{
	return m_active;
}