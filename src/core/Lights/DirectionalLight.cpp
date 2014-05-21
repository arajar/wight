#include "pch.h"
#include "DirectionalLight.h"

#include <iostream>
#include <math.h>

DirectionalLight::DirectionalLight() : Light()
{
	m_angle = 0;
	m_opening_angle = 0;
}

DirectionalLight::DirectionalLight(sf::Vector2f position, float intensity, float radius, float angle, float opening_angle, sf::Color colo)
	: Light(position, intensity, radius, 0, colo), m_angle(angle), m_opening_angle(opening_angle)
{
}

DirectionalLight::~DirectionalLight()
{
	//dtor
}


void DirectionalLight::Generate(std::vector<Wall> &m_wall)
{
	m_shape.clear();

	float angle = m_angle * (float)M_PI / 180.f;
	float o_angle = m_opening_angle * (float)M_PI / 180.f;

	AddTriangle(sf::Vector2f((m_radius*cos(angle + o_angle * 0.5f))
		, (m_radius*sin(angle + o_angle * 0.5f))),
		sf::Vector2f((m_radius*cos(angle - o_angle * 0.5f))
		, (m_radius*sin(angle - o_angle * 0.5f))), 0, m_wall);
}

void DirectionalLight::SetAngle(float angle)
{
	m_angle = angle;
}

void DirectionalLight::SetOpeningAngle(float angle)
{
	m_opening_angle = angle;
}

void DirectionalLight::SetOtherParameter(unsigned n, float v)
{
	if (n == ANGLE)
		SetAngle(v);
	else if (n == OPENING_ANGLE)
		SetOpeningAngle(v);
}
