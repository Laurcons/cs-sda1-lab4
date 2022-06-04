#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//SortedBag::Node** tableCopy;
	int size;
	int current;
	TComp* elements;

public:
	~SortedBagIterator();
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	void last();
	void previous(); // lab activity
};

