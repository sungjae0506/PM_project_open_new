#include "light.h"
#include <GL/freeglut.h>

Light::Light(float _x, float _y, float _z, int L_ID)
{
	x = _x;
	y = _y;
	z = _z;
	lightID = L_ID;
}

void Light::setAmbient(float r, float g, float b, float a)
{
	ambient.setColor(r, g, b, a);
}

void Light::setDiffuse(float r, float g, float b, float a)
{
	diffuse.setColor(r, g, b, a);
}

void Light::setSpecular(float r, float g, float b, float a)
{
	specular.setColor(r, g, b, a);
}

Color4f Light::getAmbient() const
{
	return ambient;
}

Color4f Light::getDiffuse() const
{
	return diffuse;
}

Color4f Light::getSpecular() const
{
	return specular;
}

int Light::getID() const
{
	return lightID;
}

void Light::draw() const
{
	float _ambient[4] = { ambient[0], ambient[1] , ambient[2] , ambient[3] };
	float _diffuse[4] = { diffuse[0], diffuse[1] , diffuse[2] , diffuse[3] };
	float _specular[4] = { specular[0], specular[1] , specular[2] , specular[3] };
	float _pos[3] = { x, y, z };

	glEnable(lightID);
	glLightfv(lightID, GL_AMBIENT, _ambient);
	glLightfv(lightID, GL_DIFFUSE, _diffuse);
	glLightfv(lightID, GL_SPECULAR, _specular);
	glLightfv(lightID, GL_POSITION, _pos);
}