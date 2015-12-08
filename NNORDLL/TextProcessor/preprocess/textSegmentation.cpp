#include "textPreprocess.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;
namespace nnor
{
	vector<wstring> nnor::split(const wstring &s, wchar_t delim)
	{
		vector<wstring> elems;
		wstringstream ss(s);
		wstring item;
		while (getline(ss, item, delim))
			elems.push_back(item);
		return elems;
	}

	vector<wchar_t> nnor::splitWord(wstring word)
	{
		vector<wchar_t> splittedWord;
		for (wchar_t character : word)
			splittedWord.push_back(character);
		return splittedWord;
	}
}