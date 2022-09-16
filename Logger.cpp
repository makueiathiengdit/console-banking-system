#include <iostream>
#include <fstream>
#include "Logger.h"
Logger::Logger()
{
	db_name = "db.dat";
	file_name = "logs.txt";
}
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

