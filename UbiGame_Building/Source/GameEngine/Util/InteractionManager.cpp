#include "InteractionManager.h"

#include <assert.h>

using namespace GameEngine;

InteractionManager* InteractionManager::sm_instance = nullptr;

InteractionManager::InteractionManager()
	: m_pendingScore(0)
{

}

InteractionManager::~InteractionManager()
{

}

void InteractionManager::RegisterInteractable(InteractableComponent* interactable)
{
	auto found = std::find(m_collidables.begin(), m_collidables.end(), interactable);
	assert(found == m_collidables.end()); //Drop an assert if we add duplicate;
	if (found == m_collidables.end())
	{
		m_collidables.push_back(interactable);
	}
}


void InteractionManager::UnregisterInteractable(InteractableComponent* interactable)
{
	auto found = std::find(m_collidables.begin(), m_collidables.end(), interactable);
	assert(found != m_collidables.end()); //Drop an assert if we remove a non existing entity;

	if (found != m_collidables.end())
	{
		m_collidables.erase(found);
	}
}
