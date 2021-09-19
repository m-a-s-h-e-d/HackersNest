#include "ObstacleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/ButtonComponent.h"
#include "GameEngine/Util/AnimationManager.h"
#include "GameEngine/Util/InteractionManager.h"
#include "GameEngine/GameEngineMain.h"

#include <SFML/Graphics.hpp>

using namespace Game;

ObstacleEntity::ObstacleEntity()
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

	//AddComponent<GameEngine::AnimationComponent>();

	SetEntityTag("Obstacle");
}


ObstacleEntity::~ObstacleEntity()
{

}


void ObstacleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void ObstacleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

void ObstacleEntity::Update()
{
	Entity::Update();

	auto dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (m_interactableComponent->IsActive())
	{
		m_timeActive += dt;

		if (m_timeActive >= 0.4f)
		{
			if (--m_health == 0)
			{
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
				GameEngine::InteractionManager::GetInstance()->IncrementScore();
			}

			if (m_renderComponent)
			{
				m_renderComponent->SetTileIndex(5 - m_health, 0);
				m_renderComponent->UpdateTileRect();
			}

			m_timeActive = 0.f;
		}
	}
}

