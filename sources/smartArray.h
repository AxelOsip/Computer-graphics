#pragma once

#include <stdio.h>
#include <malloc.h>
#include <typeinfo>

#include "tools.h"


template <typename T> // Don't use in loop
class Array{
	// If it's need to pass Array to a function, use a links (&)

	public:

	Array(int size, bool resizeable = 0){
		this->resizeable = resizeable;
		this->size = size;
		size_byte = sizeof(T);
		size_able = resizeable? size*2: size;
		arr = (T*)malloc(size_byte * size_able);

		if (!arr){					// Failed alloc
			printf("Error to allicate array of '%s' type.\n", typeid(T).name());
			abort();
		}
	}

	~Array(){
		free(arr);
	}
	
	T& operator [] (int index){ 	// getting array element link with given index
		if (index >= size || index < 0){
			printf("\nInvalid index %d for array of '%s' type.\n", index, typeid(T).name());
			abort();
		}
		return arr[index];
	}

	int resize(int size_new){		// resizing array length
		if (!resizeable)
			return FAIL;
		size = size_new;
		if (size_able > size_new)
			return SUCCESS;

		size_able = size_new*2;
		arr = (T*)realloc(arr, size_byte * size_able);
		if (!arr)
			return FAIL;
		return SUCCESS;	
	}

	int size;						// able area (elements)
	

	private:

	bool resizeable;
	T *arr;							// array ptr
	int size_able;				// area to resize to (elements)
	size_t size_byte;					// size of one element of array (bytes)
};
