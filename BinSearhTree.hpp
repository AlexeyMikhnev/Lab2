#pragma once
#include "Sequence.hpp"
#include "Compare.hpp"
#include "LinkedList.hpp"
#include <string.h>

template <class T>
class BinSearchTreeNode
{
public:
	BinSearchTreeNode<T>* Left;
	BinSearchTreeNode<T>* Right;
	BinSearchTreeNode<T>* Root;
	T Key;
	int Level;
	BinSearchTreeNode* InsertionNext;
public:
	BinSearchTreeNode(T item)
	{
		this->Key = item;
		this->Left = nullptr;
		this->Right = nullptr;
		this->Root = nullptr;
		this->Level = 1;
		this->InsertionNext = NULL;
	}
	BinSearchTreeNode(T item, BinSearchTreeNode* root, int rootlvl)
	{
		this->Key = item;
		this->Left = nullptr;
		this->Right = nullptr;
		this->Root = root;
		this->Level = rootlvl + 1;
		this->InsertionNext = NULL;
	}
	BinSearchTreeNode(T* items, int length)
	{
		BinSearchTreeNode(items[0], nullptr, 0);
		for (int i = 1; i < length; i++)
			this->Add(items[i]);
	}
	BinSearchTreeNode(Sequence<T> seq)
	{
		int length = seq->GetLength();
		this->Left = nullptr;
		this->Right = nullptr;
		this->Key = seq->GetFirst();
		this->Root = nullptr;
		this->Level = 1;
		for (int i = 1; i < length; i++)
		{
			this->Add(seq->Get(i));
		}
	}
	BinSearchTreeNode(BinSearchTreeNode<T>* tree)
	{
		//this = new BinSearchTreeNode(tree->Key, tree->Root, tree->Level);
		this->Key = tree->Key;
		this->Root = tree->Root;
		this->Level = tree->Level;
		this->InsertionNext = NULL;
		if (tree->Left!=nullptr) 
			this->Left = new BinSearchTreeNode(tree->Left);
		if (tree->Right!=nullptr) 
			this->Right = new BinSearchTreeNode(tree->Right);
	}
	void Add(T item)
	{
		if ((IsLesser(item, this->Key)) & (this->Left == nullptr))
		{
			this->Left = new BinSearchTreeNode<T>(item, this, this->Level);
		}
		else if ((IsLesser(this->Key, item)) & (this->Right == nullptr))
		{
			this->Right = new BinSearchTreeNode<T>(item, this, this->Level);
		}
		else if (IsLesser(item, this->Key))
			this->Left->Add(item);
		else if (IsLesser(this->Key, item))
			this->Right->Add(item);
	}
	int GetLength()
	{
		if ((this->Left == nullptr) & (this->Right == nullptr)) return 1;
		if (this->Left == nullptr) return this->Right->GetLength() + 1;
		if (this->Right == nullptr) return this->Left->GetLength() + 1;
		int LeftLength = this->Left->GetLength();
		int RightLength = this->Right->GetLength();
		if (LeftLength > RightLength) 
			return LeftLength + 1;
		else
			return RightLength + 1;
	}
	BinSearchTreeNode<T>* find(T item)
	{
		if (item == this->Key) return this;
		if ((this->Left == nullptr) & (this->Right == nullptr)) return nullptr;
		if (this->Left == nullptr) return this->Right->find(item);
		if (this->Right == nullptr) return this->Left->find(item);
		if (IsLesser(item, this->Key)) return this->Left->find(item);
		if (IsLesser(this->Key, item)) return this->Right->find(item);
	}
	void LessLevel()
	{
		this->Level--;
		if (this->Left != nullptr) this->Left->LessLevel();
		if (this->Right != nullptr) this->Right->LessLevel();
	}
	void DeleteItem()
	{
		if ((this->Left == nullptr) & (this->Right == nullptr))
		{
			if (this->Root == nullptr) delete this;
			if (this == this->Root->Left) this->Root->Left = nullptr;
			if (this == this->Root->Right) this->Root->Right = nullptr;
			delete this;
		}
		else
		if (this->Left == nullptr)
		{
			if (this == this->Root->Left) this->Root->Left = this->Right;
			if (this == this->Root->Right) this->Root->Right = this->Right;
			this->Right->Root = this->Root;
			this->Right->LessLevel();
			delete this;
		}
		else
		if (this->Right == nullptr)
		{
			if (this == this->Root->Left) this->Root->Left = this->Left;
			if (this == this->Root->Right) this->Root->Right = this->Left;
			this->Right->Root = this->Root;
			this->Right->LessLevel();
			delete this;
		}
		else
		{
			BinSearchTreeNode<T>* node = this->Right;
			while (node->Left != nullptr)
				node = node->Left;
			this->Key = node->Key;
			node->DeleteItem();
		}
	}
	int diff()
	{
		if (this == nullptr) return 0;
		if ((this->Left == nullptr) & (this->Right == nullptr)) return 0;
		if (this->Left == nullptr) return -this->Right->GetLength();
		if (this->Right == nullptr) return this->Left->GetLength();
		return this->Left->GetLength() - this->Right->GetLength();
	}
	void Balance()
	{
		if (((this->diff() == -2) & (this->Right->diff() == -1)) || ((this->diff() == -2) & (this->Right->diff() == 0)))
		{
			BinSearchTreeNode<T>* node = new BinSearchTreeNode(this->Right);
			this->Right = node->Left;
			node->Left = this;
		}
		if (((this->diff() == 2) & (this->Left->diff() == 1)) || ((this->diff() == 2) & (this->Left->diff() == 0)))
		{
			BinSearchTreeNode<T>* node = new BinSearchTreeNode(this->Left);
			this->Left = node->Right;
			node->Right = this;
		}
		if ((this->diff() == 2) & (this->Right->diff() == 1) & (this->Right->Left->diff() * this->Right->Left->diff() < 1))
		{
			BinSearchTreeNode<T>* node = new BinSearchTreeNode(this->Right->Left);
			this->Right->Left = node->Right->Right;
			node->Right->Right = this;

			BinSearchTreeNode<T>* node1 = new BinSearchTreeNode(this->Right);
			this->Right = node1->Left;
			node1->Left = this;
		}
		if ((this->diff() == -2) & (this->Left->diff() == -1) & (this->Left->Right->diff() * this->Left->Right->diff() < 1))
		{
			BinSearchTreeNode<T>* node = new BinSearchTreeNode(this->Left->Right);
			this->Left->Right = node->Left->Left;
			node->Left->Left = this;

			BinSearchTreeNode<T>* node1 = new BinSearchTreeNode(this->Left);
			this->Left = node1->Right;
			node1->Right = this;
		}

	}
	int GetAmountOfElements()
	{
		int res = 1;
		if (this->Left != nullptr) res += this->Left->GetAmountOfElements();
		if (this->Right != nullptr) res += this->Right->GetAmountOfElements();
		return res;
	}

