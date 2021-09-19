#include "HoleEntity.h"

#include "GameEngine/GameEngineMain.h"

#include <iostream>

using namespace Game;

HoleEntity::HoleEntity()
	: m_renderComponent(nullptr),
	m_interactableComponent(nullptr),
	m_health(5),
	m_timeActive(0.f)
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Tileset);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	m_interactableComponent = AddComponent<GameEngine::InteractableComponent>();
	

	SetEntityTag("Hole");
}

HoleEntity::~HoleEntity()
{

}


void HoleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void HoleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

void HoleEntity::Update()
{
	Entity::Update();

	auto dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (m_interactableComponent->IsActive())
	{
		m_timeActive += dt;

		if (m_timeActive >= 0.5f)
		{
			if (--m_health == 0)
			{
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
			}
		}
	}
}
