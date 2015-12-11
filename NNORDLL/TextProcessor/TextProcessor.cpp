#include "TextProcessor.h"

#include "preprocess/textPreprocess.h"

namespace nnor
{
	TextProcessor::TextProcessor()
	{ }

	void TextProcessor::setText(wstring text)
	{
		this->text = text;
		splitIntoWords();
		splitWordsIntoChars();
		splitIntoChars();
	}

	wstring TextProcessor::getText()
	{
		return text;
	}

	void TextProcessor::splitIntoWords()
	{
		words = split(text, ' ');
	}

	void TextProcessor::splitWordsIntoChars()
	{
		for (auto word : words)
		{
			charsByWords.push_back(splitWord(word));
		}
	}

	void TextProcessor::splitIntoChars()
	{
		for (wchar_t character : text)
		{
			characters.push_back(character);
		}
	}

	vector<wstring> TextProcessor::getWords()
	{
		return words;
	}

	vector<vector<wchar_t>> TextProcessor::getCharsByWords()
	{
		return charsByWords;
	}

	vector<wchar_t> TextProcessor::getCharacters()
	{
		return characters;
	}

	void TextProcessor::performSplitting()
	{
		splitIntoWords();
		splitWordsIntoChars();
		splitIntoChars();
	}
}