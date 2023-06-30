#ifndef LIST_HPP
#define LIST_HPP

#include "nodes.hpp"
#include "visualize.hpp"

List* newList(int iData);
void swapNext(List** head, List* ptrNode);
void swapNodes(List** head, List* ptrNode1, List* ptrNode2);
int lenght(List** head);
void bubbleSort(List** head);
void insertionSort(List** head);
void selectionSort(List** head);
void shellSort(List** head);
List* treeToList(Node* root);
void printList(List* head);

#endif