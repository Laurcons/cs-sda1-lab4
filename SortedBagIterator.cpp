#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// O(m + n)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	// initialization
	size = bag.size();
	elements = new TComp[size];
	current = size != 0 ? 0 : -1;
	// make a copy of the table
	auto tableCopy = new SortedBag::Node * [bag.hashCount];
	for (int i = 0; i < bag.hashCount; i++)
		tableCopy[i] = bag.table[i];
	// build the list of elements
	int k = 0;
	while (1) {
		TComp smallest = NULL_TCOMP;
		int smallestIndex = -1;
		for (int i = 0; i < bag.hashCount; i++) {
			auto& curr = tableCopy[i];
			if (curr == nullptr)
				continue;
			if (bag.r(curr->elem, smallest) || smallestIndex == -1)
				smallest = curr->elem,
				smallestIndex = i;
		}
		if (smallestIndex == -1) {
			break;
		}
		else {
			elements[k++] = smallest;
			tableCopy[smallestIndex] =
				tableCopy[smallestIndex]->next;
		}
	}
	// cleanup
	delete[] tableCopy;
}

TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw std::exception();
	return elements[current];
}

bool SortedBagIterator::valid() {
	return current != -1 && current != size;
}

void SortedBagIterator::next() {
	if (!valid())
		throw std::exception();
	current++;
}

void SortedBagIterator::first() {
	current = size != 0 ? 0 : -1;
}

void SortedBagIterator::last() {
	current = size - 1;
}

void SortedBagIterator::previous() {
	if (!valid())
		throw std::exception();
	current--;
}

SortedBagIterator::~SortedBagIterator() {
	delete[] elements;
}

/*SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	// copy the table
	this->tableCopy = new SortedBag::Node*[this->bag.hashCount];
	for (int i = 0; i < bag.hashCount; i++)
		this->tableCopy[i] = bag.table[i];
	this->currentIndex = -1;
	this->advance();
}

TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw std::exception();
	return tableCopy[currentIndex]->elem;
}

bool SortedBagIterator::valid() {
	return currentIndex != -1;
}

// O(m)
void SortedBagIterator::advance() {
	// - find the current smallest item in the tableCopy
	// - set it as current
	// - advance the pointer one position
	TComp smallest = NULL_TCOMP;
	int smallestIndex = -1;
	for (int i = 0; i < bag.hashCount; i++) {
		auto& curr = this->tableCopy[i];
		if (curr == nullptr)
			continue;
		if (bag.r(curr->elem, smallest) || smallestIndex == -1)
			smallest = curr->elem,
			smallestIndex = i;
	}
	if (smallestIndex == -1) {
		this->currentIndex = -1;
	}
	else {
		this->currentIndex = smallestIndex;
		this->tableCopy[smallestIndex] =
			this->tableCopy[smallestIndex]->next;
	}
}

void SortedBagIterator::next() {
	if (!valid())
		throw std::exception();
	advance();
}

void SortedBagIterator::previous() {
	if (!valid())
		throw std::exception();
	retreat();
}

void SortedBagIterator::first() {
	for (int i = 0; i < bag.hashCount; i++)
		this->tableCopy[i] = bag.table[i];
	this->current = NULL_TCOMP;
	this->advance();

}

SortedBagIterator::~SortedBagIterator() {
	delete[] this->tableCopy;
}
*/