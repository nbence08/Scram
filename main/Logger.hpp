#pragma once
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

class Logger {
private:
	static void message(std::string message);

public:
	static void info(std::string info);
	static void warning(std::string warning);
	static void error(std::string error);
};