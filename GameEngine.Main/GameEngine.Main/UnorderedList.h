#pragma once

#include <string>

template <class T>
class UnorderedList {
private:
	unsigned int count;
	T* items;
	unsigned int length;

	void IncreaseSize(){
		length = length * 2 + 1;
		T* tempItems = new T[length]();
		std::memcpy(tempItems, items, sizeof(T) * count);
		delete[] items;
		items = tempItems;
	}


public:

	unsigned int Count() {
		return count;
	}

	T Pop() {
		return items[--count];
	}

	void Push(T item) {
		if (count == length) {
			IncreaseSize();
		}
		items[count++] = item;
	}

	void Reset() {
		if (length > 0) {
			delete items;
			length = 0;
		}
		items = new T[length]();
		count = 0;
	}


	UnorderedList() :
		count(0),
		items(NULL),
		length(0) {

	}
	~UnorderedList() {
		delete items;
	}

	T operator [] (unsigned int index) {
		return items[index];
	}

};