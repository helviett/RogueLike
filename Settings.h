#pragma once
#include "json.hpp"

using json = nlohmann::json;

class Settings
{
public:
	static void GetSettngs(json config);
	static json& Config();
	Settings(Settings const&) = delete;
	void operator =(Settings const &) = delete;
private:
	Settings() {}

};