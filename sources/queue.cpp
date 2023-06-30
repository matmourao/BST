#include <iostream>
#include "../headers/queue.hpp"

QueueNode* front = nullptr;
QueueNode* rear = nullptr;

// Implementação da função enfileirar
void enQueue(Node* treeNode) 
{
    QueueNode* temp = new QueueNode(); // Cria uma nova queueNode
    temp->treeNode = treeNode; // Atribui o valor do nó da árvore à queueNode
    temp->next = nullptr; // Atribui nullptr ao ponteiro next da queueNode

    if(front == nullptr && rear == nullptr) 
    {
        front = rear = temp; // Se a fila está vazia, front e rear apontam para a nova queueNode
        return;
    }

    rear->next = temp; // O ponteiro next do último elemento da fila aponta para a nova queueNode
    rear = temp; // Rear aponta para a nova queueNode
}

// Implementação da função desenfileirar
Node* deQueue() 
{
    // Se a fila está vazia, retorna nullptr
    if(front == nullptr) 
    {
        return nullptr;
    }

    QueueNode* temp = front; // Cria um ponteiro para o primeiro elemento da fila
    Node* nodeToReturn = temp->treeNode; // Cria um ponteiro para o nó da árvore que será retornado

    front = front->next; // Front aponta para o segundo elemento da fila
    if(front == nullptr) 
    {
        rear = nullptr; // Se a fila está vazia, rear aponta para nullptr
    }

    delete temp; // Deleta o primeiro elemento da fila

    return nodeToReturn; // Retorna o nó da árvore
}

// Implementação da função para verificar se a fila está vazia
bool isQueueEmpty() 
{
    return front == nullptr; // Se front aponta para nullptr, a fila está vazia
}
