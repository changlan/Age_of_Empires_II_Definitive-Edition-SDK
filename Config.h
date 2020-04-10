#pragma once
#include <filesystem>
#include <string>


class Config
{
	static Config* instance;

	Config();
public:

	static Config* Get()
	{
		if (!instance)
		{
			instance = new Config();
		}
		return instance;
	}

	std::filesystem::path GetConfigPath();
	std::filesystem::path GetConfigFilePath();
	
	
	template <class T>
	void Write(std::string feature, std::string settingsName, T value)
	{
		if (!WritePrivateProfileString(feature.c_str(), settingsName.c_str(), std::to_string(value).c_str(), GetConfigFilePath().string().c_str()))
		{
			printf("Failed to write config: %s->%s\n", feature.c_str(), settingsName.c_str());
		}
	}

	float ReadFloat(std::string feature, std::string settingsName);

	int ReadInt(std::string feature, std::string settingsName);


	std::string ReadString(std::string feature, std::string settingsName);
};
