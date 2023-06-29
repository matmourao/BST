#include <iostream>

using namespace std;

struct Node
{
    int iData;
    struct Node* ptrNext;
    struct Node* ptrPrev;
};

void sortedInsertion(struct Node** head, struct Node* newNode)
{
    if (*head == nullptr) *head = newNode;
    else if ((*head)->iData >= newNode->iData)
    {
        newNode->ptrNext = *head;
        (*head)->ptrPrev = newNode;
        (*head) = newNode;
    }
    else
    {
        struct Node* ptrTemp = *head;
        while (ptrTemp->ptrNext != nullptr && ptrTemp->ptrNext->iData < newNode->iData) ptrTemp = ptrTemp->ptrNext;

        newNode->ptrNext = ptrTemp->ptrNext;
        if (ptrTemp->ptrNext != nullptr) ptrTemp->ptrNext->ptrPrev = newNode;

        ptrTemp->ptrNext = newNode;
        newNode->ptrPrev = ptrTemp;
    }
}

void insertionSort(struct Node** head)
{
    struct Node* ptrSorted = nullptr;
    struct Node* ptrCurrent = *head;

    while (ptrCurrent != nullptr)
    {
        struct Node* ptrNext = ptrCurrent->ptrNext;

        ptrCurrent->ptrNext = nullptr;
        ptrCurrent->ptrPrev = nullptr;

        sortedInsertion(&ptrSorted, ptrCurrent);

        ptrCurrent = ptrNext;
    }

    *head = ptrSorted;
}
