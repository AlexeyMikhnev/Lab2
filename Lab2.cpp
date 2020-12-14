#include <iostream>
#include "Sequence.hpp"
#include <cstdlib>
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include <fstream>
#include <string.h>
#include "Compare.hpp"
#include "BinSearhTree.hpp"
#include "ThreeTree.hpp"
#include <cstdio>
#include <ctime>
#include <map>
#include <clocale>
using namespace std;

struct tictactoe {
    char type;
    int i, j;
};


int hashf(string s, string * a1)
{
    int res = 0;
    for (int i = 0; i < s.length(); i++)
    {
        res = res*10 + s[i] - '0';
    }
    while (1)
        if ((a1[res] == "")||(a1[res]==s))
        {
            a1[res] = s;
            return res;
        }
        else
            res++;
}

struct ForeseeTree {
    LinkedList<tictactoe> *points;
    int m, n, amount;
    LinkedList<ForeseeTree> *variants;
};

int count(ForeseeTree *a)
{
    char** composition = new char* [a->m];
    for (int count = 0; count < a->m; count++)
        composition[count] = new char[a->n];//создали массив m*n
    for (int i = 0; i < a->m; i++)
        for (int j = 0; j < a->n; j++)
            composition[i][j] = '-';

    for (int i = 0; i < a->amount; i++)
    {
        char newpoint = a->points->Get(i).type;
        composition[a->points->Get(i).i][a->points->Get(i).j] = newpoint;
    }//заполнили массив

    int res = 0;
    int maxrow = 5;
    //считаем комбинации ноликов
    for (int i = 0; i < a->m; i++)
        for (int j = 0; j < a->n; j++)
            if (composition[i][j] == '0')
            {
                int addscore = 1;
                int k = 1;
                addscore = 1;
                if (i + k < a->m)
                while (composition[i + k][j] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                k = 1;
                addscore = 1;
                if (i - k > 0)
                while (composition[i - k][j] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                k = 1;
                addscore = 1;
                if (j + k < a->n)
                while (composition[i][j + k] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                k = 1;
                addscore = 1;
                if (j - k > 0)
                while (composition[i][j - k] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                k = 1;
                addscore = 1;
                if ((i + k < a->m) && (j + k < a->n))
                while (composition[i + k][j + k] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                k = 1;
                addscore = 1;
                if ((i - k > 0) && (j + k < a->n))
                while (composition[i - k][j + k] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                k = 1;
                addscore = 1;
                if ((i + k < a->m) && (j - k > 0))
                while (composition[i + k][j - k] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
                addscore = 1;
                k = 1;
                if ((i - k > 0) && (j + k < a->n))
                while (composition[i - k][j - k] == '0')
                {
                    addscore *= 10;
                    k++;
                }
                res += addscore;
            }

    //считаем комбинации крестиков
    for (int i = 0; i < a->m; i++)
        for (int j = 0; j < a->n; j++)
            if (composition[i][j] == 'X')
            {
                int addscore = 1;
                int k = 1;
                addscore = 1;
                if (i + k < a->m)
                    while (composition[i + k][j] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                k = 1;
                addscore = 1;
                if (i - k > 0)
                    while (composition[i - k][j] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                k = 1;
                addscore = 1;
                if (j + k < a->n)
                    while (composition[i][j + k] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                k = 1;
                addscore = 1;
                if (j - k > 0)
                    while (composition[i][j - k] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                k = 1;
                addscore = 1;
                if ((i + k < a->m) && (j + k < a->n))
                    while (composition[i + k][j + k] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                k = 1;
                addscore = 1;
                if ((i - k > 0) && (j + k < a->n))
                    while (composition[i - k][j + k] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                k = 1;
                addscore = 1;
                if ((i + k < a->m) && (j - k > 0))
                    while (composition[i + k][j - k] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
                addscore = 1;
                k = 1;
                if ((i - k > 0) && (j + k < a->n))
                    while (composition[i - k][j - k] == 'X')
                    {
                        addscore *= 10;
                        k++;
                    }
                res -= addscore;
            }
    return res;
}

bool compare(ForeseeTree a, ForeseeTree b)
{
    return (count(&a)>count(&b));
}

void ConstructVariants(struct ForeseeTree* tree, char turn)
{
    LinkedList<ForeseeTree> *result = new LinkedList<ForeseeTree>();


    char** composition = new char* [tree->m];
    for (int count = 0; count < tree->m; count++)
        composition[count] = new char[tree->n];//создали массив m*n
    for (int i = 0; i < tree->m; i++)
        for (int j = 0; j < tree->n; j++)
            composition[i][j] = '-';

    for (int i = 0; i < tree->amount; i++)
    {
        char newpoint = tree->points->Get(i).type;
        composition[tree->points->Get(i).i][tree->points->Get(i).j] = newpoint;
    }//разметили массив крестиками и ноликами

    for (int i = 0; i < tree->m; i++)
        for (int j = 0; j < tree->n; j++)
            if (composition[i][j] == '-')
            {
                ForeseeTree newtree;
                newtree.m = tree->m;
                newtree.n = tree->n;
                newtree.amount = tree->amount + 1;
                newtree.points = new LinkedList<tictactoe>(tree->points);

                tictactoe newpoint;
                newpoint.i = i;
                newpoint.j = j;
                newpoint.type = turn;
                newtree.points->prepend(newpoint);

                result->prepend(newtree);
            }//создали список всех возможных следующих ходов
    
    tree->variants = result;
}




struct tictactoe NextTurn(LinkedList<tictactoe>* points, int n)
{
    int imin = points->Get(0).i, imax = points->Get(0).i, jmin = points->Get(0).j, jmax = points->Get(0).j;
    for (int i = 1; i < n; i++)
    {
        if (points->Get(i).i<imin)
            imin = points->Get(i).i;
        if (points->Get(i).i > imax)
            imax = points->Get(i).i;
        if (points->Get(i).j < jmin)
            jmin = points->Get(i).j;
        if (points->Get(i).j > jmax)
            jmax = points->Get(i).j;
    }
    ForeseeTree *tree = new ForeseeTree;
    tree->amount = n;
    tree->m = imax+6;
    tree->n = jmax+6;
    tree->points = points;
    ConstructVariants(tree, '0');//создали все варианты ходов

    int len = tree->variants->GetLength();
    ForeseeTree* BestState = new ForeseeTree[len];
    ForeseeTree IdealState = *tree;
    

    for (int i = 0; i < len; i++)
    {
        ListNode<ForeseeTree>* temp = tree->variants->link;
        ForeseeTree* tree1 = new ForeseeTree;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }
        tree1 = &temp->data;



        ConstructVariants(tree1, 'X');
        int varlen = tree->variants->Get(i).variants->GetLength();
        BestState[i] = tree->variants->Get(i).variants->Get(0);
        for (int j = 0; j < varlen; j++)
        {
            if (compare(BestState[i], tree->variants->Get(i).variants->Get(j)))
                BestState[i] = tree->variants->Get(i).variants->Get(j);
        }
        if (compare(BestState[i], IdealState))
            IdealState = BestState[i];
    }
    return IdealState.points->GetLast();
}

bool funccriteria(int i)
{
    return (i == 0);
}

struct complex {
    double r;
    double i;
};

void testsequence()
{
    Sequence<int>* a = new ArraySequence<int>();
    a->Append(1);
    a->Prepend(2);
    //printf("%i%i \n", a->GetFirst(), a->GetLast());
    //printf("%i %i \n", a->Get(0), a->Get(1));
    int k = 2;
    Sequence<int>* b = new LinkedListSequence<int>();
    b->Append(1);
    b->Prepend(2);
    printf("%i %i \n", b->GetFirst(), b->GetLast());
    printf("%i %i \n", b->Get(0), b->GetLength());
    if ((a->GetFirst() == 1) && (a->GetLast() == a->Get(1)) && (a->GetLength() == 2))
        printf("ArrayTest completed successfully \n");
    else
        printf("ArrayTest failed \n");
    if ((b->GetFirst() == 1) && (b->GetLast() == b->Get(1)) && (b->GetLength() == 2))
        printf("LinkedListTest completed successfully \n");
    else
        printf("LinkedListTest failed \n");
    delete b;
    delete a;
}

void testsort(int param)
{
    Sequence<int>* a;
    if (param == 1)
        a = new LinkedListSequence<int>();
    else
        a = new ArraySequence<int>();
    bool criteria = 1;
    int k=0;
    int t = 0;
    std::clock_t start;
    double duration;

    int length = 0;
    printf("Input 1 to generate sequence randomly\n2 to generate sequence manually\n3 to generate template sequence\n");
    scanf_s("%i", &k);
    printf("Input length\n");
    scanf_s("%i", &length);
    if (k == 1)
        for (int i = 0; i < length; i++)
            a->Prepend(rand() % 200 - 100);
    if (k == 2)
        for (int i = 0; i < length; i++)
        {
            int x=0;
            scanf_s("%i", &x);
            a->Prepend(x);
        }
    if (k==3)
        for (int i = 0; i < length; i++)
        {
            int x;
            if (i % 2 == 0)
                x = i;
            else
                x = -i;
            a->Prepend(x);
        }

    while (t != 6)
    {
        printf("Input\n1 to generate new sequence\n2 to QuickSort sequence\n3 to ShellSort sequence\n4 to PyramidSort sequence\n5 to print sequence\n6 to finish\n7 to delete all zeros\n");
        scanf_s("%i", &t);
        if (t == 1)
        {
            delete a;
            if (param == 1)
                a = new LinkedListSequence<int>();
            else
                a = new ArraySequence<int>();
            printf("Input 1 to generate sequence randomly\n2 to generate sequence manually\n3 to generate template sequence\n");
            scanf_s("%i", &k);
            printf("Input length\n");
            scanf_s("%i", &length);
            if (k == 1)
                for (int i = 0; i < length; i++)
                    a->Prepend(rand() % 200 - 100);
            if (k == 2)
                for (int i = 0; i < length; i++)
                {
                    int x=0;
                    scanf_s("%i", &x);
                    a->Prepend(x);
                }
            if (k == 3)
                for (int i = 0; i < length; i++)
                {
                    int x;
                    if (i % 2 == 0)
                        x = i;
                    else
                        x = -i;
                    a->Prepend(x);
                }
        }
        if (t == 2)
        {
            start = std::clock();
            
            a->QuickSort();

            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            std::cout << "Operation took " << duration << "seconds" << std::endl;
        }
        if (t == 3)
        {
            start = std::clock();

            a->ShellSort();

            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            std::cout << "Operation took " << duration << "seconds" << std::endl;
        }
        if (t == 4)
        {
            start = std::clock();

            a->PyramidSort();

            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            std::cout << "Operation took " << duration << "seconds" << std::endl;
        }
        if (t == 5)
        {
            for (int i = 0; i < length; i++)
                printf("%i ", a->Get(i));
            printf("\n");
        }
        if (t == 7)
        {
            a->DeleteByCriteria(funccriteria);
            length--;
        }
    }


}

void SortInterface()
{
    bool c = 1;
    while (c)
    {
        int a = 0;
        printf("Input \n0 to work with array-based sequences\n1 to work with list-based sequences\n2 to finish work\n");
        scanf_s("%i", &a);
        if (a == 0)
            testsort(a);
        if (a == 1)
            testsort(a);
        if (a == 2)
            break;

    }

}

void TestBinaryTree()
{
    bool count = true;
    int n = 2000;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }
    BinSearchTree<int>* tree = new BinSearchTree<int>(arr, n);
    char* par = new char[3];
    par[0] = 'l';
    par[1] = 'k';
    par[2] = 'r';
    //std::cout << tree->GetAmountOfElements() << "\n";
    LinkedList<int>* str = tree->SaveAsString(par);
    int k = str->GetLength();
    tree->Insertion(par);
    for (int i = 1; i < k; i++)
    {
        //std::cout << str->Get(i) << ' ';
        int a = str->Get(i);
        int b = str->Get(i - 1);
        count &= (a > b);
        count &= (tree->Tree->find(b)->InsertionNext == tree->Tree->find(a));
    }

    if (count) printf("Test Successful \n");
    else printf("Test Failed");
}

void TestTriaryTree()
{
    bool count = true;
    for (int i = 0; i < 10; i++)
    {
        int a = rand();
        ThreeTreeNode<int>* tree = new ThreeTreeNode<int>(a);
        //tree->Set(a);
        int b = rand();
        tree->AddLeft(b);
        int c = rand();
        tree->AddMedium(c);
        int d = rand();
        tree->AddRight(d);
        tree->GetMedium()->deletethis();
        count = count * (tree->Get() == a) * (tree->GetLeft()->Get() == b) * (tree->GetRight()->Get() == d);
    }
    if (count) printf("Test Successful \n");
    else printf("Test Failed");
}

void BinaryInterface()
{
    int k = 1;
    while (k)
    {
        std::cout << "Choose our action \n1 to run tests \n2 to input custom tree \n3 to quit\n";
        int c = 0;
        std::cin >> c;
        if (c == 1)
            TestBinaryTree();
        if (c == 3)
            k = 0;
        if (c == 2)
        {
            int item;
            std::cout << "Input first element\n";
            std::cin >> item;
            BinSearchTree<int>* tree = new BinSearchTree<int>(item);
            int q = 1;
            while (q)
            {
                std::cout << "Input \n1 to add element\n2 to check if value is in tree\n3 to show string\n 4 to balance\n 5 to make insertion\n6 to map\n7 to where\n8 to reduce\n9 to exit\n";
                std::cin >> c;
                char* par = new char[3];
                int p = 0;
                LinkedList<int>* str = new LinkedList<int>();
                switch (c)
                {
                case (1):
                    std::cout << "\nInput new element\n";
                    std::cin >> item;
                    tree->Add(item);
                    break;
                case (2):
                    std::cout << "Input item to check\n";
                    std::cin >> item;
                    if (tree->find(item)) std::cout << "Item is here\n";
                    else
                        std::cout << "Item is not here";
                    break;
                case (3):
                    std::cout << "Input parameter of search\n";
                    std::cin >> par[0] >> par[1] >> par[2];
                    str = tree->SaveAsString(par);
                    p = str->GetLength();
                    for (int i = 0; i < p; i++)
                    {
                        std::cout << str->Get(i) << ' ';
                    }
                    break;
                case (4):
                    tree->Balance();
                case (5):
                    tree->Insertion(par);
                    break;
                case (6):
                    tree->map();
                case (7):
                    tree->where();
                case (8):
                    tree->reduce();
                case(9):
                    q = 0;
                }

            }
        }
    }
}

void ThreearyInterface()
{
    int k = 1;
    while (k)
    {
        std::cout << "Choose our action \n1 to run tests \n2 to input custom tree \n3 to quit\n";
        int c = 0;
        std::cin >> c;
        if (c == 1)
            TestTriaryTree();
        if (c == 3)
            k = 0;
        if (c == 2)
        {
            int item;
            std::cout << "Input first element\n";
            std::cin >> item;
            ThreeTreeNode<int>* tree = new ThreeTreeNode<int>(item);
            int q = 1;
            while (q)
            {
                std::cout << "Input \n1 to add element to left\n2 to add element to right\n3 to add element to medium\n4 to check if value is in tree\n5 to print(k123 order)\n6 to exit\n";
                std::cin >> c;
                switch (c)
                {
                case (1):
                    std::cout << "\nInput new element\n";
                    std::cin >> item;
                    tree->AddLeft(item);
                    break;
                case (2):
                    std::cout << "\nInput new element\n";
                    std::cin >> item;
                    tree->AddRight(item);
                    break;
                case (3):
                    std::cout << "\nInput new element\n";
                    std::cin >> item;
                    tree->AddMedium(item);
                    break;
                case (4):
                    std::cout << "\nInput the value\n";
                    std::cin >> item;
                    if (tree->find(item)!=nullptr) std::cout << "Item is here\n";
                    else
                        std::cout << "Item is not here";
                    break;
                case (5):
                    tree->print();
                    break;
                case (6):
                    q = 0;
                    break;
                }
            }
        }
    }
}


void tictactoe_interface()
{
    LinkedList<tictactoe>* points = new LinkedList<tictactoe>();
    tictactoe nextturn;
    int x = 0;
    int y = 0;
    /*cout << "Input coordinates of zeros \n To stop input, type -1 -1";
    cin >> x >> y;
    while (x != -1)
    {
        tictactoe newpoint;
        newpoint.i = x;
        newpoint.j = y;
        newpoint.type = '0';
        points->prepend(newpoint);
        cin >> x >> y;
    }
    cout << "Input coordinates of crosses \n To stop input, type -1 -1";
    cin >> x >> y;
    while (x != -1)
    {
        tictactoe newpoint;
        newpoint.i = x;
        newpoint.j = y;
        newpoint.type = 'X';
        points->prepend(newpoint);
        cin >> x >> y;
    }*/
    tictactoe newpoint;
    newpoint.i = 3;
    newpoint.j = 3;
    newpoint.type = 'X';
    points->prepend(newpoint);
    nextturn = NextTurn(points, points->GetLength());
    cout << "Next turn for zeros is recommended for point " << nextturn.i << ' ' << nextturn.j << '\n';
}

map <string, int*> BuildMap(int size)
{
    map <string, int*> a = {};
    int page = 1;
    int count = 0;
    ifstream fin("text.txt");
    string temp;
    while (fin >> temp)
    {
        count += temp.size() + 1;
        if (temp[0] == '(')
            temp = temp.substr(1, temp.size() - 1);
        while ((temp[temp.size() - 1] == '.') || (temp[temp.size() - 1] == ',') || (temp[temp.size() - 1] == ')'))
            temp = temp.substr(0, temp.size() - 1);
        if (count >= size)
        {
            count = 0;
            page++;
        }
        if (a.find(temp)==a.end())
        {
            int* pointer = new int[100];
            for (int i = 0; i < 100; i++)
                pointer[i] = 0;
            pointer[0] = page;
            a.insert(make_pair(temp, pointer));
        }
        else
        {
            for (int i = 0; i < 100; i++)
                if (a[temp][i] == page)
                    break;
                else
                    if (a[temp][i] == 0)
                    {
                        a[temp][i] = page;
                        break;
                    }
        }
    }
    return a;
}


int main()
{
    setlocale(LC_CTYPE, "rus");
    /* srand(RAND_MAX);
    try
        {
            
        }
        catch (const std::exception&)
        {
            std::cerr << "We caught an exception";
        }
        std::cout << "Continuing our way!\n";
    printf("Running tests...\n");
    //testsequence();

    /*int k = 1;
    while (k)
    {
        int c=0;
        printf("Choose your action \n 1 for work with binary trees 2 for work with threeary trees 3 for end \n");
        std::cin >> c;
        if (c == 1)
            BinaryInterface();
        if (c == 3) k = 0;
        if (c == 2)
            ThreearyInterface();
    }

    SortInterface();

    */


    //tictactoe_interface();
    map <string, int*> a;
    int size = 100;
    a = BuildMap(size);
    map <string, int*> ::iterator it = a.begin();
    for (int i = 0; it != a.end(); it++)
    {
        cout << it->first << ' ';
        int j = 0;
        while (it->second[j] != 0)
        {
            cout << it->second[j] << ' ';
            j++;
        }
        cout << endl;
    }

    string* a1 = new string[1000];
    for (int i = 0; i < 1000; i++)
    {
        a1[i] = std::to_string(i);
    }
    cout << a1[hashf("123", a1)];
}
