#include "texture_loader.h"

TextureData::TextureData()
{
}

TextureData::TextureData(int w, int h, GLubyte* d)
{
	imageWidth = w;
	imageHeight = h;
	textureData = d;
}

TextureLoader::TextureLoader()
{
}

FIBITMAP* TextureLoader::createBitMap(string fileName) {
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

void TextureLoader::load(string fileName)
{
	if (dataTable.find(fileName) != dataTable.end())
		return;

	FIBITMAP* bitmap32 = createBitMap(fileName);
	int imageWidth = FreeImage_GetWidth(bitmap32);
	int imageHeight = FreeImage_GetHeight(bitmap32);

	bitmap32->data;

	GLubyte* textureData = FreeImage_GetBits(bitmap32);

	dataTable.insert({fileName, TextureData(imageWidth, imageHeight, textureData)});

	IDTable.clear();
	//glEnable(GL_TEXTURE_2D);
	glGenTextures(dataTable.size(), ID);

	int cnt = 0;
	for (auto& i : dataTable)
	{
		IDTable.insert({i.first, ID[cnt]});
		glBindTexture(GL_TEXTURE_2D, ID[cnt++]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.second.imageWidth, i.second.imageHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, i.second.textureData);
	}
}

void TextureLoader::bind(string fileName)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, IDTable[fileName]);
}