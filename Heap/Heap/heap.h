#ifndef HEAP_H
#define HEAP_H
#include <assert.h>
#include <algorithm>
using namespace std;

template <typename k, typename T>
class MaxHeap{
    struct HeapItem{
	k key;
	T _item;
};
	//each item in heap will be HeapItem (a <key, _item> pair). Both key and value can be of the same datatype or different data type.
	// Key and value can be of a user-defined class as well. If key is of non-primitive datatype, then the > and < operators must be overloaded.
private:
	HeapItem *arr;
	int capacity;
	int size;

	void doubleCapacity(){
		if (this->arr==nullptr){
			this->arr = new HeapItem[1];
			this->capacity = 1;
			return;
		}

		int newCapacity = capacity*2;
		HeapItem *newArr = new HeapItem[newCapacity];

		for (int i = 0; i < this->size; i++){
			newArr[i] = this->arr[i];
		}

		if (this->arr!=nullptr)
		delete this->arr;

		this->capacity = newCapacity;
		this->arr = newArr;
	}

	void shiftUp(int index){
		if (index < 1)
			return;

		int parent = (index-1) / 2;

		if (this->arr[index].key > this->arr[parent].key){
		   swap(this->arr[index], this->arr[parent]);
		   shiftUp(parent);
		}
	    return;
	}

	void shiftDown(int index){
		int maxIndex = -1;
		int lChildIndex = index * 2+1;
		int rChildIndex = (index * 2) + 2;

		if (lChildIndex < size){
			if (arr[index].key < arr[lChildIndex].key){
		    	maxIndex = lChildIndex;
			}
		}

		if (rChildIndex < size){
			if (arr[(maxIndex == -1 ? index : maxIndex)].key < arr[rChildIndex].key){
				maxIndex = rChildIndex;
			}
		}

		if (maxIndex == -1)
			return;

		swap(arr[index], arr[maxIndex]);
		shiftDown(maxIndex);
	}

public:
	MaxHeap(){
		this->arr = nullptr;
		this->capacity = 0;
		this->size = 0;
	}

	MaxHeap(int _capacity){
		assert(_capacity >= 1);

		this->arr = new HeapItem[_capacity];
		this->capacity = _capacity;
		this->size = 0;
	}

	void insert(k const key, T const _item){
		if (this->size == this->capacity){
			doubleCapacity();
		}
		this->arr[size].key = key;
		this->arr[size]._item = _item;

		shiftUp(size);
		this->size++;
	}


	T getMax(){
		assert(size != 0);
		return this->arr[0]._item;
	}

	void popMax(){
		assert(size != 0);
		swap(arr[0], arr[this->size-1]);

		size--;

		//shift down
		shiftDown(0);
	}
	
	bool isEmpty() const{
		return (size == 0);
	}

	void deleteAll(){
		if (this->arr != nullptr){
			delete[]arr;
			arr = nullptr;
			this->capacity = 0;
			this->size = 0;
		}
	}

	~MaxHeap(){
		deleteAll();
	}
};

#endif // HEAP_H