#pragma once
#include <string>
class Logger
{
	std::string db_name;
	std::string file_name;
	Logger* instance = nullptr;
	Logger();
public:
	void Log(std::string msg, std::string file);
	Logger GetInstance(void);
};

