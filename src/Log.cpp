#include "Log.h"

static bool hasUpdated = false;

GameLog::GameLog(std::string text, LogType logType) : text(text), logType(logType) {
	time = SDL_GetTicks();
}

std::string GameLog::AsText() {
	return '(' + std::to_string(time) + ") " + text;
}

SDL_Color GameLog::GetColor() {
	switch (logType) {
	case LogType::LOG:
		return Colors::LIGHT_GREY;
	case LogType::WARNING:
		return Colors::YELLOW;
	case LogType::FAULT:
		return Colors::RED;
	case LogType::SUCCESS:
		return Colors::LIME;
	default:
		return Colors::WHITE;
	}
}

void Log(std::string text, LogType logType) {
	Game::logs.push_back(GameLog(text, logType));
	hasUpdated = true;
}

void LogToFile(std::vector<GameLog> logs) {
	// TODO: save the game log to a file
}

bool HasLogUpdated() {
	return hasUpdated;
}

void SetLogUpdated(bool logUpdated) {
	hasUpdated = logUpdated;
}