#pragma once

#include <string>
#include <vector>

using namespace std;

namespace nnor
{
	vector<wstring> split(const wstring &s, wchar_t delim);

	vector<wchar_t> splitWord(wstring word);
}