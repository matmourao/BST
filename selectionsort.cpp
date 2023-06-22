#include <iostream>

using namespace std;

struct Node
{
    int iData;
    struct Node* ptrNext;
    struct Node* ptrPrev;
};

void swapNodes(struct Node** head, Node* ptrNode1, Node* ptrNode2)
{
    struct Node* ptrTemp = (struct Node*)malloc(sizeof(struct Node));
    ptrTemp->ptrPrev = ptrNode1->ptrPrev;
    ptrTemp->ptrNext = ptrNode1->ptrNext;

    if (ptrNode2->ptrNext != ptrNode1)
    {
        if (ptrNode1->ptrPrev != nullptr) ptrNode1->ptrPrev->ptrNext = ptrNode2;
        else *head = ptrNode2;

        if (ptrNode2->ptrNext != nullptr) ptrNode2->ptrNext->ptrPrev = ptrNode1;
    }

    if (ptrNode1->ptrNext != ptrNode2)
    {
        if (ptrNode2->ptrPrev != nullptr) ptrNode2->ptrPrev->ptrNext = ptrNode1;
        else *head = ptrNode1;

        if (ptrNode1->ptrNext != nullptr) ptrNode1->ptrNext->ptrPrev = ptrNode2;
    }

    if (ptrNode1->ptrNext == ptrNode2)
    {
        ptrNode1->ptrPrev = ptrNode2;
        ptrNode1->ptrNext = ptrNode2->ptrNext;
        ptrNode2->ptrNext = ptrNode1;
        ptrNode2->ptrPrev = ptrTemp->ptrPrev;
    }
    else if (ptrNode2->ptrNext == ptrNode1)
    {
        ptrNode1->ptrNext = ptrNode2;
        ptrNode1->ptrPrev = ptrTemp->ptrPrev;
        ptrNode2->ptrPrev = ptrNode1;
        ptrNode2->ptrNext = ptrTemp->ptrNext;
    }
    else
    {
        ptrNode1->ptrPrev = ptrNode2->ptrPrev;
        ptrNode1->ptrNext = ptrNode2->ptrNext;
        ptrNode2->ptrPrev = ptrTemp->ptrPrev;
        ptrNode2->ptrNext = ptrTemp->ptrNext;
    }
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