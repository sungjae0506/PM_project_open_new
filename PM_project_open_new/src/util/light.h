#pragma once

#include "object.h"
#include "color4f.h"

class Light
{
private:
	int lightID;
	float x, y, z;
	Color4f ambient;
	Color4f diffuse;
	Color4f specular;

public:
	Light(float x, float y, float z, int L_ID);

	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);

	Color4f getAmbient() const;
	Color4f getDiffuse() const;
	Color4f getSpecular() const;
	int getID() const;

	void draw() const;
};