	//String segment
	LinkedList<T>* SaveAsString(char* par)
	{
		if ((par[0] == 'k') & (par[1] == 'l') & (par[2] == 'r'))
			return this->klr_s();
		if ((par[0] == 'k') & (par[1] == 'r') & (par[2] == 'l'))
			return this->krl_s();
		if ((par[0] == 'l') & (par[1] == 'r') & (par[2] == 'k'))
			return this->lrk_s();
		if ((par[0] == 'r') & (par[1] == 'l') & (par[2] == 'k'))
			return this->rlk_s();
		if ((par[0] == 'l') & (par[1] == 'k') & (par[2] == 'r'))
			return this->lkr_s();
		if ((par[0] == 'r') & (par[1] == 'k') & (par[2] == 'l'))
			return this->rkl_s();
	}
	LinkedList<T>* klr_s()
	{
		LinkedList<T>* list = new LinkedList<T>(this->Key);
		if (this->Left != nullptr) 
			list = list->Concat(this->Left->klr_s());
		if (this->Right != nullptr) 
			list = list->Concat(this->Right->klr_s());
		return list;
	}
	LinkedList<T>* krl_s()
	{
		LinkedList<T>* list = new LinkedList<T>(this->Key);
		if (this->Left != nullptr) 
			list = list->Concat(this->Right->klr_s());
		if (this->Right != nullptr) 
			list = list->Concat(this->Left->klr_s());
		return list;
	}
	LinkedList<T>* lrk_s()
	{
		LinkedList<T>* list = new LinkedList<T>(this->Key);
		if (this->Right != nullptr) 
			list = list->PreConcat(this->Right->lrk_s());
		if (this->Left != nullptr) 
			list = list->PreConcat(this->Left->lrk_s());
		return list;
	}
	LinkedList<T>* rlk_s()
	{
		LinkedList<T>* list = new LinkedList<T>(this->Key);
		if (this->Left != nullptr)
			list = list->PreConcat(this->Left->rlk_s());
		if (this->Right != nullptr) 
			list = list->PreConcat(this->Right->rlk_s());
		return list;
	}
	LinkedList<T>* lkr_s()
	{
		LinkedList<T>* list = new LinkedList<T>(this->Key);
		if (this->Left != nullptr)
			list = list->PreConcat(this->Left->lkr_s());
		if (this->Right != nullptr) 
			list = list->Concat(this->Right->lkr_s());
		return list;
	}
	LinkedList<T>* rkl_s()
	{
		LinkedList<T>* list = new LinkedList<T>(this->Key);
		if (this->Left != nullptr) 
			list = list->Concat(this->Left->rkl_s());
		if (this->Right != nullptr) 
			list = list->PreConcat(this->Right->rkl_s());
		return list;
	}

