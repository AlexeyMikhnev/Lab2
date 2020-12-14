#pragma once
#include "DynamicArray.hpp"
#include "Sequence.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T>* arr;
public:
	ArraySequence(T* items, int count)
	{
		this->arr = new DynamicArray<T>(items, count);
	}
	ArraySequence()
	{
		this->arr = new DynamicArray<T>(0);
	}
	/*ArraySequence(ArraySequence<T>* seq)
	{
		this->arr = new DynamicArray<T>(seq->arr);
	}*/

	T GetFirst()
	{
		return this->arr->get(0);
	}
	T GetLast()
	{
		return this->arr->get(this->arr->GetSize() - 1);
	}
	T Get(int index)
	{
		return this->arr->get(index);
	}
	/*ArraySequence<T>* GetSubSequence(int startindex, int endindex)
	{
		ArraySequence<T>* res = new ArraySequence<T>();
		res->arr = new DynamicArray<T>(endindex - startindex + 1);
		for (int i = startindex; i <= endindex; i++)
		{
			res->arr->set(i, this->Get(i));
		}
		return res;
	}*/
	int GetLength()
	{
		return this->arr->GetSize();
	}
	void InsertAt(T item, int index)
	{
		this->arr->set(index, item);
		/*DynamicArray<T>* res = new DynamicArray<T>(this->GetLength() + 1);
		for (int i = 0; i < this->GetLength() + 1; i++)
			if (i < index)
				res->set(i, this->arr->get(i));
			else
				if (i == index)
					res->set(i, item);
				else res->set(i, this->arr->get(i - 1));
		this->arr = res;*/
	}
	void Append(T item)
	{
		int index = 0;
		DynamicArray<T>* res = new DynamicArray<T>(this->GetLength() + 1);
		for (int i = 0; i < this->GetLength() + 1; i++)
			if (i < index)
				res->set(i, this->arr->get(i));
			else
				if (i == index)
					res->set(i, item);
				else res->set(i, this->arr->get(i - 1));
		this->arr = res;
	}
	void Prepend(T item)
	{
		int index = this->GetLength();
		DynamicArray<T>* res = new DynamicArray<T>(this->GetLength() + 1);
		for (int i = 0; i < this->GetLength() + 1; i++)
			if (i < index)
				res->set(i, this->arr->get(i));
			else
				if (i == index)
					res->set(i, item);
				else res->set(i, this->arr->get(i - 1));
		this->arr = res;
	}
	void DeleteByIndex(int index)
	{
		int n = this->arr->GetSize();
		for (int i = index; i < n; i++)
		{
			this->arr[i] = this->arr[i + 1];
		}
		this->arr->resize(n-1);
	}
	ArraySequence<T>* Concat(ArraySequence<T>* list)
	{
		int size = this->GetLength() + list->GetLength() - 1;
		T* res = new T[size];
		for (int i = 0; i < size; i++)
		{
			if (i < this->GetLength())
				res[i] = this->Get(i);
			if (i >= this->GetLength())
				res[i] = list->Get(i + this->GetLength());
		}
		ArraySequence* resseq = new ArraySequence<T>(res, size);
		return resseq;
	}
};