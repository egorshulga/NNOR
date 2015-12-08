///////////////////////////////////////////////////////////
//  TextProcessor.h
//  Implementation of the Class TextProcessor
//  Created on:      07-Dec-2015 09:52:45
//  Original author: egors
///////////////////////////////////////////////////////////

#if !defined(EA_AE186D2B_FFDD_4628_90E6_E3AE474A2C17__INCLUDED_)
#define EA_AE186D2B_FFDD_4628_90E6_E3AE474A2C17__INCLUDED_

#include <string>
#include <vector>

using namespace std;

class TextProcessor
{

public:
	TextProcessor();
	virtual ~TextProcessor();

	void performSplitting();
	vector<string> getWords();
	vector<vector<char>> getCharsByWords();
	vector<string> getChars();

private:
	vector<string> words;
	vector<vector<char>> charactersByWords;
	vector<string> characters;

	void splitIntoWords();
	void splitWordsIntoChars();
	void splitIntoChars();

};
#endif // !defined(EA_AE186D2B_FFDD_4628_90E6_E3AE474A2C17__INCLUDED_)
