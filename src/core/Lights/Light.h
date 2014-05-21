#pragma once

struct Wall
{
	Wall(sf::Vector2f p1, sf::Vector2f p2)
	{
		pt1 = p1;
		pt2 = p2;
	}

	// Pt1 et Pt2 sont les deux extrémités du mur
	sf::Vector2f pt1;
	sf::Vector2f pt2;
};

// WallEntity est une variable qui permet de représenter dans le programme un mur
struct WallEntity
{
	WallEntity(int id)
	{
		m_ID = id;
	}

	int ID() { return m_ID; }

private:

	int m_ID;
};

enum class LightType
{
	STATIC,
	DYNAMIC,
};

// Interface for Lights
class ILight
{
public:
	virtual ~ILight() {}

public:
	virtual void SetPosition(const sf::Vector2f& pos) = 0;
	virtual void SetColor(const sf::Color& color) = 0;
	virtual void SetIntensity(float intensity) = 0;
};

class Light
{
public:
	Light();
	Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color);
	~Light();

	void Draw(sf::RenderTarget* rt);
	
	virtual void Generate(std::vector <Wall> &m_wall);
	void AddTriangle(sf::Vector2f pt1, sf::Vector2f pt2, int minimum_wall, std::vector <Wall> &m_wall);

	void SetIntensity(float);
	void SetRadius(float);
	void SetQuality(int);
	void SetColor(sf::Color);
	void SetPosition(sf::Vector2f);

	virtual void SetOtherParameter(unsigned, float);

	// Retourner différents attributs de la lumière
	float GetIntensity();
	float GetRadius();
	int GetQuality();
	sf::Color GetColor();
	sf::Vector2f GetPosition();

	// Une petite bool pour savoir si la lumière est allumée ou éteinte
	bool m_active;

protected:
	//Position à l'écran
	sf::Vector2f m_position;
	//Intensité, gère la transparence ( entre 0 et 255 )
	float m_intensity;
	//Rayon de la lumière
	float m_radius;
	//Couleur de la lumière
	sf::Color m_color;


	//Tableau dynamique de Shape, ce sont ces shapes de type triangle qui compose la lumière
	std::vector <sf::VertexArray> m_shape;

private:

	//Qualité de la lumière, c'est à dire le nombre de triangles par défaut qui la compose.
	int m_quality;
};

using LightPtr = std::shared_ptr < Light > ;