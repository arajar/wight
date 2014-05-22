#pragma once

//////////////////////////////////////////////////////////////////////////

struct Wall
{
	Wall(sf::Vector2f p1, sf::Vector2f p2)
	{
		pt1 = p1;
		pt2 = p2;
	}

	sf::Vector2f pt1;
	sf::Vector2f pt2;
};

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////

enum class LightType
{
	OMNI,
	SPOT,
};

//////////////////////////////////////////////////////////////////////////

enum class LightQuality
{
	ULTRA = 10,
	GOOD = 8,
	FAIR = 6,
	LOW = 4,
	LOWEST = 2,
};

//////////////////////////////////////////////////////////////////////////

// Interface for Lights
class ILight
{
public:
	virtual ~ILight() {}

public:
	virtual void Render(sf::RenderTarget* rt) = 0;

public:
	virtual void SetPosition(const sf::Vector2f& pos) = 0;
	virtual void SetColor(const sf::Color& color) = 0;
	virtual void SetQuality(LightQuality quality) = 0;
	virtual void SetIntensity(float intensity) = 0;
	virtual void SetRadius(float radius) = 0;

	virtual const sf::Vector2f& GetPosition() const = 0;
	virtual const sf::Color& GetColor() const = 0;
	virtual LightQuality GetQuality() const = 0;
	virtual float GetIntensity() const = 0;
	virtual float GetRadius() const = 0;

	virtual LightType GetType() const = 0;

	virtual void SetActive(bool active) = 0;
	virtual bool IsActive() = 0;

public:
	virtual void Generate(std::vector<Wall> walls) = 0;

};

//////////////////////////////////////////////////////////////////////////

class LightBase : public ILight
{
public:
	LightBase();
	virtual ~LightBase();

public:
	virtual void Render(sf::RenderTarget* rt) override;

public:
	virtual void SetPosition(const sf::Vector2f& pos) override;
	virtual void SetColor(const sf::Color& color) override;
	virtual void SetQuality(LightQuality quality) override;
	virtual void SetIntensity(float intensity) override;
	virtual void SetRadius(float radius) override;

	virtual const sf::Vector2f& GetPosition() const override;
	virtual const sf::Color& GetColor() const override;
	virtual LightQuality GetQuality() const override;
	virtual float GetIntensity() const override;
	virtual float GetRadius() const override;

	virtual void SetActive(bool active) override;
	virtual bool IsActive() override;

protected:
	virtual void AddTriangle(sf::Vector2f point1, sf::Vector2f point2, int minWall, std::vector<Wall>& walls);

protected:
	sf::Vector2f					m_position;
	sf::Color						m_color;
	LightQuality					m_quality;

	float							m_intensity;
	float							m_radius;

	bool							m_active;

	std::vector<sf::VertexArray>	m_shape;
};

//////////////////////////////////////////////////////////////////////////
