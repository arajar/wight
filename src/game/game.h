#pragma once

#include "Screens/Screen.h"

//////////////////////////////////////////////////////////////////////////

class Game : public w::Screen, private sf::NonCopyable
{
public:
	Game();
	virtual ~Game() {};

public:
	virtual void Run() override;

private:
	void	ProcessEvents();
	void	Update(sf::Time elapsedTime);
	void	Render();

	void	UpdateStatistics(sf::Time elapsedTime);
	void	HandleInput(sf::Keyboard::Key key, bool isPressed);
	
private:
	static const sf::Time	s_timePerFrame;

	sf::RenderWindow		m_window;
	sf::Font				m_font;
	sf::Text				m_statisticsText;
	sf::Time				m_statisticsUpdateTime;

	std::size_t				m_statisticsNumFrames;

	sf::Clock				m_clock;
	sf::Time				m_timeSinceLastUpdate;

};

//////////////////////////////////////////////////////////////////////////
