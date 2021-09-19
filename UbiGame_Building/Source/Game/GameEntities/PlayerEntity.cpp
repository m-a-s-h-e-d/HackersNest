#include "PlayerEntity.h"

#include "Game/GameComponents/PlayerSoundComponent.h"
#include "Game/GameComponents/PlayerCameraComponent.h"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/EntitySystem/Components/InteractorComponent.h"
#include "GameEngine/Util/AnimationManager.h"

using namespace Game;

PlayerEntity::PlayerEntity()
{
	//Movement
	m_playerMovementComponent = AddComponent<PlayerMovementComponent>();

	//Render 
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();	
	m_renderComponent->SetTexture(GameEngine::eTexture::Player);
	m_renderComponent->SetZLevel(3);

	//Animation
	m_animComponent = AddComponent<GameEngine::AnimationComponent>();
		
	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();

	//Sound
	GameEngine::SoundComponent* const soundComponent = AddComponent<GameEngine::SoundComponent>();
	soundComponent->SetNumSimultaneousSounds(2); // Hard coded 5 simultaneous sounds for the player
												 
	m_playerSoundComponent = AddComponent<PlayerSoundComponent>();

	//Camera control
	AddComponent<PlayerCameraComponent>();

	// Interact with environment
	AddComponent<GameEngine::InteractorComponent>();
}

 
PlayerEntity::~PlayerEntity()
{

}


void PlayerEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();

	m_playerSoundComponent->PlayMusicLoop();

	if (m_animComponent)
	{
		m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerIdle);
	}
	
	SetEntityTag("Player");
}


void PlayerEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
