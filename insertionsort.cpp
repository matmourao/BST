#include <iostream>

using namespace std;

struct Node
{
    int iData;
    struct Node* ptrNext;
    struct Node* ptrPrev;
};

void insertionSort(struct Node** head)
{
    struct Node* ptrTemp1 = (*head)->ptrNext;

    while (ptrTemp1 != nullptr)
    {
        struct Node* ptrTemp2 = ptrTemp1->ptrPrev;
        struct Node* ptrTemp3 = ptrTemp1->ptrNext;

        if (ptrTemp1->iData > ptrTemp2->iData)
        {
            ptrTemp1 = ptrTemp3;
            continue;
        }

        while (ptrTemp1->iData < ptrTemp2->iData)
        {
            if (ptrTemp2->ptrNext == ptrTemp1) ptrTemp2->ptrNext = ptrTemp1->ptrNext;

            ptrTemp2 = ptrTemp2->ptrPrev;
            if (ptrTemp2 == nullptr) break;
        }

        if (ptrTemp2 == nullptr)
        {
            ptrTemp1->ptrNext = *head;
            (*head)->ptrPrev = ptrTemp1;
            ptrTemp1->ptrPrev = nullptr;
            *head = ptrTemp1;
        }
        else if (ptrTemp2)
        {
            ptrTemp2->ptrNext->ptrPrev = ptrTemp1;
            ptrTemp1->ptrNext = ptrTemp2->ptrNext;
            ptrTemp1->ptrPrev = ptrTemp2;
            ptrTemp2->ptrNext = ptrTemp1;
        }

        ptrTemp1 = ptrTemp3;
    }
}