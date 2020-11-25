#include "SortBlock.h"

static BlockMaker<SortBlock> sortBlockMaker("SortBlock");

void SortBlock::swap(string* str1, string* str2)
{
	string str3;

	str3 = *str1;
	*str1 = *str2;
	*str2 = str3;
}

bool SortBlock::isBigger(string str1, string str2)
{
	// str1 >=? str2

	bool is_bigger = true;
	int minSize;

	if (str1.size() < str2.size())
		minSize = str1.size();
	else
		minSize = str2.size();

	for (auto i = 0; i < minSize; i++)
	{
		if (str1[i] < str2[i])
		{
			is_bigger = false;
			break;
		}
	}

	return is_bigger;
}

void SortBlock::work(string* text, vector<string> params)
{
	// params.size() == 0

	if (text->size() == 0)
		throw std::exception("ERROR: text is empty");

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

	int j, k = separatedText.size();

	for (i = 0; i < separatedText.size() - 1; i++)	// sorting lines using bubble method
	{
		for (j = 0; j < k - 1; j++)
			if (this->isBigger(separatedText[j], separatedText[j + 1]))
				swap(&separatedText[j], &separatedText[j + 1]);

		k--;
	}

	string sortedText = "";

	for (i = 0; i < separatedText.size(); i++)
		sortedText += separatedText[i];	// uniting lines back again

	*text = sortedText;
}

BLOCK_TYPE SortBlock::getType()
{
	return BLOCK_TYPE::INOUT;
}

Worker* SortBlock::createCopy()
{
	return new SortBlock();
}

int SortBlock::getNrOfParams()
{
	return 0;
}