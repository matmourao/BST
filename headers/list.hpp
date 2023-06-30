#ifndef LIST_HPP
#define LIST_HPP

#include "nodes.hpp"

List* newList(int iData);
void swapNext(List** head, List* ptrNode);
void swapNodes(List** head, List* ptrNode1, List* ptrNode2);
void bubbleSort(List** head);
void insertionSort(List** head);
void selectionSort(List** head);
void shellSort(List** head);
int lenght(List** head);
List* treeToList(Node* root);

#endif