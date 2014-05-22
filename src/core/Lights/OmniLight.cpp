#include "pch.h"
#include "OmniLight.h"

//////////////////////////////////////////////////////////////////////////

LightType OmniLight::GetType() const
{
	return LightType::OMNI;
}

//////////////////////////////////////////////////////////////////////////

void OmniLight::Generate(std::vector<Wall> walls)
{
	m_shape.clear();

	float buf = ((float)M_PI * 2) / (float)m_quality;

	for (int i = 0; i < (int)m_quality; i++)
	{
		sf::Vector2f p1(sf::Vector2f((float)((float)m_radius * cos((float)i * buf)), (float)((float)m_radius * sin((float)i * buf))));
		sf::Vector2f p2(sf::Vector2f((float)((float)m_radius * cos((float)(i + 1) * buf)), (float)((float)m_radius * sin((float)(i + 1) * buf))));
		AddTriangle(p1, p2, 0, walls);
	}
}

//////////////////////////////////////////////////////////////////////////
