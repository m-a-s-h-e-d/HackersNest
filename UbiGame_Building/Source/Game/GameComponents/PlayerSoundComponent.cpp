#include "PlayerSoundComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

using namespace Game;

PlayerSoundComponent::PlayerSoundComponent()
{

}


PlayerSoundComponent::~PlayerSoundComponent()
{

}

void PlayerSoundComponent::OnAddToWorld()
{
	if (GameEngine::SoundComponent* const soundComponent = GetEntity()->GetComponent<GameEngine::SoundComponent>())
	{
		m_musicSoundId = soundComponent->LoadSoundFromFile("Resources/snd/music_loop.wav");
		m_brickSoundId   = soundComponent->LoadSoundFromFile("Resources/snd/place_brick.wav");
	}
}


void PlayerSoundComponent::Update()
{
	Component::Update();

	m_timeSinceLastPlaceBrick += GameEngine::GameEngineMain::GetTimeDelta();
	m_timeSinceLastMusicLoop += GameEngine::GameEngineMain::GetTimeDelta();
}


void PlayerSoundComponent::PlayMusicLoop()
{
	GameEngine::SoundManager::SoundId soundId = m_musicSoundId;
	float& lastPlayTimer = m_timeSinceLastMusicLoop;
	
	if (GameEngine::SoundComponent* const soundComponent = GetEntity()->GetComponent<GameEngine::SoundComponent>())
	{
		soundComponent->PlaySound(soundId);
		lastPlayTimer = 0.0f;
		
		/*if (lastPlayTimer > 10.0f)
		{
			soundComponent->PlaySound(soundId);
			lastPlayTimer = 0.0f;
		}*/
	}
}



void PlayerSoundComponent::RequestSound()
{
	static bool enablePlayerSounds = true;	
	if (!enablePlayerSounds)
		return;

	GameEngine::SoundManager::SoundId soundId = m_brickSoundId;
	float& lastPlayTimer =					    m_timeSinceLastPlaceBrick;
	

	if (GameEngine::SoundComponent* const soundComponent = GetEntity()->GetComponent<GameEngine::SoundComponent>())
	{
		if (lastPlayTimer > 1.0f)
		{
			soundComponent->PlaySound(soundId);
			lastPlayTimer = 0.0f;
		}
	}
}