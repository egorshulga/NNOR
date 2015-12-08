#pragma once

#include <string>
#include <vector>

namespace nnor
{

	std::vector<std::string> split(const std::string &s, char delim);

	std::vector<char> splitWord(std::string word);
}