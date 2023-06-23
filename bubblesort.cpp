#include <iostream>

using namespace std;

struct Node
{
    int iData;
    struct Node* ptrNext;
    struct Node* ptrPrev;
};

void swapNext(Node** head, Node* ptrNo)
{
    Node* ptrNext = ptrNo->ptrNext;
    Node* ptrTemp;

    if(ptrNo == *head)
    {
        *head = ptrNext;
    }
    else ptrNo->ptrPrev->ptrNext = ptrNext; 
    
    if(ptrNext->ptrNext != nullptr)
    {
        ptrNext->ptrNext->ptrPrev = ptrNo; 
    }

    Node* ptrNoPrev = ptrNo->ptrPrev;
    ptrNo->ptrPrev = ptrNext;
    ptrNo->ptrNext = ptrNext->ptrNext;
    ptrNext->ptrNext = ptrNo;
    ptrNext->ptrPrev = ptrNoPrev;
}

void bubbleSort(struct Node** head)
{
    struct Node* ptrTemp1 = *head;
    int iSize = 0;
    while (ptrTemp1 != nullptr)
    {
        ptrTemp1 = ptrTemp1->ptrNext;
        iSize++;
    }

    for (int i=0; i<iSize; i++)
    {
        struct Node* ptrTemp = *head;
        while (ptrTemp->ptrNext != nullptr)
        {
            if (ptrTemp->iData > ptrTemp->ptrNext->iData) swapNext(head, ptrTemp);
            else ptrTemp = ptrTemp->ptrNext;
        }
    }
}