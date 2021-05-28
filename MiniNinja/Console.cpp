#include "Console.h"
#include "Log.h"
#include <unordered_map>
#include <algorithm>
#include "Collider.h"

static uint8_t pageSize = 10;
static std::unordered_map<std::string, std::function<bool(std::vector<std::string>)>> voidFuncs;
static std::unordered_map<std::string, std::function<std::string(std::vector<std::string>)>> strFuncs;

int GetFunctionCount() {
	return voidFuncs.size() + strFuncs.size();
}

void InitConsole() {
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1 && IsInteger(args[0])) {
			LogFunctions(std::stoi(args[0]));
			return true;
		}
		LogFunctions();
		return true;
		}, "help"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1 && IsInteger(args[0])) {
			SetHelpPageSize(std::stoi(args[0]));
			return true;
		}
		return false;
		}, "sethelppagesize"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1) {
			Game::doLogConsoleToFile = ToBool(args[0]);
			return true;
		}
		return false;
		}, "setlogconsoletofile"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1) {
			Game::doRenderColliders = ToBool(args[0]);
			return true;
		}
		return false;
		}, "setdorendercolliders"
	);
	SetFunction([](std::vector<std::string> args) {
		return BoolToString(Game::doRenderColliders);
		}, "getdorendercolliders"
	);
}

bool IsFunction(std::string call) {
	return voidFuncs.find(call) != voidFuncs.end() || strFuncs.find(call) != strFuncs.end();
}

void LogFunction(std::string call) {
	Log(call + "()");
}

void LogFunctions(int pageIndex) {
	int pageCount = (int)std::ceil((float)GetFunctionCount() / pageSize);
	if (pageIndex < 1 || pageIndex > pageCount) {
		Log("Help index out-of-bounds. Type help().", WARNING);
	}

	int i = 0;
	for (auto voidFunc : voidFuncs) {
		if (i < (pageIndex - 1) * pageSize) {
			i++;
			continue;
		}
		if (i >= pageIndex * pageSize) {
			break;
		}
		LogFunction(voidFunc.first);
		i++;
	}
	for (auto strFunc : strFuncs) {
		if (i < (pageIndex - 1) * pageSize) {
			i++;
			continue;
		}
		if (i >= pageIndex * pageSize) {
			break;
		}
		LogFunction(strFunc.first);
		i++;
	}
	Log("- - - End Help(" + std::to_string(pageIndex) + '/' + std::to_string(pageCount) + ") - - -");
}

void SetFunction(std::function<bool(std::vector<std::string>)> func, std::string call) {
	std::transform(call.begin(), call.end(), call.begin(), std::tolower);
	voidFuncs[call] = func;
}

void SetFunction(std::function<std::string(std::vector<std::string>)> func, std::string call) {
	std::transform(call.begin(), call.end(), call.begin(), std::tolower);
	strFuncs[call] = func;
}

void SetHelpPageSize(int lineCount) {
	if (lineCount < 1) {
		lineCount = 1;
	}
	pageSize = lineCount;
}

bool IsInteger(const std::string& str) {
	if (str.empty() || (!std::isdigit(str[0]) && str[0] != '-' && str[0] != '+')) {
		return false;
	}
	char* p;
	std::strtol(str.c_str(), &p, 10);
	return (*p == 0);
}

bool ToBool(const std::string& str) {
	if (str[0] == 'T' || str[0] == 't') {
		return true;
	}
	if (IsInteger(str)) {
		return std::stoi(str);
	}
	return false;
}

std::string BoolToString(const bool& boolean) {
	switch (boolean) {
	case true:
		return "True";
	case false:
		return "False";
	}
	return "BoolToString Failed";
}

std::vector<std::string> GetArgList(std::string& args) {
	std::vector<std::string> argList;
	std::string currentArg = "";

	for (std::string::iterator it = args.begin(); it < args.end(); it++) {
		// ignore whitespace
		while (*it == ' ') {
			it++;
		}
		// push back the arg if a comma is reached
		if (*it == ',') {
			argList.push_back(currentArg);
			currentArg = "";
			continue;
		}
		// add the char to the arg
		currentArg += *it;
	}
	if (currentArg != "") {
		// push back the last arg
		argList.push_back(currentArg);
	}

	return argList;
}

// call a function titled call given arguments separated by commas, ignoring spaces
void InterpretFunction(const std::string& call, std::string& args) {
	std::vector<std::string> argList = GetArgList(args);

	if (voidFuncs.find(call) != voidFuncs.end()) {
		Log("> " + call + '(' + args + ')', SUCCESS);
		if (!voidFuncs[call](argList)) {
			Log("Function failed.", WARNING);
			return;
		}
		return;
	}

	if (strFuncs.find(call) != strFuncs.end()) {
		Log("> " + call + '(' + args + ')', SUCCESS);
		std::string result = strFuncs[call](argList);
		if (result == "") {
			Log("Function failed.", WARNING);
			return;
		}
		Log(result);
		return;
	}

	Log("> " + call + '(' + args + ')', FAULT);
	if (!IsFunction("help")) {
		Log("Console not initialized, all engine functions are unsupported.", FAULT);
		return;
	}
	Log("Unsupported function.", WARNING);
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
				name.erase(remove(name.begin(), name.end(), ' '), name.end());
				std::transform(name.begin(), name.end(), name.begin(), std::tolower);
				std::transform(args.begin(), args.end(), args.begin(), std::tolower);

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