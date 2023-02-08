#include "Logger.hpp"

namespace ScLogger {
	void Logger::message(std::string message) {
		auto nowPoint = std::chrono::system_clock::now();
		time_t now = std::chrono::system_clock::to_time_t(nowPoint);
		char buffer[50];
		tm time;
		localtime_s(&time, &now);
		std::cout << std::put_time(&time, "%F %T ");
		std::cout << message << '\n';
	}

	void Logger::info(std::string info) {
		message("INFO: " + info);
	}
	void Logger::warning(std::string warning) {
		message("WARNING: " + warning);
	}
	void Logger::error(std::string error) {
		message("ERROR: " + error);
	}
}