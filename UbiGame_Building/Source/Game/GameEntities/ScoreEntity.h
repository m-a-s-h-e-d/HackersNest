#pragma once

#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"

namespace Game
{
	class ScoreEntity : public GameEngine::Entity
	{
	public:
		ScoreEntity();
		~ScoreEntity();

		void SetScore(int score) { m_score = score; }

		virtual void Update() override;

	private:
		int m_score;

		GameEngine::TextRenderComponent* m_textComponent;
	};
}
