#pragma once

#include <vector>
#include <iostream>

enum TritVal { False = -1, Unknown = 0, True = 1 };

class TritSet;	// description's going to be later


class TSReference
	// micro class for using [] as setter
{
private:

	// PRIVATE MEMBERS
	TritSet* set;
	int index;

public:

	// CONSTRUCTOR
	TSReference(TritSet* set, int index);

	// GETTERS
	TritSet* getTritSet();
	int getIndex();

	// SETTERS
	void setTritSet(TritSet* set);
	void setIndex(const int idex);

	// OPERATOR
	TSReference & operator = (TritVal val);
	TSReference & operator = (const TSReference& obj);
	operator TritVal () const;
};



class TritSet
	// TritSet class itself
{
private:

	// PRIVATE MEMBERS
	std::vector<unsigned int> tritSet;
	int capacity;

	// PRIVATE FUNCTIONS
	int getAmountOfBits();
	int getAmountOfBytes();
	int getAmountOfUints();

public:

	// CONSTRUCTOR
	TritSet(int capacity);

	// OPERATORS
	TritSet& operator = (const TritSet& obj);
	TritSet operator ! ();
	TritSet operator & (const TritSet& obj);
	TritSet operator | (const TritSet& obj);
	TritVal operator [] (const int index) const;	// getter
	TSReference operator [] (const int index);	// setter

	// GETTERS
	std::vector<unsigned int> getTritSet();
	TritVal getTrit(int index);
	int getCapacity();

	// SETTERS
	void setTrit(int index, TritVal val);

	// OTHER FUNCTIONS
	void printInfo();	// for debug
	int cardinality(TritVal val);
	void trim(int lastIndex);
};