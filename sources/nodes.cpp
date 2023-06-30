#include <iostream>
#include "../headers/tree.hpp"

struct Node
{
    int iData;
    Node* ptrLeft;
    Node* ptrRight;
};

struct QueueNode 
{
    Node* treeNode;
    QueueNode* next;
};

struct List
{
    int iData;
    struct List* ptrNext;
    struct List* ptrPrev;
};