#include "GrepBlock.h"

namespace {
	static BlockMaker<GrepBlock> grepBlockMaker("GrepBlock");
}
bool GrepBlock::containsWord(string str, string word)
{
	bool contains = false;

	for (auto i = 0; i < str.size(); i++)
	{
		if ((i + word.size() - 1 > str.size()) && (contains == false))
			break;

		if (str[i] == word[0])
		{
			for (auto j = 1; j < word.size(); j++)
			{
				if (str[i + j] == word[j])
				{
					if (j == word.size() - 1)
						contains = true;
				}
			}
		}
	}
	
	return contains;
}

void GrepBlock::work(string* text, vector<string> params)
{
	// params[0] == word

	if (params.size() == 0)
		throw std::exception("ERROR: no parameters");

	if (text->size() == 0)
		throw std::exception("ERROR: text is empty");

	if (params[0] == "")
		throw std::exception("ERROR: word is empty");

	vector<string> separatedText;	// vector of text's lines
	string currStr = "";
	char currSymbol;

	int i = 0;

	while (i < text->size())	// separating text on lines
	{
		currSymbol = text->at(i);

		if ((currSymbol != '\n') && ((i != text->size() - 1)))
			currStr += currSymbol;
		else
		{
			separatedText.push_back(currStr + '\n');
			currStr = "";
		}

		i++;
	}

	string selectedText = "";

	for (i = 0; i < separatedText.size(); i++)	// uniting together lines that contain word
		if (this->containsWord(separatedText[i], params[0]))
			selectedText += separatedText[i];

	*text = selectedText;
}

BLOCK_TYPE GrepBlock::getType()
{
	return BLOCK_TYPE::INOUT;
}

Worker* GrepBlock::createCopy()
{
	return new GrepBlock();
}

int GrepBlock::getNrOfParams()
{
	return 1;
}