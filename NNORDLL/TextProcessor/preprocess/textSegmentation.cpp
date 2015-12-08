#include "textPreprocess.h"

#include <vector>
#include <string>
#include <sstream>


std::vector<std::string> nnor::split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)) 
		elems.push_back(item);
	return elems;
}

std::vector<char> nnor::splitWord(std::string word)
{
	std::vector<char> splittedWord;
	for (char character : word)
		splittedWord.push_back(character);
	return splittedWord;
}