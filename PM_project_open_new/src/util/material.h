#pragma once

#include "object.h"
#include "color4f.h"

class Material
{
public:
	Material();
	void setEmission(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setShininess(float sh);

	Color4f getEmission() const;
	Color4f getAmbient() const;
	Color4f getDiffuse() const;
	Color4f getSpecular() const;
	float getShininess() const;

private:
	Color4f emission;
	Color4f ambient;
	Color4f diffuse;
	Color4f specular;
	float shininess;
};

