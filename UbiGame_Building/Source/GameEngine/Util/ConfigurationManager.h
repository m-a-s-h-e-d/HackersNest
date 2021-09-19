#pragma once

#include <SFML/System/Vector2.hpp>

namespace GameEngine
{

	class ConfigurationManager
	{
	public:
		static ConfigurationManager* GetInstance() { if (!sm_instance) sm_instance = new ConfigurationManager(); return sm_instance; }
		~ConfigurationManager();

		sf::Vector2f* GetWindowSize() { return m_windowSize; }

		void ResizeWindow(sf::Vector2f* newSize);

	private:
		ConfigurationManager();
		static ConfigurationManager* sm_instance;

		sf::Vector2f* m_windowSize;
	};

}
