#ifndef CONSOLE_H
#define CONSOLE_H
#pragma once

#include <string>

namespace Game {
	inline std::string* consoleInput = new std::string;
}

void InterpretConsoleInput(std::string* text = Game::consoleInput);

#endif // !CONSOLE_H