#include "game.h"
//#include <Book/StringHelpers.hpp>

const sf::Time Game::s_timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
: m_window(sf::VideoMode(640, 480), "wight", sf::Style::Close)
, m_font()
, m_statisticsText()
, m_statisticsUpdateTime()
, m_statisticsNumFrames(0)
{
	m_font.loadFromFile("data/fonts/Sansation.ttf");
	m_statisticsText.setFont(m_font);
	m_statisticsText.setPosition(5.f, 5.f);
	m_statisticsText.setCharacterSize(14);
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > s_timePerFrame)
		{
			timeSinceLastUpdate -= s_timePerFrame;

			ProcessEvents();
			Update(s_timePerFrame);
		}

		UpdateStatistics(elapsedTime);
		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			HandleInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			HandleInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::Update(sf::Time elapsedTime)
{

}

void Game::Render()
{
	m_window.clear();
	m_window.draw(m_statisticsText);
	m_window.display();
}

void Game::UpdateStatistics(sf::Time elapsedTime)
{
	m_statisticsUpdateTime += elapsedTime;
	m_statisticsNumFrames += 1;

	if (m_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		m_statisticsText.setString(
			"Frames / Second = " + std::to_string(m_statisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(m_statisticsUpdateTime.asMicroseconds() / m_statisticsNumFrames) + "us");

		m_statisticsUpdateTime -= sf::seconds(1.0f);
		m_statisticsNumFrames = 0;
	}
}

void Game::HandleInput(sf::Keyboard::Key key, bool isPressed)
{

}
