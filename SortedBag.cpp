#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->r = r;
	this->hashCount = 10;
	this->elemCount = 0;
	this->table = new Node*[this->hashCount];
	for (int i = 0; i < this->hashCount; i++)
		this->table[i] = nullptr;
}

// O(1) supposedly
int SortedBag::hash(TComp elem) const {
	if (elem < 0)
		elem = -elem;
	return elem % this->hashCount;
}

// theta(m + n)
void SortedBag::tryResizeAndRehash() {
	if (100 * this->elemCount / this->hashCount < 50)
		return;
	int oldHashCount = this->hashCount;
	Node** oldTable = this->table;
	this->hashCount *= 2;
	this->table = new Node * [this->hashCount];
	Node** tailTable = new Node * [this->hashCount];
	for (int i = 0; i < this->hashCount; i++)
		this->table[i] = nullptr,
		tailTable[i] = nullptr;
	for (int i = 0; i < oldHashCount; i++) {
		auto curr = oldTable[i];
		Node* next = nullptr;
		while (curr != nullptr) {
			next = curr->next;
			curr->next = nullptr;
			int newKey = hash(curr->elem);
			if (table[newKey] == nullptr) {
				table[newKey] = curr;
				tailTable[newKey] = curr;
			}
			else {
				tailTable[newKey]->next = curr;
				tailTable[newKey] = curr;
			}
			curr = next;
		}
	}
	delete[] oldTable;
	delete[] tailTable;
}

// O(1) amortized?
void SortedBag::add(TComp e) {
	this->tryResizeAndRehash();
	Node* node = new Node;
	node->elem = e;
	int key = this->hash(e);
	Node* curr = this->table[key];
	Node* prev = nullptr;
	while (curr != nullptr && this->r(curr->elem, e))
		prev = curr,
		curr = curr->next;
	node->next = curr;
	if (prev == nullptr)
		this->table[key] = node;
	else
		prev->next = node;
	this->elemCount++;
}

// O(1) amortized?
bool SortedBag::remove(TComp e) {
	int key = this->hash(e);
	Node* curr = this->table[key];
	Node* prev = nullptr;
	while (curr != nullptr && curr->elem != e)
		prev = curr,
		curr = curr->next;
	if (curr == nullptr)
		return false;
	Node* toDelete = curr;
	if (prev == nullptr)
		this->table[key] = curr->next;
	else
		prev->next = curr->next;
	delete toDelete;
	this->elemCount--;
	return true;
}

// O(1) amortized?
bool SortedBag::search(TComp elem) const {
	int key = this->hash(elem);
	Node* curr = this->table[key];
	while (curr != nullptr && curr->elem != elem)
		curr = curr->next;
	return curr != nullptr;
}

// O(1) amortized?
int SortedBag::nrOccurrences(TComp elem) const {
	int key = this->hash(elem);
	Node* curr = this->table[key];
	while (curr != nullptr && curr->elem != elem)
		curr = curr->next;
	if (curr == nullptr)
		return 0;
	int count = 0;
	while (curr != nullptr && curr->elem == elem)
		count++,
		curr = curr->next;
	return count;
}

// theta(1)
int SortedBag::size() const {
	return this->elemCount;
}

// theta(1)
bool SortedBag::isEmpty() const {
	return this->size() == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

// theta(n + m)
SortedBag::~SortedBag() {
	for (int i = 0; i < this->hashCount; i++) {
		if (this->table[i] == nullptr)
			continue;
		Node* curr = this->table[i];
		Node* prev = nullptr;
		while (curr != nullptr) {
			prev = curr;
			curr = curr->next;
			delete prev;
		}
	}
	delete[] table;
}
