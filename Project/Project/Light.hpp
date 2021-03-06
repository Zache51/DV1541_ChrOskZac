#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <fstream>

using std::string;

struct Light
{
	float x, y, z, w;
	float r, g, b, distance;
	//float distance;
};

inline Light * readLights(std::string file, unsigned int &nrLights)
{
	nrLights = 0;
	std::ifstream inFile(file, std::ios::binary);
	inFile.read((char*)&nrLights, sizeof(unsigned int));
	Light * lights = new Light[nrLights];
	for (unsigned int i = 0; i < nrLights; i++)
	{
		//lights[i] = Light{i, 0, 0, 0, i, i*2, i*3, 25};
		inFile.read((char*)&lights[i], sizeof(Light));
	}

	return lights;

	inFile.close();
}

#endif