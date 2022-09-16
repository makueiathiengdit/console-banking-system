#pragma once
#include <string>
class Logger
{
	std::string db_name;
	std::string file_name;
public:
	Logger();
	void Log(std::string msg, std::string file);
};

