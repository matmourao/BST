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

    while (ptrTemp1->ptrNext != nullptr)
    {
        struct Node* ptrTemp2 = ptrTemp1->ptrPrev;

        while (ptrTemp1->iData < ptrTemp2->iData && ptrTemp2 != nullptr)
        {
            ptrTemp2->ptrPrev = ptrTemp2;
            ptrTemp2->ptrNext = ptrTemp2->ptrNext->ptrNext;

            ptrTemp2 = ptrTemp2->ptrPrev;
        }

        if (ptrTemp2 == nullptr)
        {
            ptrTemp1->ptrNext = *head;
            ptrTemp1->ptrPrev = nullptr;
            (*head) = ptrTemp1;
        }
        else
        {
        ptrTemp1->ptrPrev = ptrTemp2;
        ptrTemp1->ptrNext = ptrTemp2->ptrNext->ptrNext;
        }

        ptrTemp1 = ptrTemp1->ptrNext;
    }
}