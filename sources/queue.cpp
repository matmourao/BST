#include <iostream>
#include "../headers/queue.hpp"

QueueNode* front = nullptr;
QueueNode* rear = nullptr;

// Implementação da função enfileirar
void enfileirar(Node* treeNode) 
{
    QueueNode* temp = new QueueNode();
    temp->treeNode = treeNode;
    temp->next = nullptr;

    if(front == nullptr && rear == nullptr) {
        front = rear = temp;
        return;
    }

    rear->next = temp;
    rear = temp;
}

// Implementação da função desenfileirar
Node* desenfileirar() 
{
    if(front == nullptr) {
        return nullptr;
    }

    QueueNode* temp = front;
    Node* nodeToReturn = temp->treeNode;

    front = front->next;
    if(front == nullptr) {
        rear = nullptr;
    }

    delete temp;

    return nodeToReturn;
}

// Implementação da função para verificar se a fila está vazia
bool isQueueEmpty() 
{
    return front == nullptr;
}
