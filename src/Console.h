#ifndef CONSOLE_H
#define CONSOLE_H
#pragma once

#include <string>
#include <vector>
#include <functional>

namespace Game {
	inline std::string* consoleInput = new std::string;
}

void InitConsole();
bool IsFunction(std::string call);
void LogFunctions(int pageIndex = 1);
void SetFunction(std::function<bool(std::vector<std::string>)> func, std::string call);
void SetFunction(std::function<std::string(std::vector<std::string>)> func, std::string call);
void SetHelpPageSize(int lineCount);
bool IsInteger(const std::string& str);
bool ToBool(const std::string& str);
std::string BoolToString(const bool& boolean);
void InterpretConsoleCommand(std::string* text = Game::consoleInput);

#endif // !CONSOLE_H