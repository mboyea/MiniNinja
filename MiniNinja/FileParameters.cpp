#include "FileParameters.h"
#include "Log.h"

std::string MakeSerializable(std::string str) {
	str.erase(remove(str.begin(), str.end(), TEXT_START), str.end());
	str.erase(remove(str.begin(), str.end(), TEXT_END), str.end());
	return TEXT_START + str + TEXT_END;
}

std::string DeserializeString(std::istream& is) {
	std::string str;
	is >> str;
	if (str[0] != TEXT_START) {
		Log("Deserialized text not wrapped between TEXT_START & TEXT_END: " + str, WARNING);
		return str;
	}
	while (str.back() != TEXT_END) {
		std::string item;
		is >> item;
		str += ' ' + item;
	}
	return str.substr(1, str.size() - 2);
}

std::string DeserializeString(std::string str) {
	if (str[0] != TEXT_START) {
		Log("Deserialized text not wrapped between TEXT_START & TEXT_END: " + str, WARNING);
		return str;
	}
	if (str.back() == TEXT_END) {
		return str.substr(1, str.size() - 2);
	}
	for (auto it = str.crbegin(); it != str.crend(); it++) {
		if (*it == TEXT_END) {
			return str.substr(1, str.size() - (it - str.crbegin()) - 1);
		}
	}
}