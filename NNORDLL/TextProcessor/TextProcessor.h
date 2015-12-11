#pragma once

#include <string>
#include <vector>

using namespace std;

namespace nnor 
{
	class TextProcessor
	{
	public:
		TextProcessor();

	private:	//Input data
		wstring text = L"";

	public:
		void setText(wstring text);
		wstring getText();

	private:	//Output data
		vector<wstring> words;
		vector<vector<wchar_t>> charsByWords;
		vector<wchar_t> characters;

		void splitIntoWords();
		void splitWordsIntoChars();
		void splitIntoChars();

	public:
		vector<wstring> getWords();
		vector<vector<wchar_t>> getCharsByWords();
		vector<wchar_t> getCharacters();

		void performSplitting();
	};
}
