#ifndef TREE_HPP
#define TREE_HPP

#include "nodes.hpp"
#include "queue.hpp"

Node* newNode(int iVal);
Node* insertTree(Node* sNode, int iVal);
Node* searchNode(Node* root, int iData);
Node* searchParent(Node* root, Node* sNode);
Node* swapRoot(Node* root, Node* sNode);
Node* swapTree(Node* root, Node* sNode1, Node* sNode2);
int treeHeight(Node* sNode);
Node* lesserLeaf(struct Node* sNode);
Node* deleteNode(struct Node* sNode, int iValue, Node* root);
int treeSize(struct Node* root);
bool isComplete(Node* root);
int leftHeight(Node* root);
bool isPerfect(Node* root, int iLevel, int iHeight);
void BFS(struct Node* ptrStartingNode);

#endif