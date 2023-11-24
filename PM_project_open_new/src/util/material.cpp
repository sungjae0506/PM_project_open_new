#include "material.h"

Material::Material()
{
}

void Material::setEmission(float r, float g, float b, float a)
{
	emission.setColor(r, g, b, a);
}

void Material::setAmbient(float r, float g, float b, float a)
{
	ambient.setColor(r, g, b, a);
}

void Material::setDiffuse(float r, float g, float b, float a)
{
	diffuse.setColor(r, g, b, a);
}

void Material::setSpecular(float r, float g, float b, float a)
{
	specular.setColor(r, g, b, a);
}

void Material::setShininess(float sh)
{
	shininess = sh;
}

Color4f Material::getEmission() const
{
	return emission;
}

Color4f Material::getAmbient() const
{
	return ambient;
}

Color4f Material::getDiffuse() const
{
	return diffuse;
}

Color4f Material::getSpecular() const
{
	return specular;
}

float Material::getShininess() const
{
	return shininess;
}