#pragma once
#include "Exception.hpp"

template <class T>
class DynamicArray
{
private:
	T* items;
	bool* itemsCheck;
	int size;
public:
	DynamicArray(T* items, int count)
	{
		if (count < 0) 
			throw new Exception;
		this->items = items;
		this->size = count;
		this->itemsCheck = new bool[count];
		for (int i = 0; i < count; i++)
			this->itemsCheck[i] = false;
	}
	DynamicArray(const int size)
	{
		if (size < 0) throw new Exception;
		if (size < 0) 
			throw new Exception;
		this->items = new T[size];
		this->itemsCheck = new bool[size];
		for (int i = 0; i < size; i++)
			this->itemsCheck[i] = false;
		this->size = size;
	}
	/*DynamicArray(const DynamicArray<T>& array)
	{
		this->size = array->size;
		this->items = array->items;
		this->itemsCheck = array->itemsCheck;
	}*/
	int GetSize() const { return this->size; }
	T get(const int index) const
	{
		if ((index < 0) || (index >= this->size))
		{
			throw new Exception;
			
		}
		/*if (index<0 || index>this->size || !this->itemsCheck[index])
			throw new Exception; */
		return this->items[index];
	}	
	void set(const int index, const T value)
	{
		if (!((index >= 0) && (index < this->size))) throw new Exception;
		if (index < 0 || index >= this->size)
			throw new Exception;
		this->itemsCheck[index] = true;
		this->items[index] = value;
	}
	void resize(int newsize)
	{
		if (newsize < 0) throw new Exception;
		T* newitems = new T[newsize];
		bool *newitemscheck = new bool[newsize];
		if (newsize < size)
			for (int i = 0; i < newsize; i++)
			{
				newitems[i] = this->items[i];
				newitemscheck[i] = this->itemsCheck[i];
			}
		if (newsize >= size)
		{
			for (int i = 0; i < size; i++)
			{
				newitems[i] = this->items[i];
				newitemscheck[i] = this->itemsCheck[i];
			}
			for (int i = size; i < newsize; i++)
				newitemscheck[i] = false;
		}
		delete this->items;
		delete this->itemsCheck;
		this->size = newsize;
		this->items = newitems;
		this->itemsCheck = newitemscheck;
	}
};

