#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdle,
			eTexture::Player,
			sf::Vector2i(0, 0),
			1,
			3)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerHammer,
			eTexture::Player,
			sf::Vector2i(0, 0),
			2,
			6)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BrickRepair,
			eTexture::Tileset,
			sf::Vector2i(0, 0),
			5,
			1)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
