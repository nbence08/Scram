#include "Logger.hpp"

#include <time.h>

namespace ScLogger {
	void Logger::message(std::string message) {
		
		using tm = struct tm;

		auto nowPoint = std::chrono::system_clock::now();
		time_t now = std::chrono::system_clock::to_time_t(nowPoint);
		char buffer[50];
		tm time;

		#ifdef APPLE
			localtime_r(&now, &time);
		#endif
		#ifdef WINDOWS
			localtime_s(&time, &now);
		#endif

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