#include <iostream>
#include <fstream>
#include "Logger.h"
void Logger::Log(std::string msg, std::string file)
{
	std::ofstream db(file, std::ios::app);
	if (db.is_open())
	{
		db << msg << "\n";
		db.close();
		std::cout << msg << "\n";
	}
	else
	{
		std::cout << "Error opening file: " << file << "\n";
	}
}

//Logger Logger::GetInstance(void)
//{
//	if (instance == nullptr)
//	{
//		instance = new Logger;
//	}
//	return *instance;
//}
