#pragma once

#include "WordNFreq.h"

class WordCounter
{
private:

	std::vector<WordNFreq> WNF_vec;
	int totalNrOfWords;
	int totalNrOfDiffWords;
	void swapWNF(WordNFreq& obj1, WordNFreq& obj2)
	{
		WordNFreq tmp = obj1;
		obj1 = obj2;
		obj2 = tmp;
	}

	void sortFreqDown(int endIndex)
	{
		int minIndex;
		endIndex--;

		while (endIndex > 0)
		{
			minIndex = 0;

			for (int i = 0; i <= endIndex; i++)
			{
				if (this->WNF_vec[i].getFreq() < this->WNF_vec[minIndex].getFreq())
					minIndex = i;
			}

			this->swapWNF(this->WNF_vec[minIndex], this->WNF_vec[endIndex]);
			endIndex--;
		}
	}

public:

	void read(const char* in_filename)
	{
		std::ifstream in_file;
		in_file.open(in_filename);

		if (!in_file.is_open())
			std::cout << "ERROR::COULD NOT_OPEN_INPUT_FILE" << std::endl;
		else
			std::cout << "INPUT FILE " << in_filename << " OPENED SUCCESSFULLY" << std::endl << std::endl;

		std::vector<char> currWord;

		char* currSymb = new char[2];
		int nrOfLetters = 0;
		bool isNew = true;

		this->totalNrOfWords = 0, this->totalNrOfDiffWords = 0;


		while (!in_file.eof())
		{
			in_file.get(currSymb, 2);
			//std::cout << currSymb << std::endl;

			if (!(
				(*currSymb < '0')
				|| ((*currSymb > '9') && (*currSymb < 'A'))
				|| ((*currSymb > 'Z') && (*currSymb < 'a'))
				|| (*currSymb > 'z')
				))	// if NOT end of word
			{
				currWord.push_back(*currSymb);
				nrOfLetters++;
			}
			else
			{
				isNew = true;
				this->totalNrOfWords++;

				for (int i = 0; i < this->totalNrOfDiffWords; i++)
				{
					if (this->WNF_vec[i].compare(currWord, nrOfLetters))
					{
						isNew = false;
						this->WNF_vec[i].incFreq();
					}
				}

				if (isNew)
				{
					WordNFreq wnf;

					wnf.setWord(currWord);
					wnf.setFreq(1);
					wnf.setNrOfLetters(nrOfLetters);

					this->WNF_vec.push_back(wnf);

					this->totalNrOfDiffWords++;
				}

				for (int i = 0; i < nrOfLetters; i++)
					currWord.pop_back();

				nrOfLetters = 0;
			}
		}
	}

	void write(const char* out_filename)
	{
		std::cout << "TOTAL NUMBER OF DIFFERENT WORDS: " << totalNrOfDiffWords << std::endl;
		std::cout << "TOTAL NUMBER OF ALL WORDS: " << totalNrOfWords << std::endl << std::endl;
		std::cout << "BEFORE SORTING: " << std::endl << std::endl;

		for (int i = 0; i < this->totalNrOfDiffWords; i++)
		{
			this->WNF_vec[i].countPercent(this->totalNrOfWords);
			this->WNF_vec[i].printInfo();
		}

		this->sortFreqDown(this->totalNrOfDiffWords);

		std::cout << std::endl << "AFTER SORTING: " << std::endl << std::endl;

		for (int i = 0; i < this->totalNrOfDiffWords; i++)
			this->WNF_vec[i].printInfo();

		std::ofstream out_file;
		out_file.open(out_filename);

		if (!out_file.is_open())
			std::cout << "ERROR::COULD_NOT_OPEN_OUTPUT_FILE" << std::endl;
		else
			std::cout << "OUTPUT FILE " << out_filename << " OPENED SUCCESSFULLY" << std::endl << std::endl;

		for (int i = 0; i < this->totalNrOfDiffWords; i++)
		{
			for (int j = 0; j < this->WNF_vec[i].getNrOfLetters(); j++)
				out_file << this->WNF_vec[i].getWord()[j];

			out_file << ", ";
			out_file << this->WNF_vec[i].getFreq();
			out_file << ", ";
			out_file << this->WNF_vec[i].countPercent(this->totalNrOfWords) << std::endl;
		}

		std::cout << "WORD COUNTING FINISHED SUCCESSFULLY - CHECK OUTPUT FILE" << std::endl;
	}

};