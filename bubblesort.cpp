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
    struct Node* ptrTemp = *head;
    int iSize = 0;
    while(ptrTemp != nullptr)
    {
        ptrTemp = ptrTemp->ptrNext;
        iSize++;
    }

    for(int i=1; i<iSize; i++)
    {
        ptrTemp = *head;
        bool Swapped = false;
        for(int j=0; j<iSize-i; j++)
        {
            if(ptrTemp->iData > ptrTemp->ptrNext->iData)
            {
                swapNext(head, ptrTemp);
                Swapped = true;
            }
            else ptrTemp = ptrTemp->ptrNext;
        }
        if(!Swapped) break;
    }
}