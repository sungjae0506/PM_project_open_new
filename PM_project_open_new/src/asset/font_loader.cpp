#include "font_loader.h"

FontLoader::FontLoader()
{

}

FIBITMAP* FontLoader::createBitMap(string fileName) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName.data(), 0);
	if (format == -1) { // couldn't find image
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) { // couldn't determine file format
		// attemp to get from file extension
		format = FreeImage_GetFIFFromFilename(fileName.data());
		if (!FreeImage_FIFSupportsReading(format)) {
			//cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}
	FIBITMAP* bitmap = FreeImage_Load(format, fileName.data());
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	//cout << "Source image has " << bitsPerPixel << " bits per pixel." << endl;
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		//cout << "Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		//cout << "Converting to 32-bits." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	return bitmap32;
}

void FontLoader::load(string fileName)
{
	if (dataTable.find(fileName) != dataTable.end())
		return;

	FIBITMAP* bitmap32 = createBitMap(fileName);
	int imageWidth = FreeImage_GetWidth(bitmap32);
	int imageHeight = FreeImage_GetHeight(bitmap32);

	bitmap32->data;

	GLubyte* textureData = FreeImage_GetBits(bitmap32);
	GLubyte* colorFilteredTexture[25];
	for (int i = 0; i < 25; ++i)
	{
		colorFilteredTexture[i] = new unsigned char [imageWidth * imageHeight * 4];
	}
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < imageWidth * imageHeight; ++j) // red
		{
			colorFilteredTexture[i + 16][j * 4] = textureData[j * 4] >> (8 - i);
			colorFilteredTexture[i + 16][j * 4 + 1] = 0;
			colorFilteredTexture[i + 16][j * 4 + 2] = 0;
			colorFilteredTexture[i + 16][j * 4 + 3] = textureData[j * 4 + 3];
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < imageWidth * imageHeight; ++j) // green
		{
			colorFilteredTexture[i + 8][j * 4] = 0;
			colorFilteredTexture[i + 8][j * 4 + 1] = textureData[j * 4 + 1] >> (8 - i);
			colorFilteredTexture[i + 8][j * 4 + 2] = 0;
			colorFilteredTexture[i + 8][j * 4 + 3] = textureData[j * 4 + 3];
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < imageWidth * imageHeight; ++j) // blue
		{
			colorFilteredTexture[i][j * 4] = 0;
			colorFilteredTexture[i][j * 4 + 1] = 0;
			colorFilteredTexture[i][j * 4 + 2] = textureData[j * 4 + 2] >> (8 - i);
			colorFilteredTexture[i][j * 4 + 3] = textureData[j * 4 + 3];
		}
	}
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < imageWidth * imageHeight; ++j) // black
		{
			colorFilteredTexture[i + 24][j * 4] = 0;
			colorFilteredTexture[i + 24][j * 4 + 1] = 0;
			colorFilteredTexture[i + 24][j * 4 + 2] = 0;
			colorFilteredTexture[i + 24][j * 4 + 3] = textureData[j * 4 + 3];
		}
	}

	dataTable.insert({fileName, TextureData(imageWidth, imageHeight, textureData)});

	glEnable(GL_TEXTURE_2D);
	glGenTextures(25, ID);
	idxTable.insert({fileName, IDTable.size()});
	for (int i = 0; i < 25; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, ID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, colorFilteredTexture[i]);
	}
	vector<GLuint> tmp;
	tmp.resize(25);
	for (int i = 0; i < 25; ++i)
		tmp[i] = ID[i];
	IDTable.push_back(tmp);
}

void FontLoader::bind(string fileName, int color)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, IDTable[idxTable[fileName]][color]);
}