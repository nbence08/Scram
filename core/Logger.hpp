#pragma once
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "core_export.hpp"

namespace ScLogger {
	class CORE_EXPORT Logger {
	private:
		static void message(std::string message);

	public:
		static void info(std::string info);
		static void warning(std::string warning);
		static void error(std::string error);
	};
}