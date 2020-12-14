#pragma once
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include "Compare.hpp"


template <class T>
class Sequence
{
public:
    virtual ~Sequence<T>() {};
    virtual T GetFirst() { return 0; };
    virtual T GetLast() { return 0; };
    virtual T Get(int index) { return 0; };
    virtual int GetLength() { return 0; };
    //virtual Sequence<T>* GetSubSequence(int startindex, int endindex) {};
    virtual void Append(T item) {};
    virtual void Prepend(T item) {};
    virtual void InsertAt(T item, int index) {};
    virtual void DeleteByIndex(int index) {};
    //virtual Sequence<T>* Concat(Sequence<T>* list) const = 0;
    void swap(int a, int b)
    {
        T temp;
        temp = this->Get(a);
        this->InsertAt(this->Get(b), a);
        this->InsertAt(temp, b);
    }
    void QuickSort()
    {
        this->QuickSort(0, this->GetLength());
    }
    void QuickSort(int first, int last)
    {
        if (first != last)
        {
            int left = first;
            int right = last;
            int pivot = left++;

            while (left != right)
            {
                if (compare(this->Get(left), this->Get(pivot)))
                    ++left;
                else
                {
                    while ((left != --right) && (compare(this->Get(pivot), this->Get(right))));
                    this->swap(left, right);
                }
            }

            --left;
            this->swap(first, left);
            this->QuickSort(first, left);
            this->QuickSort(right, last);

        }
    }
    void ShellSort()
    {
        long inc, i, j, seq[40];
        int s;

        // s = increment(seq, this->GetLength());
        int p1, p2, p3;

        p1 = p2 = p3 = 1;
        s = -1;
        do {
            if (++s % 2) {
                seq[s] = 8 * p1 - 6 * p2 + 1;
            }
            else {
                seq[s] = 9 * p1 - 9 * p3 + 1;
                p2 *= 2;
                p3 *= 2;
            }
            p1 *= 2;
        } while (3 * seq[s] < this->GetLength());


        while (s >= 0)
        {
            inc = seq[s--];
            for (i = inc; i < this->GetLength(); i++)
            {
                T temp = this->Get(i);
                for (j = i - inc; (j >= 0) && (!compare(this->Get(j), temp)); j -= inc)
                    this->InsertAt(this->Get(j), j + inc);
                this->InsertAt(temp, j + inc);
            }
        }
    }
    void PyramidSort()
    {
        int N = this->GetLength();
        for (int j = 0; j < N; j++)
        {
            for (int i = N / 2 - 1 - j / 2; i > -1; i--)
            {
                if (2 * i + 2 <= N - 1 - j)
                {
                    if (!compare(this->Get(2 * i + 1), this->Get(2 * i + 2)))
                    {
                        if (compare(this->Get(i), this->Get(2 * i + 1)))
                        {
                            this->swap(i, 2 * i + 1);
                        }
                    }
                    else
                        if (compare(this->Get(i), this->Get(2 * i + 2)))
                        {
                            this->swap(i, 2 * i + 2);
                        }
                }
                else
                    if (2 * i + 1 <= N - 1 - j)
                        if (compare(this->Get(i), this->Get(2 * i + 1)))
                            this->swap(i, 2 * i + 1);
            }
            this->swap(0, N - 1 - j);
        }
    }

    void DeleteByCriteria(bool (*criteria)(T))
    {
        int n = this->GetLength();
        for (int i = 0; i < n; i++)
            if (criteria(this->Get(i)))
            {
                this->DeleteByIndex(i);
                i--;
                n--;
            }
    }
};