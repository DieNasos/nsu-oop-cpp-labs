#include "TritSet.h"

// TritSet

// PRIVATE FUNCTIONS

int TritSet::getAmountOfBits()
{
	return this->capacity * 2;
}

int TritSet::getAmountOfBytes()
{
	int amountOfBits = this->getAmountOfBits();
	int amountOfBytes = amountOfBits / 8;

	if (amountOfBits % 8 != 0)
		amountOfBytes++;

	return amountOfBytes;
}

int TritSet::getAmountOfUints()
{
	int amountOfBytes = this->getAmountOfBytes();

	int amountOfUints = amountOfBytes / sizeof(unsigned int);

	if (amountOfBytes % sizeof(unsigned int) != 0)
		amountOfUints++;

	return amountOfUints;
}

// CONSTRUCTOR
TritSet::TritSet(int capacity)
{
	if (capacity <= 0)
		std::cout << "ERROR! CAPACITY SHOULD NOT BE <= 0!" << std::endl;
	else
	{
		this->capacity = capacity;

		int amountOfBits = this->getAmountOfBits();
		int amountOfUints = this->getAmountOfUints();

		for (int i = 1; i <= amountOfUints; i++)
		{
			if (sizeof(unsigned int) == 2)
				this->tritSet.push_back(43690);	// 43690(10) == 1010101010101010(2)
			else
				this->tritSet.push_back(2863311530);	// 2863311530(10) == 10101010101010101010101010101010(2)
		}

		this->tritSet[amountOfUints - 1] =
			this->tritSet[amountOfUints - 1] << (amountOfUints * sizeof(unsigned int) * 8 - amountOfBits);
	}
}

// OPERATORS

TritSet& TritSet::operator = (const TritSet& obj)
{
	if (this == &obj)
		return *this;

	for (int i = 1; i <= this->getAmountOfUints(); i++)
		this->tritSet.pop_back();	// deleting old uints

	this->capacity = obj.capacity;

	for (int i = 0; i < this->getAmountOfUints(); i++)
		this->tritSet.push_back(obj.tritSet[i]);	// adding obj's uints

	return *this;
}

TritSet TritSet::operator ! ()
{
	// creating input tritset's copy
	TritSet in(this->capacity);
	in.tritSet = this->tritSet;

	TritSet out(this->capacity);	// creating output tritset

	for (int i = 0; i < this->getAmountOfUints(); i++)
		out.tritSet.pop_back();

	unsigned int currUint = 0;
	short move = 0;

	for (int i = 0; i < out.capacity; i++)
	{
		if ((i % (sizeof(unsigned int) * 4) == 0) && (i != 0))
		{
			out.tritSet.push_back(currUint);
			currUint = 0;
			move = 0;
		}

		if (in.getTrit(i) == True)
		{
			currUint = currUint << 2;
			move += 2;
		}

		if (in.getTrit(i) == False)
		{
			currUint = currUint << 2;
			currUint += 1;
			move += 2;
		}

		if (in.getTrit(i) == Unknown)
		{
			currUint = currUint << 2;
			currUint += 2;
			move += 2;
		}
	}

	currUint = currUint << sizeof(unsigned int) * 8 - move;
	out.tritSet.push_back(currUint);

	return out;
}

TritSet TritSet::operator & (const TritSet& obj)
{
	// creating input tritsets' copies
	TritSet obj1 = *this;
	TritSet obj2 = obj;

	int smallestCapacity;

	// output tritset's going to have the smallest capacity
	if (obj1.capacity < obj2.capacity)
		smallestCapacity = obj1.capacity;
	else
		smallestCapacity = obj2.capacity;

	TritSet out(smallestCapacity);	// creating output tritset (out == obj1 & obj2)

	for (int i = 0; i < smallestCapacity; i++)
	{
		if ((obj1.getTrit(i) == True) && (obj2.getTrit(i) == True))
			out.setTrit(i, True);
		else if ((obj1.getTrit(i) == False) || (obj2.getTrit(i) == False))
			out.setTrit(i, False);
		else
			out.setTrit(i, Unknown);
	}

	return out;
}

TritSet TritSet::operator | (const TritSet& obj)
{
	// creating input tritsets' copies
	TritSet obj1 = *this;
	TritSet obj2 = obj;

	int smallestCapacity;

	// output tritset's going to have the smallest capacity
	if (obj1.capacity < obj2.capacity)
		smallestCapacity = obj1.capacity;
	else
		smallestCapacity = obj2.capacity;

	TritSet out(smallestCapacity);	// creating output tritset (out == obj1 | obj2)

	for (int i = 0; i < smallestCapacity; i++)
	{
		if ((obj1.getTrit(i) == True) || (obj2.getTrit(i) == True))
			out.setTrit(i, True);
		else if ((obj1.getTrit(i) == False) && (obj2.getTrit(i) == False))
			out.setTrit(i, False);
		else
			out.setTrit(i, Unknown);
	}

	return out;
}

