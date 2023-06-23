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

void swapNodes(Node** head, Node* ptrNode1, Node* ptrNode2)
{
    if(ptrNode1->ptrNext == ptrNode2)
    {
        swapNext(head, ptrNode1);
        return;
    }
    if(ptrNode2->ptrNext == ptrNode1)
    {
        swapNext(head, ptrNode2);
        return;
    }
    
    if(ptrNode1->ptrPrev == nullptr) *head = ptrNode2;
    else ptrNode1->ptrPrev->ptrNext = ptrNode2; 
    
    if(ptrNode1->ptrNext != nullptr) ptrNode1->ptrNext->ptrPrev = ptrNode2;
    
    if(ptrNode2->ptrPrev == nullptr) *head = ptrNode1;
    else ptrNode2->ptrPrev->ptrNext = ptrNode1;
    
    if(ptrNode2->ptrNext != nullptr) ptrNode2->ptrNext->ptrPrev = ptrNode1;

    Node* ptrTemp = (Node*)malloc(sizeof(Node));
    ptrTemp->ptrPrev = ptrNode1->ptrPrev;
    ptrTemp->ptrNext = ptrNode1->ptrNext;

    ptrNode1->ptrPrev = ptrNode2->ptrPrev; 
    ptrNode1->ptrNext = ptrNode2->ptrNext; 
    ptrNode2->ptrPrev = ptrTemp->ptrPrev; 
    ptrNode2->ptrNext = ptrTemp->ptrNext;
    free(ptrTemp);
}

void selectionSort(struct Node** head)
{
    struct Node* ptrTemp1 = (*head);

    while (ptrTemp1 != nullptr)
    {
        struct Node* ptrTemp2 = ptrTemp1->ptrNext;
        struct Node* ptrMin = ptrTemp1;

        while (ptrTemp2 != nullptr)
        {
            if (ptrMin->iData > ptrTemp2->iData)
            {
                ptrMin = ptrTemp2;
            }
            ptrTemp2 = ptrTemp2->ptrNext;
        }

        swapNodes(head, ptrMin, ptrTemp1);

        ptrTemp1 = ptrMin->ptrNext;
    }
}