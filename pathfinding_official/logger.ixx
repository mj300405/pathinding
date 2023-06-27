module;

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <mutex>

export module logger;

enum class LogLevel {
	INFO,
	WARN,
	ERROR,
	NONE
};

export class Logger {
private:
	LogLevel log_level;
	std::ofstream log_file;
	std::mutex mtx;


	std::string get_time() {
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::tm buf;
		gmtime_s(&buf, &in_time_t);

		std::stringstream ss;
		ss << std::put_time(&buf, "%Y-%m-%d %X");
		return ss.str();
	}



public:
	Logger(LogLevel level = LogLevel::INFO) : log_level(level) {}

	Logger(const std::string& file, LogLevel level = LogLevel::INFO)
		: log_level(level), log_file(file, std::ios_base::app) {
		if (!log_file.is_open()) {
			std::cerr << "Failed to open log file: " << file << std::endl;
			exit(1);
		}
	}

	~Logger() {
		if (log_file.is_open()) {
			log_file.close();
		}
	}

	void log(const std::string& message, LogLevel level) {
		if (level < log_level) {
			return;
		}

		std::string str_level;
		switch (level) {
		case LogLevel::INFO:
			str_level = "INFO";
			break;
		case LogLevel::WARN:
			str_level = "WARN";
			break;
		case LogLevel::ERROR:
			str_level = "ERROR";
			break;
		default:
			return;
		}

		std::stringstream ss;
		ss << "[" << get_time() << "] [" << str_level << "]: " << message << std::endl;

		std::lock_guard<std::mutex> lock(mtx);

		if (log_file.is_open()) {
			log_file << ss.str();
		}
		else {
			std::cout << ss.str();
		}
	}
};
