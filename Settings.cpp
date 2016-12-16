#define _CRT_SECURE_NO_WARNINGS
#include "Settings.h"
#include <fstream>
#include <iostream>

void Settings::GetSettngs(json &config)
{
	std::ifstream fin("config.cfg");
	fin >> config;
	std::cout << config;
}

json & Settings::Config()
{
	static json j;
	return j;
}
