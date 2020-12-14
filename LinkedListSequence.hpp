#pragma once
#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T>
class LinkedListSequence : public Sequence<T>
{
private:
	LinkedList<T> list;
public:
	LinkedListSequence(T* items, int count)
	{
		this->list = LinkedList<T>(items, count);
	}
	LinkedListSequence()
	{
		this->list = LinkedList<T>();
	}
	LinkedListSequence(LinkedListSequence<T>& list)
	{
		this->list = list->list;
	}
	LinkedListSequence(LinkedList<T>& list)
	{
		this->list = list;
	}
	T Get(int index)
	{
		return this->list.Get(index);
	}
	T GetFirst()
	{
		return this->list.GetFirst();
	}
	T GetLast()
	{
		return this->list.GetLast();
	}
	LinkedListSequence<T> GetSubSequence(int startindex, int endindex)
	{
		LinkedList<T> res = this->list->GetSubList(startindex, endindex);
		LinkedListSequence<T> resseq = LinkedListSequence(res);
		return resseq;
	}
	int GetLength()
	{
		return this->list.GetLength();
	}
	
	void Append(T item)
	{
		this->list.append(item);
	}
	void Prepend(T item)
	{
		this->list.prepend(item);
	}
	void InsertAt(T item, int index)
	{
		this->list.insert(item, index);
	}
	LinkedListSequence<T>* Concat(LinkedListSequence<T>* list)
	{
		this->list->Concat(list->list);
	}
	void DeleteByIndex(int index)
	{
		this->list.DeleteByIndex(index);
	}
	bool IsEmpty()
	{
		return (this->list->length == 0);
	}
};