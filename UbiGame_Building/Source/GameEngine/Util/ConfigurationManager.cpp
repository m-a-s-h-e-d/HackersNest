#include "ConfigurationManager.h"

using namespace GameEngine;

ConfigurationManager* ConfigurationManager::sm_instance = nullptr;
	
ConfigurationManager::ConfigurationManager()
	: m_windowSize(nullptr)
{
	m_windowSize = new sf::Vector2f(500, 750);
}

ConfigurationManager::~ConfigurationManager()
{

}

void ConfigurationManager::ResizeWindow(sf::Vector2f* newSize)
{
	m_windowSize = newSize;
}

