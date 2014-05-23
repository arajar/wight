#include "pch.h"
#include "game\game.h"
#include "core\Lights.h"

int main(int argc, char** argv)
{
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "wight");

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

	LightManager::GetInstance()->SetGlobalAmbientColor(sf::Color(0, 0, 0));

	/*LightManager::GetInstance()->AddWall(sf::Vector2f(450, 325), sf::Vector2f(300, 200));
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
	*/
	
	OmniLight* light = new OmniLight();
	light->SetPosition(sf::Vector2f(375, 275));
	light->SetIntensity(255.f);
	light->SetRadius(128.f);
	light->SetQuality(LightQuality::LOW);
	light->SetColor(sf::Color::White);

	LightManager::GetInstance()->AddLight(light);

	SpotLight* light2 = new SpotLight();
	light2->SetPosition(sf::Vector2f(375, 275));
	light2->SetIntensity(255.f);
	light2->SetRadius(255.f);
	light2->SetQuality(LightQuality::LOWEST);
	light2->SetColor(sf::Color::White);
	light2->SetAngle(0.f);
	light2->SetOpeningAngle(35.f);

	LightManager::GetInstance()->AddLight(light2);

	sf::Texture Image;
	Image.loadFromFile("data/test.png");
	sf::Sprite background;
	background.setTexture(Image);
	background.setScale(800.f / Image.getSize().x, 600.f / Image.getSize().y);

	float LightRefresh = 0;
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


		Clock.restart();

		if (LightRefresh > 0.025f)
		{
			LightManager::GetInstance()->Generate();
			LightRefresh = 0;
		}

		light->SetPosition(sf::Vector2f((float)sf::Mouse::getPosition(App).x, (float)sf::Mouse::getPosition(App).y));

		App.clear();

		App.draw(background);

		//App.draw(Wall, 10, sf::Lines);

		LightManager::GetInstance()->Render(&App);

		App.display();
	}

	return EXIT_SUCCESS;
}

