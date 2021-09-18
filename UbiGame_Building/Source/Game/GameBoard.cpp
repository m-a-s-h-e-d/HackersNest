#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/ObstacleEntity.h"

using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_backGround(nullptr)
	, m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
{
	m_player = new PlayerEntity();
	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(50.f, 50.f));	
	m_player->SetSize(sf::Vector2f(40.f, 40.f));
	
	m_text = new GameEngine::Entity();

    GameEngine::GameEngineMain::GetInstance()->AddEntity(m_text);
	m_text->SetParent(m_player);
    GameEngine::TextRenderComponent* textRenderComponent = m_text->AddComponent<GameEngine::TextRenderComponent>();
    textRenderComponent->SetFont("arial.ttf");
	textRenderComponent->SetString("Player!");
	textRenderComponent->SetZLevel(3);
	m_text->SetLocalPosOffset(sf::Vector2f(1.f, 1.f));
	m_text->SetLocalRotOffset(90.f);

	CreateBackGround();
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			SpawnNewRandomObstacles();
			//SpawnNewRandomTiledObstacles();
		}

		UpdateCheckGameOver();
		UpdateBackGround();
		UpdatePlayerDying();
	}
	else
	{
		// Update game over screen and stuff.
		// Will most likely need to destroy all other entities (no memory leak pls)
	}
}


void GameBoard::UpdateCheckGameOver()
{
	const static int obstacle_max = 7;

	if (std::vector<GameEngine::Entity*> obstacles = GameEngine::GameEngineMain::GetInstance()->GetEntitiesByTag("Obstacle"); obstacles.size() >= obstacle_max)
	{
		m_isGameOver = true;
	}
}


void GameBoard::UpdatePlayerDying()
{
	// Player should not die
}

void GameBoard::SpawnNewRandomObstacles()
{
	static float minNextSpawnTime = 3.0f;
	static float maxNextSpawnTime = 5.0f;

	static float minObstacleXPos = 70.f;
	static float maxObstacleXPos = 430.f;
	static float minObstacleYPos = 50.f;
	static float maxObstacleYPos = 700.f;

	static float obstacleHeight = 96.f;
	static float obstacleWidth = 128.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(obstacleWidth, obstacleHeight);

	SpawnNewObstacle(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

// We will not use this
void GameBoard::SpawnNewRandomTiledObstacles()
{
	static int minObstacleCount = 2;
	static int maxObstacleCount = 7;

	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 350.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));	
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	for (int a = 0; a < obstacleCount; ++a)
	{
		SpawnNewObstacle(pos, size);
		pos.y += size.y;
	}

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* obstacle = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));
}


void GameBoard::CreateBackGround()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(250.f, 375.f));
	bgEntity->SetSize(sf::Vector2f(500.f, 750.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}


void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (m_isGameOver)
	{
		// Update the background sprite to the game over screen on game over
	}

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}