#pragma once

struct Wall
{
	Wall(sf::Vector2f p1, sf::Vector2f p2)
	{
		pt1 = p1;
		pt2 = p2;
	}

	// Pt1 et Pt2 sont les deux extr�mit�s du mur
	sf::Vector2f pt1;
	sf::Vector2f pt2;
};

// WallEntity est une variable qui permet de repr�senter dans le programme un mur
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

	// Retourner diff�rents attributs de la lumi�re
	float GetIntensity();
	float GetRadius();
	int GetQuality();
	sf::Color GetColor();
	sf::Vector2f GetPosition();

	// Une petite bool pour savoir si la lumi�re est allum�e ou �teinte
	bool m_active;

protected:
	//Position � l'�cran
	sf::Vector2f m_position;
	//Intensit�, g�re la transparence ( entre 0 et 255 )
	float m_intensity;
	//Rayon de la lumi�re
	float m_radius;
	//Couleur de la lumi�re
	sf::Color m_color;


	//Tableau dynamique de Shape, ce sont ces shapes de type triangle qui compose la lumi�re
	std::vector <sf::VertexArray> m_shape;

private:

	//Qualit� de la lumi�re, c'est � dire le nombre de triangles par d�faut qui la compose.
	int m_quality;
};

using LightPtr = std::shared_ptr < Light > ;