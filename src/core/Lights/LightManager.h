#pragma once
#include "DirectionalLight.h"

class LightManager : public Singleton < LightManager >
{
public:
	LightManager();
	~LightManager();

public:
	//Différents moyen d'ajouter une lumière dynamique, soit on l'ajoute sans aucune valeur par défaut, soit on lui donne une lumière par défaut, soit on lui donne ses valeurs "à la main"
	LightEntity AddDynamicLight();
	LightEntity AddDynamicLight(Light);
	LightEntity AddDynamicLight(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color);

	LightEntity AddDynamicDirectionalLight();
	LightEntity AddDynamicDirectionalLight(DirectionalLight);
	LightEntity AddDynamicDirectionalLight(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color);

	LightEntity AddStaticLight(Light);
	LightEntity AddStaticLight(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color);

	LightEntity AddStaticDirectionalLight(DirectionalLight);
	LightEntity AddStaticDirectionalLight(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color);

	// Ajouter un mur
	WallEntity AddWall(sf::Vector2f pt1, sf::Vector2f pt2);

	// Désactiver une lumière ou supprimer un mur
	void Delete_Light(LightEntity);
	void Delete_Wall(WallEntity);

	void Delete_All_Wall();
	void Delete_All_Light();

	// Calculer toutes les lumières dynamiques
	void Generate();
	void Generate(LightEntity);

	// Afficher toutes les lumières à l'écran
	void Draw(sf::RenderWindow *App);

	// Différentes méthodes pour modifier les attributs d'une lumière, ou les récupérer. Il faut à chaque fois envoyer une LightEntity en paramètre pour
	// savoir de quelle lumière on parle/

	void SetPosition(LightEntity, sf::Vector2f);
	void SetQuality(LightEntity, int);
	void SetRadius(LightEntity, float);
	void SetColor(LightEntity, sf::Color);
	void SetIntensity(LightEntity, float);

	void SetOtherParameter(LightEntity, unsigned, float);

	float GetIntensity(LightEntity);
	float GetRadius(LightEntity);
	int GetQuality(LightEntity);
	sf::Color GetColor(LightEntity);
	sf::Vector2f GetPosition(LightEntity);

	void SetPosition(WallEntity, sf::Vector2f);

	sf::Color m_basicLight;
	int m_lightSmooth;

protected:
	std::vector<Wall> m_wall;
	std::vector<LightPtr> m_staticLight;
	std::vector<LightPtr> m_dynamicLight;

private:
	sf::Shader m_blurEffect;
	sf::RenderTexture m_renderImg;

};
