#pragma once
#include "Light.h"

enum { ANGLE, OPENING_ANGLE };

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(sf::Vector2f position, float intensity, float radius, float angle, float opening_angle, sf::Color colo);
	virtual ~DirectionalLight();

	void Generate(std::vector <Wall> &m_wall);

	void SetAngle(float angle);
	void SetOpeningAngle(float angle);

	void SetOtherParameter(unsigned, float);

protected:
private:

	float m_angle;
	float m_opening_angle;
};

