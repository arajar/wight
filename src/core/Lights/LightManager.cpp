#include "pch.h"
#include "LightManager.h"

LightManager::LightManager()
{
	m_lightSmooth = 0;

	m_blurEffect.loadFromFile("/data/shaders/blur.frag", sf::Shader::Fragment);
	m_blurEffect.setParameter("texture", sf::Shader::CurrentTexture);

	m_renderImg.create(800, 600);
}

LightManager::~LightManager()
{
	for (unsigned i = 0; i < m_DynamicLight.size(); ++i)
		delete m_DynamicLight[i];

	for (unsigned i = 0; i < m_StaticLight.size(); ++i)
		delete m_StaticLight[i];

	m_DynamicLight.clear();
	m_StaticLight.clear();
}

LightEntity LightManager::AddDynamicLight()
{
	m_DynamicLight.push_back(new Light());
	return LightEntity((int)m_DynamicLight.size() - 1, true);
}

LightEntity LightManager::AddDynamicLight(Light light)
{
	m_DynamicLight.push_back(new Light(light));
	return LightEntity((int)m_DynamicLight.size() - 1, true);
}
LightEntity LightManager::AddDynamicLight(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
{
	m_DynamicLight.push_back(new Light(position, intensity, radius, quality, color));
	return LightEntity((int)m_DynamicLight.size() - 1, true);
}

// Les différents moyens d'ajouter des lumières directionelles

LightEntity LightManager::AddDynamicDirectionalLight()
{
	m_DynamicLight.push_back(new DirectionalLight());
	return LightEntity((int)m_DynamicLight.size() - 1, true);
}
LightEntity LightManager::AddDynamicDirectionalLight(DirectionalLight light)
{
	m_DynamicLight.push_back(new DirectionalLight(light));
	return LightEntity((int)m_DynamicLight.size() - 1, true);
}
LightEntity LightManager::AddDynamicDirectionalLight(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color)
{
	m_DynamicLight.push_back(new DirectionalLight(position, intensity, radius, angle, o_angle, color));
	return LightEntity((int)m_DynamicLight.size() - 1, true);
}


// Notez bien qu'on calcule les lumières statiques lors de leur ajout.

LightEntity LightManager::AddStaticLight(Light light)
{
	m_StaticLight.push_back(new Light(light));
	m_StaticLight.back()->Generate(m_wall);
	return LightEntity((int)m_StaticLight.size() - 1, false);
}
LightEntity LightManager::AddStaticLight(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
{
	m_StaticLight.push_back(new Light(position, intensity, radius, quality, color));
	m_StaticLight.back()->Generate(m_wall);
	return LightEntity((int)m_StaticLight.size() - 1, false);
}

// Notez bien qu'on calcule les lumières statiques lors de leur ajout.

LightEntity LightManager::AddStaticDirectionalLight(DirectionalLight light)
{
	m_StaticLight.push_back(new DirectionalLight(light));
	m_StaticLight.back()->Generate(m_wall);
	return LightEntity((int)m_StaticLight.size() - 1, false);
}
LightEntity LightManager::AddStaticDirectionalLight(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color)
{
	m_StaticLight.push_back(new DirectionalLight(position, intensity, radius, angle, o_angle, color));
	m_StaticLight.back()->Generate(m_wall);
	return LightEntity((int)m_StaticLight.size() - 1, false);
}

// Ajouter un mur

WallEntity LightManager::AddWall(sf::Vector2f pt1, sf::Vector2f pt2)
{
	for (int i = 0; i < (int)m_wall.size(); i++)
		if ((pt1.y - pt2.y) / (pt1.x - pt2.y) == (m_wall[i].pt1.y - m_wall[i].pt2.y) / (m_wall[i].pt1.x - m_wall[i].pt2.y))
			if (pt1 == m_wall[i].pt1 || pt2 == m_wall[i].pt1 || pt1 == m_wall[i].pt2 || pt2 == m_wall[i].pt2)
			{
		sf::Vector2f min = pt1, max = pt2;

		if (pt2.x<min.x)
			min.x = pt2.x;
		if (pt1.x>max.x)
			max.x = pt2.x;

		if (m_wall[i].pt1.x<min.x)
			min.x = m_wall[i].pt1.x;
		if (m_wall[i].pt2.x<min.x)
			min.x = m_wall[i].pt2.x;

		if (m_wall[i].pt1.x>max.x)
			max.x = m_wall[i].pt1.x;
		if (m_wall[i].pt2.x>max.x)
			max.x = m_wall[i].pt2.x;


		if (pt2.y<min.y)
			min.y = pt2.y;
		if (pt1.y>max.y)
			max.y = pt2.y;

		if (m_wall[i].pt1.y<min.y)
			min.y = m_wall[i].pt1.y;
		if (m_wall[i].pt2.y<min.y)
			min.y = m_wall[i].pt2.y;

		if (m_wall[i].pt1.y>max.y)
			max.y = m_wall[i].pt1.y;
		if (m_wall[i].pt2.y>max.y)
			max.y = m_wall[i].pt2.y;

		m_wall[i].pt1 = min;
		m_wall[i].pt2 = max;

		return WallEntity(i);

			}

	m_wall.push_back(Wall(pt1, pt2));
	return WallEntity(static_cast<int>(m_wall.size() - 1));
}

// On désactive une lumière
void LightManager::Delete_Light(LightEntity e)
{
	if (e.Dynamic())
	{
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->m_active = false;
	}
	else
		if (e.ID() >= 0 && e.ID() < (int)m_StaticLight.size())
			m_StaticLight[e.ID()]->m_active = false;
}

// On supprime un mur
void LightManager::Delete_Wall(WallEntity e)
{
	m_wall.erase(m_wall.begin() + e.ID());
}

void LightManager::Delete_All_Wall()
{
	m_wall.clear();
}
void LightManager::Delete_All_Light()
{
	for (unsigned i = 0; i < m_DynamicLight.size(); ++i)
		delete m_DynamicLight[i];

	for (unsigned i = 0; i < m_StaticLight.size(); ++i)
		delete m_StaticLight[i];

	m_DynamicLight.clear();
	m_StaticLight.clear();
}

// On calcule toutes les lumières dynamiques actives
void LightManager::Generate()
{
	m_renderImg.clear(m_basicLight);
	m_blurEffect.setParameter("offset", 0.005f * m_lightSmooth);

	std::vector<Light*>::iterator it;

	for (it = m_DynamicLight.begin(); it != m_DynamicLight.end(); ++it)
	{
		if ((*it)->m_active)
		{
			(*it)->Generate(m_wall), (*it)->Draw(&m_renderImg);
		}
	}

	for (it = m_StaticLight.begin(); it != m_StaticLight.end(); ++it)
	{
		if ((*it)->m_active)
		{
			(*it)->Draw(&m_renderImg);
		}
	}

	m_renderImg.display();
}


void LightManager::Generate(LightEntity e)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->Generate(m_wall);
}

void LightManager::Draw(sf::RenderWindow *App)
{
	sf::RenderStates r(sf::BlendMultiply);
	r.shader = &m_blurEffect;
	App->draw(sf::Sprite(m_renderImg.getTexture()), r);
}

void LightManager::SetPosition(LightEntity e, sf::Vector2f p)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->SetPosition(p);
}
void LightManager::SetQuality(LightEntity e, int q)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->SetQuality(q);
}
void LightManager::SetRadius(LightEntity e, float r)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->SetRadius(r);
}
void LightManager::SetColor(LightEntity e, sf::Color c)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->SetColor(c);
}
void LightManager::SetIntensity(LightEntity e, float i)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->SetIntensity(i);
}

