/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"
#include <algorithm>

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
		int deque_size;
		int initial_array_capacity;
		int array_capacity;
		int ifront;
		int iback;
		Type * Array;
		// Any private member functions
		//   - helper functions for resizing your array?

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n ) :
// Your initalization list
deque_size(0),
initial_array_capacity(std::max(16, n)),
array_capacity( initial_array_capacity ),
ifront(0),
iback(0),
Array( new Type[array_capacity] )
{
	// Enter your implementation here
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque ) :
// Your initalization list
deque_size(deque.deque_size),
initial_array_capacity(deque.initial_array_capacity),
array_capacity(deque.array_capacity),
ifront(deque.ifront),
iback(deque.iback),
Array( new Type[array_capacity] )
{
	for (int i = 0; i < deque.array_capacity; i++)
	{
		Array[i] = deque.Array[i];
	}
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque ) :
// Your initalization list
deque_size(0),
initial_array_capacity(0),
array_capacity(0),
ifront(0),
iback(0),
Array(nullptr)
{
	swap(deque);
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
	delete [] Array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here
	return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	//if array is empty return true.
	if (deque_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
	//If there are no elements inside the array throw underflow()
	if (deque_size == 0)
	{
		throw underflow();
	}

	return Array[ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
	//If there are no elements inside the array throw underflow()
	if (deque_size == 0)
	{
		throw underflow();
	}
	
	return Array[iback];
}

template <typename Type>
void Resizable_deque<Type>::swap(Resizable_deque<Type> &deque) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );
	std::swap(ifront,                 deque.ifront);
	std::swap(iback,                  deque.iback);
	std::swap(initial_array_capacity, deque.initial_array_capacity);
	std::swap(array_capacity,         deque.array_capacity);
	std::swap(deque_size,             deque.deque_size);
	std::swap(Array,                  deque.Array);
	// Enter your implementation here
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=(Resizable_deque<Type> const &rhs) {
	// This is done for you...
	Resizable_deque<Type> copy(rhs);
	swap(copy);

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=(Resizable_deque<Type> &&rhs) {
	// This is done for you...
	swap(rhs);

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front(Type const &obj) {
	// Enter your implementation here
	if (deque_size == array_capacity)
	{
		//Double the size of the array.

		//Create a copy of Array
		Type * Previous_Array = Array;
		//Increase create a new Array size by 2
		Array = new Type[array_capacity * 2];
		//Create a temp ifront
		int temp_ifront = ifront;

		for (int i = 0; i <= deque_size; i++)
		{
			//reassign Array with original values in order
			Array[i] = Previous_Array[temp_ifront];

			//If iback is in the last index, set iback to first index for wrap around
			if (temp_ifront == array_capacity)
			{
				temp_ifront = 0;
			}
			else
			{
				temp_ifront++;
			}
		}
		//set the proper indexes after
		ifront = 0;
		iback = deque_size;
		array_capacity = array_capacity*2;
		delete [] Previous_Array;
		
	}

	if (deque_size == 0)
	{
		ifront = iback = 0;
	}
	else if (ifront == 0)
	{
		//If ifront is in the first index, set ifront to last index for wrap around
		ifront = array_capacity - 1;
	}
	else
	{
		//Otherwise decrement the ifront index in the counter-clockwise direction
		ifront--;
	}

	Array[ifront] = obj;
	deque_size++;
}

template <typename Type>
void Resizable_deque<Type>::push_back(Type const &obj) {
	// Enter your implementation here
	if (deque_size == array_capacity)
	{
		//Double the size of the array.

		//Create a copy of Array
		Type * Previous_Array = Array;
		//Increase create a new Array size by 2
		Array = new Type[array_capacity * 2];
		//Create a temp ifront
		int temp_ifront = ifront;

		for (int i = 0; i <= deque_size; i++)
		{
			//reassign Array with original values in order
			Array[i] = Previous_Array[temp_ifront];

			//If iback is in the last index, set iback to first index for wrap around
			if (temp_ifront == array_capacity)
			{
				temp_ifront = 0;
			}
			else
			{
				temp_ifront++;
			}
		}
		//set the proper indexes after
		ifront = 0;
		iback = deque_size;
		array_capacity = array_capacity*2;
		delete [] Previous_Array;
	}

	if (deque_size == 0)
	{
		ifront = iback = 0;
	}
	else if ( iback == (array_capacity - 1) )
	{
		//If iback is in the last index, set iback to first index for wrap around
		iback = 0;
	}
	else
	{
		//Otherwise increment the iback index in the clockwise direction
		iback++;
	}

	Array[iback] = obj;
	deque_size++;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here

	if (deque_size == 0)
	{
		//If there are no items in the array, throw an exception
		throw underflow();
	}
	else
	{
		if (ifront == (array_capacity - 1))
		{
			//If the item being deleted is in the max index, set ifront to 0 in order to counter the wrap around
			ifront = 0;
		}
		else
		{
			ifront++;
		}

		deque_size--;
	}

	if ( (deque_size == (array_capacity / 4)) && (array_capacity > initial_array_capacity) )
	{
		//Half the size of the Array

		//Create a copy of Array
		Type * Previous_Array = Array;
		//Increase create a new Array size / 2
		Array = new Type[array_capacity/2];
		//Create a temp ifront
		int temp_ifront = ifront;

		for (int i = 0; i <= deque_size; i++)
		{
			//reassign Array with original values in order
			Array[i] = Previous_Array[temp_ifront];

			//If iback is in the last index, set iback to first index for wrap around
			if (temp_ifront == array_capacity)
			{
				temp_ifront = 0;
			}
			else
			{
				temp_ifront++;
			}
		}
		//set the proper indexes after
		ifront = 0;
		iback = deque_size;
		array_capacity = array_capacity / 2;
		delete [] Previous_Array;
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
	if (deque_size == 0)
	{
		//If there are no items in the array, throw an exception
		throw underflow();
	}
	else
	{
		if (iback == 0)
		{
		//If the item being deleted is in the min index, set iback to max in order to counter the wrap around
		iback = array_capacity - 1;
		}
		else
		{
			iback--;
		}

		deque_size--;
	}

	if ((deque_size == (array_capacity / 4)) && (array_capacity > initial_array_capacity))
	{
		//Half the size of the Array

		//Create a copy of Array
		Type * Previous_Array = Array;
		//Increase create a new Array size / 2
		Array = new Type[array_capacity/2];
		//Create a temp ifront
		int temp_ifront = ifront;

		for (int i = 0; i <= deque_size; i++)
		{
			//reassign Array with original values in order
			Array[i] = Previous_Array[temp_ifront];

			//If iback is in the last index, set iback to first index for wrap around
			if (temp_ifront == array_capacity)
			{
				temp_ifront = 0;
			}
			else
			{
				temp_ifront++;
			}
		}
		//set the proper indexes after
		ifront = 0;
		iback = deque_size;
		array_capacity = array_capacity / 2;
		delete [] Previous_Array;
	}
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
	delete [] Array;
	array_capacity = initial_array_capacity;
	Array = new Type[array_capacity];
	ifront = 0;
	iback = 0;
	deque_size = 0;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	
	int temp_ifront = list.ifront;

	//Iterate through all of the original Array. Regardless of the placement of ifront,
	//Set the new array with ifront at position 0.
	for (int i = 0; i < list.deque_size; i++)
	{
		if (temp_ifront == list.array_capacity)
		{

			std::cout << "--" << list.Array[temp_ifront];
			temp_ifront = 0;
		}
		else
		{
			std::cout << "--" << list.Array[temp_ifront];
			temp_ifront++;
		}
	}

	return out;
}

#endif
