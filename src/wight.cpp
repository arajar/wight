#include "pch.h"
#include "game\game.h"
#include "core\Lights\LightManager.h"

int main(int argc, char** argv)
{
	//	Game game;
	//	game.Run();
	//	return 0;

	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Holyspirit Light Test");

	sf::Clock Clock;

	sf::Vertex Wall[] = {
		sf::Vertex(sf::Vector2f(450, 325)), sf::Vertex(sf::Vector2f(300, 200)),
		sf::Vertex(sf::Vector2f(250, 240)), sf::Vertex(sf::Vector2f(400, 365)),
		sf::Vertex(sf::Vector2f(125, 125)), sf::Vertex(sf::Vector2f(100, 100)),
		sf::Vertex(sf::Vector2f(500, 200)), sf::Vertex(sf::Vector2f(600, 300)),
		sf::Vertex(sf::Vector2f(500, 300)), sf::Vertex(sf::Vector2f(600, 200)),
		sf::Vertex(sf::Vector2f(125, 425)), sf::Vertex(sf::Vector2f(125, 475)),
		sf::Vertex(sf::Vector2f(125, 475)), sf::Vertex(sf::Vector2f(175, 475))
	};

	new LightManager();

	LightManager::GetInstance()->m_lightSmooth = 2;
	LightManager::GetInstance()->m_basicLight = sf::Color(128, 128, 128);

	LightManager::GetInstance()->AddWall(sf::Vector2f(450, 325), sf::Vector2f(300, 200));
	LightManager::GetInstance()->AddWall(sf::Vector2f(250, 240), sf::Vector2f(400, 365));
	LightManager::GetInstance()->AddWall(sf::Vector2f(100, 100), sf::Vector2f(125, 125));
	LightManager::GetInstance()->AddWall(sf::Vector2f(500, 200), sf::Vector2f(600, 300));
	LightManager::GetInstance()->AddWall(sf::Vector2f(500, 300), sf::Vector2f(600, 200));
	LightManager::GetInstance()->AddWall(sf::Vector2f(125, 425), sf::Vector2f(125, 475));
	LightManager::GetInstance()->AddWall(sf::Vector2f(125, 475), sf::Vector2f(175, 475));

	LightManager::GetInstance()->AddWall(sf::Vector2f(200, 200), sf::Vector2f(400, 200));
	LightManager::GetInstance()->AddWall(sf::Vector2f(200, 200), sf::Vector2f(200, 400));
	LightManager::GetInstance()->AddWall(sf::Vector2f(400, 400), sf::Vector2f(200, 400));
	LightManager::GetInstance()->AddWall(sf::Vector2f(400, 400), sf::Vector2f(400, 200));
	
	LightEntity light, light2, light3, DirectionalLight;

	light = LightManager::GetInstance()->AddDynamicLight();
	light2 = LightManager::GetInstance()->AddDynamicLight();

	light3 = LightManager::GetInstance()->AddDynamicLight(sf::Vector2f(600, 200), 255, 160, 16, sf::Color(0, 255, 0));

	LightManager::GetInstance()->AddStaticLight(sf::Vector2f(110, 490), 160, 96, 8, sf::Color(255, 255, 255));

	LightManager::GetInstance()->SetPosition(light, sf::Vector2f(375, 275));

	LightManager::GetInstance()->SetIntensity(light, 255);

	LightManager::GetInstance()->SetRadius(light, 128);

	LightManager::GetInstance()->SetQuality(light, 16);

	LightManager::GetInstance()->SetColor(light, sf::Color(255, 0, 0));

	LightManager::GetInstance()->SetPosition(light2, sf::Vector2f(175, 50));
	LightManager::GetInstance()->SetIntensity(light2, 255);
	LightManager::GetInstance()->SetRadius(light2, 128);
	LightManager::GetInstance()->SetQuality(light2, 16);
	LightManager::GetInstance()->SetColor(light2, sf::Color(0, 0, 255));

	DirectionalLight = LightManager::GetInstance()->AddDynamicDirectionalLight(sf::Vector2f(750, 310), 255, 384, 90, 45, sf::Color(255, 128, 255));

	sf::Texture Image;
	Image.loadFromFile("data/test.png");
	sf::Sprite background;
	background.setTexture(Image);
	background.setScale(800.f / Image.getSize().x, 600.f / Image.getSize().y);

	float LightRefresh = 0;

	bool allerX = true, allerY = true;
	bool allerX2 = true, allerY2 = true;

	float angle = 90;

	while (App.isOpen())
	{
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				App.close();
		}

		LightRefresh += Clock.getElapsedTime().asSeconds();

		angle += Clock.getElapsedTime().asSeconds() * 20;

		if (allerX)
			LightManager::GetInstance()->SetPosition(light, sf::Vector2f(LightManager::GetInstance()->GetPosition(light).x + 100 * Clock.getElapsedTime().asSeconds(),
			LightManager::GetInstance()->GetPosition(light).y));
		else
			LightManager::GetInstance()->SetPosition(light, sf::Vector2f(LightManager::GetInstance()->GetPosition(light).x - 100 * Clock.getElapsedTime().asSeconds(),
			LightManager::GetInstance()->GetPosition(light).y));

		if (allerY)
			LightManager::GetInstance()->SetPosition(light, sf::Vector2f(LightManager::GetInstance()->GetPosition(light).x,
			LightManager::GetInstance()->GetPosition(light).y + 100 * Clock.getElapsedTime().asSeconds()));
		else
			LightManager::GetInstance()->SetPosition(light, sf::Vector2f(LightManager::GetInstance()->GetPosition(light).x,
			LightManager::GetInstance()->GetPosition(light).y - 100 * Clock.getElapsedTime().asSeconds()));

		if (LightManager::GetInstance()->GetPosition(light).x > 800)
			allerX = false;
		if (LightManager::GetInstance()->GetPosition(light).x < 0)
			allerX = true;

		if (LightManager::GetInstance()->GetPosition(light).y > 600)
			allerY = false;
		if (LightManager::GetInstance()->GetPosition(light).y < 0)
			allerY = true;


		if (allerX2)
			LightManager::GetInstance()->SetPosition(light2, sf::Vector2f(LightManager::GetInstance()->GetPosition(light2).x + 125 * Clock.getElapsedTime().asSeconds(),
			LightManager::GetInstance()->GetPosition(light2).y));
		else
			LightManager::GetInstance()->SetPosition(light2, sf::Vector2f(LightManager::GetInstance()->GetPosition(light2).x - 125 * Clock.getElapsedTime().asSeconds(),
			LightManager::GetInstance()->GetPosition(light2).y));

		if (allerY2)
			LightManager::GetInstance()->SetPosition(light2, sf::Vector2f(LightManager::GetInstance()->GetPosition(light2).x,
			LightManager::GetInstance()->GetPosition(light2).y + 125 * Clock.getElapsedTime().asSeconds()));
		else
			LightManager::GetInstance()->SetPosition(light2, sf::Vector2f(LightManager::GetInstance()->GetPosition(light2).x,
			LightManager::GetInstance()->GetPosition(light2).y - 125 * Clock.getElapsedTime().asSeconds()));

		if (LightManager::GetInstance()->GetPosition(light2).x > 800)
			allerX2 = false;
		if (LightManager::GetInstance()->GetPosition(light2).x < 0)
			allerX2 = true;

		if (LightManager::GetInstance()->GetPosition(light2).y > 600)
			allerY2 = false;
		if (LightManager::GetInstance()->GetPosition(light2).y < 0)
			allerY2 = true;


		LightManager::GetInstance()->SetPosition(light3, sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(App).x),
			static_cast<float>(sf::Mouse::getPosition(App).y)));

		LightManager::GetInstance()->SetOtherParameter(DirectionalLight, ANGLE, angle);

		Clock.restart();

		if (LightRefresh > 0.025f)
		{
			LightManager::GetInstance()->Generate();
			LightRefresh = 0;
		}

		App.clear();

		App.draw(background);

		App.draw(Wall, 10, sf::Lines);

		LightManager::GetInstance()->Draw(&App);

		App.display();
	}

	return EXIT_SUCCESS;
}

