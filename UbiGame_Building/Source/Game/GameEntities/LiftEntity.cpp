#include "LiftEntity.h"

using namespace Game;

LiftEntity::LiftEntity()
{
	//Render 
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetTexture(GameEngine::eTexture::Lift);
	m_renderComponent->SetZLevel(4);
}


LiftEntity::~LiftEntity()
{

}


void LiftEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();

	SetEntityTag("Lift");
}


void LiftEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
