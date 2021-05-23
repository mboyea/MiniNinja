#include "Files.h"
#include <filesystem>

bool IsFileExtension(std::string filePath, std::string extension) {
	if (extension[0] == '.') {
		extension.erase(extension.begin() + 0);
	}
	return GetFileExtension(filePath) == extension;
}

std::string GetFileExtension(std::string filePath) {
	int index = -1;
	for (auto it = filePath.crbegin(); it != filePath.crend(); it++) {
		if (*it == '.') {
			index = filePath.size() - (it - filePath.crbegin());
			continue;
		}
		if (*it == '/' || *it == '\\') {
			break;
		}
	}
	if (index < 0) {
		return "";
	}
	return filePath.substr(index);
}

std::string ForceFileExtension(std::string filePath, std::string extension) {
	if (extension[0] == '.') {
		extension.erase(extension.begin() + 0);
	}
	if (IsFileExtension(filePath, extension)) {
		return filePath;
	}
	RemoveFileExtension(filePath);
	return filePath + '.' + extension;
}

std::string RemoveFileExtension(std::string filePath) {
	int index = -1;
	for (auto it = filePath.crbegin(); it != filePath.crend(); it++) {
		if (*it == '.') {
			index = filePath.size() - (it - filePath.crbegin()) - 1;
			continue;
		}
		if (*it == '/' || *it == '\\') {
			break;
		}
	}
	if (index < 0) {
		return filePath;
	}
	return filePath.substr(0, index);
}

std::string RemoveFilePath(std::string filePath) {
	int index = -1;
	for (auto it = filePath.crbegin(); it != filePath.crend(); it++) {
		if (*it == '/' || *it == '\\') {
			index = filePath.size() - (it - filePath.crbegin());
			break;
		}
	}
	if (index < 0) {
		return filePath;
	}
	return filePath.substr(index);
}

std::vector<std::string> GetFilesInDirectory(std::string folderPath) {
	std::vector<std::string> files;
	for (const auto& file : std::filesystem::directory_iterator(folderPath)) {
		files.push_back(file.path().string());
	}
	return files;
}

std::vector<std::string> GetFilesWithExtension(std::vector<std::string> files, std::string extension) {
	std::vector<std::string> extensionFiles;
	for (std::string file : files) {
		if (IsFileExtension(file, extension)) {
			extensionFiles.push_back(file);
		}
	}
	return extensionFiles;
}
