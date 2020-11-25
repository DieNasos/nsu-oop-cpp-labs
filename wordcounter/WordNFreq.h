#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class WordNFreq
{
private:

	std::vector<char> word;
	int freq;
	int nrOfLetters;

public:

	std::vector<char> getWord()
	{
		return this->word;
	}

	int getFreq()
	{
		return this->freq;
	}

	int getNrOfLetters()
	{
		return this->nrOfLetters;
	}

	void addLetter(char letter)
	{
		this->word.push_back(letter);
	}

	void incFreq()
	{
		this->freq++;
	}

	int countPercent(int totalNrOfWords)
	{
		return this->freq / double(totalNrOfWords) * 100.0;
	}

	void setWord(std::vector<char> word)
	{
		this->word = word;
	}

	void setFreq(int freq)
	{
		this->freq = freq;
	}

	void setNrOfLetters(int nrOfLetters)
	{
		this->nrOfLetters = nrOfLetters;
	}

	WordNFreq& operator = (const WordNFreq& obj)
	{
		if (this == &obj)
			return *this;

		this->setWord(obj.word);
		this->setFreq(obj.freq);
		this->setNrOfLetters(obj.nrOfLetters);

		return *this;
	}

	bool compare(std::vector<char> word1, int nrOfLetters1)
		// true <=> equal
		// false <=> not equal
	{
		if (nrOfLetters1 != this->nrOfLetters)
			return false;

		for (int i = 0; i < nrOfLetters1; i++)
			if (this->word[i] != word1[i])
				return false;

		return true;
	}

	void printInfo()
		// for debug
	{
		std::cout << "word: ";

		for (int i = 0; i < this->nrOfLetters; i++)
			std::cout << this->word[i];

		std::cout << std::endl << "freq: " << this->freq << std::endl << std::endl;
	}
};