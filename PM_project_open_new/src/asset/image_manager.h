#pragma once
#include "image.h"
#include <string>
#include <vector>
#include <fstream>
#include "../util/json.hpp"

using namespace std;
using json = nlohmann::json;

class ImageManager
{
public:
	json jsonData;

	ImageManager();
	ImageManager(string path);
	ImageManager& operator() (string path);

	vector<Image> getImages(string name);
};