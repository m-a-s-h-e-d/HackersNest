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
	}
	else
	{
		m_isBuilding = false;
	}

	auto cfgMgr = GameEngine::ConfigurationManager::GetInstance();
	
	auto newPos = GetEntity()->GetPos() + wantedVel;

	if (newPos.y < 0)
	{
		newPos.y = 0;
	}
	if (newPos.y > cfgMgr->GetWindowSize()->y)
	{
		newPos.y = cfgMgr->GetWindowSize()->y;
	}
	if (newPos.x < 0)
	{
		newPos.x = 0;
	}
	if (newPos.x > cfgMgr->GetWindowSize()->x)
	{
		newPos.x = cfgMgr->GetWindowSize()->x;
	}

	GetEntity()->SetPos(newPos);

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