#ifndef FILE_PARAMETERS_H
#define FILE_PARAMETERS_H
#pragma once

#include <iostream>
#include <string>

const char TEXT_START = '{';
const char TEXT_END = '}';

const char LIST_START = '[';
const char LIST_END = ']';
const char LIST_ITEM_END = ';';

const char MODULE_END = '\n';
const std::string FILE_END = "EOF";

std::string MakeSerializable(std::string str);
std::string DeserializeString(std::istream& is);

#endif // !FILE_PARAMETERS_H