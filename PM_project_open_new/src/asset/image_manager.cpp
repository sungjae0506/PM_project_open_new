#include "image_manager.h"

ImageManager::ImageManager()
{
}

ImageManager::ImageManager(string path)
{
	fstream f(path);
	jsonData = json::parse(f);
}

ImageManager& ImageManager::operator() (string path)
{
	fstream f(path);
	jsonData = json::parse(f);

	return *this;
}

vector<Image> ImageManager::getImages(string name)
{
	vector<Image> ret;
	
	cout << "second" << jsonData.size() << endl;

	for (auto& i : jsonData[name])
	{
		cout << i[0].get<string>() << endl;
		ret.push_back(Image(i[0].get<string>(), Range(i[1][0].get<double>(), i[1][1].get<double>(), i[1][2].get<double>(), i[1][3].get<double>())));
	}
	return ret;
}