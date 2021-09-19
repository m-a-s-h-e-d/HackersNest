#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/Util/SoundManager.h"

namespace Game
{
	class PlayerSoundComponent : public GameEngine::Component
	{
	public:
		PlayerSoundComponent();
		virtual ~PlayerSoundComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

		void PlayMusicLoop();
		void RequestSound();

	private:		
		float m_timeSinceLastPlaceBrick;
		float m_timeSinceLastMusicLoop = 100.f;

		GameEngine::SoundManager::SoundId m_musicSoundId;
		GameEngine::SoundManager::SoundId m_brickSoundId;
	};
}


