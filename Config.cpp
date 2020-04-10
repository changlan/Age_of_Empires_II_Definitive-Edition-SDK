#include "Config.h"

#include <Windows.h>

#include <iostream>
#include <fstream>

#include "Shlobj.h"
#include "Shlobj_core.h"


Config* Config::instance = NULL;


std::filesystem::path Config::GetConfigPath()
{
	TCHAR szPath[MAX_PATH];
	SHGetFolderPath(nullptr, CSIDL_APPDATA, nullptr, 0, szPath);
	std::filesystem::path path = std::filesystem::path(szPath);
	path.append("AoE2DE_imgui");
	return path;
}

Config::Config()
{
	std::filesystem::path path = GetConfigPath();

	//create directory if it doesn't exist
	CreateDirectoryA(GetConfigPath().string().c_str(), NULL);

	//create config.ini if doesn't exist
	std::ofstream configFile;
	path.append("config.ini");
	configFile.open(path.c_str(), std::fstream::app);
}

std::filesystem::path Config::GetConfigFilePath()
{
	std::filesystem::path path = GetConfigPath();
	path.append("config.ini");
	return path;
}

float Config::ReadFloat(std::string feature, std::string settingsName)
{
	char buffer[256];
	int read = GetPrivateProfileString(feature.c_str(), settingsName.c_str(), NULL, buffer, 256, GetConfigFilePath().string().c_str());
	if (!read)
	{
		printf("Failed to read config: %s->%s\n", feature.c_str(), settingsName.c_str());
	}
	return std::stof(buffer);
}

int Config::ReadInt(std::string feature, std::string settingsName)
{
	char buffer[256];
	int read = GetPrivateProfileString(feature.c_str(), settingsName.c_str(), NULL, buffer, 256, GetConfigFilePath().string().c_str());
	if (!read)
	{
		printf("Failed to read config: %s->%s\n", feature.c_str(), settingsName.c_str());
	}
	return std::stoi(buffer);
}

std::string Config::ReadString(std::string feature, std::string settingsName)
{
	char buffer[256];
	int read = GetPrivateProfileString(feature.c_str(), settingsName.c_str(), NULL, buffer, 256, GetConfigFilePath().string().c_str());
	if (!read)
	{
		printf("Failed to read config: %s->%s\n", feature.c_str(), settingsName.c_str());
	}
	return std::string(buffer);
}