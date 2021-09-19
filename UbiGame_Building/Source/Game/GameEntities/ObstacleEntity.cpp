#include "ObstacleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/ButtonComponent.h"
#include "GameEngine/Util/AnimationManager.h"

#include <SFML/Graphics.hpp>

using namespace Game;

ObstacleEntity::ObstacleEntity()	
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Tileset);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	//Animation
	m_animComponent = AddComponent<GameEngine::AnimationComponent>();
	
	AddComponent<GameEngine::ButtonComponent>();

	SetEntityTag("Obstacle");
}


ObstacleEntity::~ObstacleEntity()
{

}


void ObstacleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
	
	if (m_animComponent)
	{
		m_animComponent->PlayAnim(GameEngine::EAnimationId::BrickRepair);
	}
}


void ObstacleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
