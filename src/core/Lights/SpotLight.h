#pragma once
#include "Light.h"

enum { ANGLE, OPENING_ANGLE };

class SpotLight : public LightBase
{
public:
	SpotLight();

public:
	virtual void Generate(std::vector<Wall> wall) override;

	void SetAngle(float angle);
	void SetOpeningAngle(float angle);

public:
	virtual LightType GetType() const override;

private:
	float m_angle;
	float m_openingAngle;
};

