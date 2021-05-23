#ifndef FILES_H
#define FILES_H
#pragma once

#include <string>
#include <vector>

bool IsFileExtension(std::string filePath, std::string extension);
std::string GetFileExtension(std::string filePath);
std::string ForceFileExtension(std::string filePath, std::string extension);
std::string RemoveFileExtension(std::string filePath);
std::string RemoveFilePath(std::string filePath);
std::vector<std::string> GetFilesInDirectory(std::string folderPath);
std::vector<std::string> GetFilesWithExtension(std::vector<std::string> filePaths, std::string extension);

#endif // !FILES_H