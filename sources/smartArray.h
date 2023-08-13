#pragma once

#include <iostream>
#include <malloc.h>
#include <typeinfo>
using namespace std;

#include "tools.h"


template <typename T> // Don't use array in loops or use static array
class Array{
	// If it's need to pass Array to a function, use a links (&)

	public:

	Array(int size, bool resizeable = 0){
		if (size == 0){
			this->resizeable = 1;
			size_able = 10;
		}
		else{
			this->resizeable = resizeable;
			size_able = resizeable? size*2: size;
		}
		this->size = size;
		size_byte = sizeof(T);
		
		arr = (T*)malloc(size_byte * size_able);

		if (!arr)					// allocate failing 
			aborting("allocate failing");
	}

	Array(int size, T *data, bool resizeable = 0){
		this->resizeable = resizeable;
		this->size = size;
		size_byte = sizeof(T);
		size_able = resizeable? size*2: size;
		arr = (T*)malloc(size_byte * size_able);

		if (!arr)					// allocate failing 
			aborting("allocate failing");

		for (int i = 0; i < size; i++)
			arr[i] = data[i];
		delete [] data;
	}

	~Array(){
		free(arr);
	}
	
	T& operator [] (int index){ 	// getting array element link with given index
		if (index < 0)
			aborting("invalid index");
		if (index >= size){
			if(!resize(index+1)){
				aborting("resize failing");
			}
		}
		return arr[index];
	}


	int resize(int size_new){		// resizing array length
		if (!resizeable)
			return FAIL;
		if (size == size_new)
			return SUCCESS;
		size = size_new;
		if (size_able > size_new)
			return SUCCESS;

		size_able = size_new*2;
		arr = (T*)realloc(arr, size_byte * size_able);
		if (!arr)
			return FAIL;
		return SUCCESS;	
	}


	void aborting(const char* letter){
		cout << "Array error: " << letter << endl;
		cout << "In " << typeid(T).name() << " type.\n";
		abort();
	}


	int size;						// able area (elements)
	

	private:

	bool resizeable;
	T *arr;							// array ptr
	int size_able;				// area to resize to (elements)
	size_t size_byte;					// size of one element of array (bytes)
};