TritVal TritSet::operator [] (const int index) const
// getter
{
	int indOfUint = (index + 1) * 2 / 8 / sizeof(unsigned int);
	int modIndex = index % 8;

	unsigned int currUint = this->tritSet[indOfUint];

	currUint = currUint >> 8 * sizeof(unsigned int) - (modIndex + 1) * 2;
	currUint = currUint << 8 * sizeof(unsigned int) - (modIndex + 1) * 2 + modIndex * 2;

	if (sizeof(unsigned int) == 2)
	{
		if (currUint == 16384)
			// 0100000000000000 = True
			return True;
		else if (currUint == 0)
			// 0000000000000000 = False
			return False;
		else if (currUint == 32768)
			// 1000000000000000 = Unknown
			return Unknown;
	}
	else
	{
		if (currUint == 1073741824)
			// 01000000000000000000000000000000 = True
			return True;
		else if (currUint == 0)
			// 00000000000000000000000000000000 = False
			return False;
		else if (currUint == 2147483648)
			// 10000000000000000000000000000000 = Unknown
			return Unknown;
	}
}

TSReference TritSet::operator [] (const int index)
// setter
{
	return *new TSReference(this, index);
}

// GETTERS

std::vector<unsigned int> TritSet::getTritSet()
{
	return this->tritSet;
}

TritVal TritSet::getTrit(int index)
{
	int indOfUint = (index + 1) * 2 / 8 / sizeof(unsigned int);
	int modIndex = index % 8;

	unsigned int currUint = this->tritSet[indOfUint];

	currUint = currUint >> 8 * sizeof(unsigned int) - (modIndex + 1) * 2;
	currUint = currUint << 8 * sizeof(unsigned int) - (modIndex + 1) * 2 + modIndex * 2;

	if (sizeof(unsigned int) == 2)
	{
		if (currUint == 16384)
			// 0100000000000000 = True
			return True;
		else if (currUint == 0)
			// 0000000000000000 = False
			return False;
		else if (currUint == 32768)
			// 1000000000000000 = Unknown
			return Unknown;
	}
	else
	{
		if (currUint == 1073741824)
			// 01000000000000000000000000000000 = True
			return True;
		else if (currUint == 0)
			// 00000000000000000000000000000000 = False
			return False;
		else if (currUint == 2147483648)
			// 10000000000000000000000000000000 = Unknown
			return Unknown;
	}
}

int TritSet::getCapacity()
{
	return this->capacity;
}

// SETTERS

void TritSet::setTrit(int index, TritVal val)
{
	int indOfUint = (index + 1) * 2 / 8 / sizeof(unsigned int);
	index %= 8;

	int move;
	move = 8 * sizeof(unsigned int) - (index) * 2;

	unsigned int left = this->tritSet[indOfUint];

	if (move == 8 * sizeof(unsigned int))
		left = 0;
	else
	{
		left = left >> move;
		left = left << move;
	}

	unsigned int right = this->tritSet[indOfUint];
	move = (index + 1) * 2;
	right = right << move;
	right = right >> move;

	unsigned int between;

	if (sizeof(unsigned int) == 2)
	{
		if (val == True)
			// 0100000000000000 = True
			between = 16384;
		else if (val == False)
			// 0000000000000000 = False
			between = 0;
		else if (val == Unknown)
			// 1000000000000000 = Unknown
			between = 32768;
	}
	else
	{
		if (val == True)
			// 01000000000000000000000000000000 = True
			between = 1073741824;
		else if (val == False)
			// 00000000000000000000000000000000 = False
			between = 0;
		else if (val == Unknown)
			// 10000000000000000000000000000000 = Unknown
			between = 2147483648;
	}

	between = between >> index * 2;

	this->tritSet[indOfUint] = 0;
	this->tritSet[indOfUint] = left | between | right;

	/*

		example:
		
		origin tritset: 10 01 10 00 10 00 10 01
		>>> setTrit(2, True);
		left == 10 01 . 00 00 00 00 00 00
		right == 00 00 00 . 00 10 00 10 01
		between == 00 00 . 01 . 00 00 00 00 00
		tritSet[2] == left | between | right == 10 01 . 01 . 00 10 00 10 01

	*/
}

void TritSet::printInfo()
{
	// for debug

	std::cout << "PRINTING INFO ABOUT TRITSET" << std::endl;

	for (int i = 0; i < this->capacity; i++)
	{
		std::cout << i << ": ";

		if (this->getTrit(i) == True)
			std::cout << "True" << std::endl;
		if (this->getTrit(i) == False)
			std::cout << "False" << std::endl;
		if (this->getTrit(i) == Unknown)
			std::cout << "Unknown" << std::endl;
	}
}

int TritSet::cardinality(TritVal val)
{
	// returns amount of TritVal == val in tritset

	int count = 0;

	for (int i = 0; i < this->capacity; i++)
		if (this->getTrit(i) == val)
			count++;

	return count;
}

void TritSet::trim(int lastIndex)
{
	// forgets (= Unknown) trits from lastIndex -> til the end of tritset

	for (int i = lastIndex; i < this->capacity; i++)
		this->setTrit(i, Unknown);
}

//////////

// TSReference

// CONSTRUCTOR
TSReference::TSReference(TritSet* set, int index)
{
	this->set = set;
	this->index = index;
}

// GETTERS

TritSet* TSReference::getTritSet()
{
	return this->set;
}

int TSReference::getIndex()
{
	return this->index;
}

// SETTERS

void TSReference::setTritSet(TritSet* set)
{
	this->set = set;
}

void TSReference::setIndex(const int index)
{
	this->index = index;
}

// OPERATORS

TSReference &TSReference::operator = (TritVal val)
{
	this->set->setTrit(this->index, val);
	return *this;
}

TSReference & TSReference::operator = (const TSReference& obj)
{
	this->set->setTrit(this->index, (TritVal)obj);

	return *this;
}

TSReference::operator TritVal () const
{
	return this->set->getTrit(this->index);
}