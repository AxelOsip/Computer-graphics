#pragma once
#include <stdio.h>
#include <malloc.h>
#include <typeinfo>

// Status
#define SUCCESS 	1
#define FAIL 		0

// Colors
#define CL_RED 		0xff0000
#define CL_GREEN 	0x00ff00
#define CL_BLUE 	0x0000ff
#define CL_CYAN 	0x00ffff
#define CL_MAGENTA	0xff00ff
#define CL_YELLOW 	0xffff00
#define CL_WHITE 	0xffffff
#define CL_BLACK 	0x000000

// Affine matrix
#define MAT_mir_Ox 				imat3{1,0,0, 0,-1,0, 0,0,1};		// mirroring mftrix on the Ox axis (-)
#define MAT_mir_Oy 				imat3{-1,0,0, 0,1,0, 0,0,1};		// mirroring mftrix on the Oy axis (|)
#define MAT_mir_xy 				imat3{0,1,0, 1,0,0, 0,0,1};			// mirroring mftrix on the xy axis (/)
#define MAT_mir_mxy 			imat3{0,1,0, 1,0,0, 0,0,1};			// mirroring mftrix on the -xy axis (\)
#define MAT_shift(dx, dy)		imat3(1,0,dx, 0,1,dy, 0,0,1)		// transporting matrix to the (dx, dy) local cords
#define MAT_rot_clw(a)			imat3(cos(a),sin(a),1, cos(a),-sin(a),1, 0,0,1)	// rotating matrix clockwise (↻)
#define MAT_rot_ctclw(a) 		imat3(cos(a),-sin(a),1, cos(a),sin(a),1, 0,0,1)	// rotating matrix counterclockwise (↺)

// Smart ptr
template <typename T>
class Array{

	public:

	Array(int size, bool resizeable = 0){
		this->resizeable = resizeable;
		this->size = size;
		size_byte = sizeof(int);
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
