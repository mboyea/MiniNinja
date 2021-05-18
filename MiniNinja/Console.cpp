#include "Console.h"
#include "Log.h"

// call a function titled functionName given arguments separated by commas, ignoring spaces
void InterpretFunction(const std::string& functionName, const std::string& arguments) {

	// TODO: outline function interpretation
	Log("> " + functionName + '(' + arguments + ')');
	Log("Unsupported args \"" + functionName + '(' + arguments + ')' + "\"", WARNING);
	Log("Unsupported func \"" + functionName + '(' + arguments + ')' + "\"", WARNING);
}

void InterpretConsoleInput(std::string* text) {
	if (text->size() < 1) {
		return;
	}

	if ((*text)[0] == '-') {
		Log(text->substr(1, text->size() - 1));
	}
	else if ((*text)[text->size() - 1] == ')') {
		for (std::string::iterator i = text->begin(); i < text->end(); i++) {
			if (*i == '(') {
				std::string name = std::string(text->begin(), i);
				std::string args = std::string(i + 1, text->end() - 1);

				InterpretFunction(name, args);
				break;
			}
		}
	}
	else {
		Log("Unsupported cmd \"" + *text + "\"", WARNING);
	}

	Game::consoleInput->clear();
}