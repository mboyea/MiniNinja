#ifndef LOG_H
#define LOG_H
#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include "Colors.h"

enum LogType {
	LOG = 0,
	WARNING,
	FAULT,
	SUCCESS
};

struct GameLog {
	uint32_t time;
	std::string text;
	LogType logType;

	GameLog(std::string text, LogType logType);
	std::string AsText();
	SDL_Color GetColor();
};

namespace Game {
	inline std::vector<GameLog> logs;
	inline bool doLogConsoleToFile = false;
	inline std::string inputText = "";
}

void Log(std::string text, LogType logType = LogType::LOG);
void LogToFile(std::vector<GameLog> logs);
bool HasLogUpdated();
void SetLogUpdated(bool logUpdated);

#endif // !LOG_H