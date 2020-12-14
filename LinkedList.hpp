#pragma once
#include <stdio.h>
#include "Exception.hpp"

template <class T>

struct ListNode
{
	T data;
	ListNode* next;
};

template <class T>
class LinkedList
{
public:
	int length;
	struct ListNode<T>* link;
public:
	LinkedList(T value)
	{
		this->length = 1;
		this->link = new ListNode<T>();
		this->link->data = value;
		this->link->next = NULL;
	}
	LinkedList(ListNode<T>* list)
	{
		this->link = list;
		int count = 1;
		ListNode<T>* i = list;
		while (i->next != nullptr)
		{
			i = i->next;
			count++;
		}
		this->length = count;
	}
	LinkedList(T* items, int count)
	{
		if (count <= 0)
			throw new Exception;
		if (count != 0)
		{
			this->link->data = items[0];
			for (int i = 1; i < count; i++)
			{
				struct ListNode<T>* list = new ListNode<T>;
				list->data = items[i];
				list->next = NULL;
				this->link->next = list;
			}
		}
		this->length = count;
	}
	LinkedList()
	{
		this->link = NULL;
		this->length = 0;
	}
	/*LinkedList(const LinkedList <T>& list)
	{
		this->link = list.link;
		this->length = list.length;
	}*/
	LinkedList(LinkedList<T>* list)
	{
		this->link = list->link;
		this->length = list->length;
	}
public:
	T GetFirst()
	{
		return this->link->data;
	}
	T GetLast()
	{
		if (this->length == 0)
			throw new Exception;
		struct ListNode<T>* l = this->link;
		while (l->next != NULL)
			l = l->next;
		return l->data;
	}
	T Get(int index)
	{
		if (index < 0)
			throw new Exception;
		//if ()
		ListNode<T>* l = this->link;
		for (int i = 0; i < index; i++)
			l = l->next;
		return l->data;
	}
	int GetLength()
	{
		return this->length;
	}
	void append(T item)
	{
		int k = this->length;
		this->length = k + 1;
		ListNode<T>* l = new ListNode<T>;
		l->data = item;
		l->next = this->link;
		this->link = l;
	}
	void prepend(T item)
	{
		int k = this->length;
		this->length = k + 1;
		ListNode<T>* l = new ListNode<T>;
		struct ListNode<T>* l1;
		l->data = item;
		l->next = NULL;
		if (this->link == NULL)
			this->link = l;
		else
		{
			l1 = this->link;
			while (l1->next != NULL)
				l1 = l1->next;
			l1->next = l;
		}
	}
	void insert(T item, int index)
	{
		if ((index < 0) || (index > this->GetLength()))
			throw new Exception;
		ListNode<T>* l = new ListNode<T>;
		l = this->link;
		for (int i = 0; i < index; i++)
			l = l->next;
		l->data = item;
		//this->length++;
	}
	void DeleteByIndex(int index)
	{
		if (index == 0)
		{
			this->link = this->link->next;
			this->length--;
		}
		else
		{
			ListNode<T>* l = this->link;
			ListNode<T>* l1 = new ListNode<T>;
			for (int i = 0; i < index - 1; i++)
				l = l->next;
			l1 = l->next;
			if (l->next != NULL)
				l->next = l->next->next;
			else
				l->next = NULL;
			delete l1;
			this->length--;
		}
	}
	LinkedList<T>* Concat(LinkedList<T>* list)
	{
		ListNode<T>* res = this->link;
		ListNode<T>* a = this->link;
		while (a->next != 0)
			a = a->next;
		a->next = list->link;
		return new LinkedList<T>(res);
	}
	LinkedList<T>* PreConcat(LinkedList<T>* list)
	{
		ListNode<T>* res = list->link;
		ListNode<T>* a = list->link;
		while (a->next != nullptr) 
			a = a->next;
		a->next = this->link;
		LinkedList<T>* reslist = new LinkedList<T>(res);
		return reslist;
	}
	LinkedList<T>* GetSubList(int startindex, int endindex)
	{
		if ((startindex < 0) || (endindex > this->GetLength()) || (startindex > endindex)) 
			throw new Exception;
		struct ListNode<T>* l = this->link;
		for (int i = 0; i < startindex; i++)
			l = l->next;
		LinkedList<T>* res = new LinkedList(l->data);
		for (int i = startindex; i < endindex; i++)
		{
			l = l->next;
			res->prepend(l->data);
		}
	}
};