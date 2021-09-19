#include "ScoreEntity.h"

#include "GameEngine/Util/InteractionManager.h"

using namespace Game;

ScoreEntity::ScoreEntity()
	: m_score(0)
{
	m_textComponent = AddComponent <GameEngine::TextRenderComponent>();
	m_textComponent->SetZLevel(5);
	m_textComponent->SetColor(sf::Color::White);
	m_textComponent->SetCharacterSizePixels(22);
	m_textComponent->SetFont("opensans.ttf");
	m_textComponent->SetString("0");
}

ScoreEntity::~ScoreEntity()
{

}

void ScoreEntity::Update()
{
	int pscore = GameEngine::InteractionManager::GetInstance()->GetScore();
	if (pscore > 0)
	{
		SetScore(m_score + pscore);
		m_textComponent->SetString(std::to_string(m_score));
		GameEngine::InteractionManager::GetInstance()->ResetScoreCounter();
	}
}