void LightManager::SetOtherParameter(LightEntity e, unsigned no, float v)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			m_DynamicLight[e.ID()]->SetOtherParameter(no, v);
}


float LightManager::GetIntensity(LightEntity e)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			return m_DynamicLight[e.ID()]->GetIntensity();
	return 0;
}
float LightManager::GetRadius(LightEntity e)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			return m_DynamicLight[e.ID()]->GetRadius();
	return 0;
}
int LightManager::GetQuality(LightEntity e)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			return m_DynamicLight[e.ID()]->GetQuality();

	return 0;
}
sf::Color LightManager::GetColor(LightEntity e)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			return m_DynamicLight[e.ID()]->GetColor();

	return sf::Color(0, 0, 0);
}
sf::Vector2f LightManager::GetPosition(LightEntity e)
{
	if (e.Dynamic())
		if (e.ID() >= 0 && e.ID() < (int)m_DynamicLight.size())
			return m_DynamicLight[e.ID()]->GetPosition();

	return sf::Vector2f(0, 0);
}



// On modifie ou récupère différents attributs des murs

void LightManager::SetPosition(WallEntity e, sf::Vector2f p)
{
	if (e.ID() >= 0 && e.ID() < (int)m_wall.size())
	{
		sf::Vector2f buffer = m_wall[e.ID()].pt1;
		m_wall[e.ID()].pt1 = p;
		m_wall[e.ID()].pt2.x = m_wall[e.ID()].pt2.x + (p.x - buffer.x);
		m_wall[e.ID()].pt2.y = m_wall[e.ID()].pt2.y + (p.y - buffer.y);
	}
}



