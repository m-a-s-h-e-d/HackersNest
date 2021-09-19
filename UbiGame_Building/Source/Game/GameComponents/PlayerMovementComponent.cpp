#include "PlayerMovementComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/AnimationManager.h"
#include "GameEngine/Util/ConfigurationManager.h"

#include "Game/GameComponents/PlayerSoundComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{
	m_isBuilding = false;
}


PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
	m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
	m_playerSoundComponent = GetEntity()->GetComponent<PlayerSoundComponent>();
}


void PlayerMovementComponent::Update()
{
	Component::Update();

	if (GameEngine::GameEngineMain::GetInstance()->IsGameOver())
	{
		return;
	}

	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	static float playerVel = 200.f; //Pixels/s

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		wantedVel.x -= playerVel * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		wantedVel.x += playerVel * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		wantedVel.y -= playerVel * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		wantedVel.y += playerVel * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_isBuilding = true;

		bool is_repairing = true; // Default to true for debug
		if (m_playerSoundComponent && is_repairing)
		{
			m_playerSoundComponent->RequestSound();
		}
	}
	else
	{
		m_isBuilding = false;
	}

	auto cfgMgr = GameEngine::ConfigurationManager::GetInstance();

	auto liftEntity = GameEngine::GameEngineMain::GetInstance()->GetEntitiesByTag("Lift")[0];
	
	auto newPos = GetEntity()->GetPos() + wantedVel;

	if (newPos.y < 50)
	{
		newPos.y = 50;
	}
	if (newPos.y > cfgMgr->GetWindowSize()->y - 50)
	{
		newPos.y = cfgMgr->GetWindowSize()->y - 50;
	}
	if (newPos.x < 50)
	{
		newPos.x = 50;
	}
	if (newPos.x > cfgMgr->GetWindowSize()->x - 50)
	{
		newPos.x = cfgMgr->GetWindowSize()->x - 50;
	}

	auto newLiftPos = newPos;
	newLiftPos.x += 45;
	newLiftPos.y -= 650;

	GetEntity()->SetPos(newPos);
	liftEntity->SetPos(newLiftPos);

	if (m_animComponent)
	{
		if (m_isBuilding)
		{
			if (m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerHammer)
			{
				m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerHammer);
			}
		}
		else if(m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerIdle)
		{
			m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerIdle);
		}
	}

	

	
	static float rotationVel = 50.f; //Deg/s
	static float maxRotation = 0.f; //Deg
	
	float currentRotation = GetEntity()->GetRot();
	float wantedRot = 0.f;
	bool  reseting = false;

	if (wantedVel.y > 0.f)
		wantedRot = rotationVel;
	else if (wantedVel.y < 0.f)
		wantedRot = -rotationVel;
	else
	{				
		if (currentRotation > 0.f)
			wantedRot = -rotationVel;
		else if (currentRotation < 0.f)
			wantedRot = rotationVel;
	}

	float frameRot = wantedRot * dt;
	float totalRot = currentRotation + frameRot;

	if (!reseting)
	{
		if (totalRot > maxRotation)
			totalRot = maxRotation;
		else if (totalRot < -maxRotation)
			totalRot = -maxRotation;
	}
	else
	{
		if (currentRotation > 0.f && totalRot < 0.f)
			totalRot = 0.f;
		if (currentRotation < 0.f && totalRot > 0.f)
			totalRot = 0.f;
	}

	GetEntity()->SetRotation(totalRot);
}