	//Insertion segment
	void Insertion(char* par)
	{
		LinkedList<T>* list = new LinkedList<T>(this->SaveAsString(par));
		int len = list->GetLength();
		for (int i = 0; i < len-1; i++)
		{
			this->find(list->Get(i))->InsertionNext = this->find(list->Get(i+1));
		}
		this->find(list->Get(len-1))->InsertionNext = nullptr;
	}

	BinSearchTreeNode<T>* GetSubTree(BinSearchTreeNode<T>* root)
	{
		BinSearchTreeNode<T>* res = new BinSearchTreeNode<T>(root);
		res->root = nullptr;
	}

	bool equal(BinSearchTreeNode<T>* tree1, BinSearchTreeNode<T>* tree2)
	{
		if (((tree1 == nullptr) && (tree2 != nullptr)) || ((tree1 != nullptr) && (tree2 == nullptr))) return false;
		if (tree1->Key != tree2->Key) return false;
		return equal(tree1->Right, tree2->Right) * equal(tree1->Left, tree2->Left);
	}
	BinSearchTreeNode<T>* SearchCopy(BinSearchTreeNode<T>* tree)
	{
		if (equal(this->find(tree->Key), tree))
			return this->find(tree->Key);
		else return nullptr;
	}

	void Transform()
	{
		this->Key++;
	}
	BinSearchTreeNode<T>* map()
	{
		BinSearchTreeNode<T>* res = new BinSearchTreeNode<T>(this);
		res->Transform();
		if (res->Left!=nullptr) 
			res->Left = res->Left->map();
		if (res->Right != nullptr)
			res->Right = res->Right->map();
		return res;
	}
	bool Quality()
	{
		if (this->Right = NULL) return true;
		return IsLesser(this->Key, this->Right->Key);
	}
	BinSearchTreeNode<T>* where()
	{
		BinSearchTreeNode<T>* res = new BinSearchTreeNode<T>(this);
		if (!this->Quality()) this->DeleteItem();
		if (res->Left != nullptr)
			res->Left = res->Left->where();
		if (res->Right != nullptr)
			res->Right = res->Right->where();
		return res;
	}
	T reduce()
	{
		char* c = new char[3];
		c[0] = 'l';
		c[1] = 'k';
		c[2] = 'r';
		this->Insertion(c);
		BinSearchTreeNode<T>* node = new BinSearchTreeNode<T>(this);
		while (node->Left != NULL)
			node = node->Left;
		T res = 0;
		while (node->InsertionNext != NULL)
		{
			res += node->Key;
			node = node->InsertionNext;
		}
		return res;
	}
};

template <class T>
class BinSearchTree
{
public:
	BinSearchTreeNode<T>* Tree;
	int Length;
public:
	BinSearchTree(T item)
	{
		this->Tree = new BinSearchTreeNode<T>(item);
		this->Length = 1;
	}
	BinSearchTree(BinSearchTreeNode<T>* tree)
	{
		this->Tree = tree;
		this->Length = tree->GetLength();
	}
	void Add(T item)
	{
		this->Tree->Add(item);
	}
	BinSearchTree(Sequence<T> seq)
	{
		this->Tree = new BinSearchTreeNode<T>(seq);
		this->Length = this->Tree->GetLength();
	}
	BinSearchTree(T* items, int length)
	{
		this->Tree = new BinSearchTreeNode<T>(items, length);
		this->Length = this->Tree->GetLength();
	}
	bool find(T item)
	{
		return (this->Tree->find(item)!=nullptr);
	}
	LinkedList<T>* SaveAsString(char* par)
	{
		return this->Tree->SaveAsString(par);
	}
	void Balance()
	{
		this->Tree->Balance();
		this->Length = this->Tree->GetLength();
	}
	void Insertion(char* par)
	{
		this->Tree->Insertion(par);
	}
	BinSearchTreeNode<T>* GetSubTree(BinSearchTreeNode<T>* root)
	{
		return this->Tree->GetSubTree(root);
	}
	BinSearchTree<T>* SearchCopy(BinSearchTreeNode<T>* tree)
	{
		return this->Tree->SearchCopy(tree);
	}
	BinSearchTree<T>* map()
	{
		BinSearchTree<T>* res = new BinSearchTree<T>(this->Tree->map());
		return res;
	}
	BinSearchTree<T>* where()
	{
		BinSearchTree<T>* res = new BinSearchTree<T>(this->Tree->where());
		return res;
	}
	BinSearchTree<T>* reduce()
	{
		BinSearchTree<T>* res = new BinSearchTree<T>(this->Tree->reduce());
		return res;
	}

	int GetAmountOfElements()
	{
		return this->Tree->GetAmountOfElements();
	}
};
