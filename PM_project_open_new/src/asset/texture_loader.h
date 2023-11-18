#pragma once

#include <GL/freeglut.h>
#include <FreeImage.h>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class TextureData
{
public:
	int imageWidth;
	int imageHeight;
	GLubyte* textureData;

	TextureData();
	TextureData(int w, int h, GLubyte* d);
};

class TextureLoader
{
public:
	unordered_map<string, TextureData> dataTable;
	unordered_map<string, GLuint> IDTable;
	GLuint ID[100] = { 0 };

	TextureLoader();
	FIBITMAP* createBitMap(string fileName);
	void load(string fileName);
	void bind(string fileName);
};