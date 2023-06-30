#include <iostream>
#include <cmath>
#include "../headers/list.hpp"

using namespace std;

List* newList(int iValue)
{
    List* ptrNewList = new List;
    ptrNewList -> iData = iValue;
    ptrNewList -> ptrNext = nullptr;
    ptrNewList -> ptrPrev = nullptr;

    return ptrNewList;
}

void swapNext(List** head, List* sNode)
{
    List* ptrNext = sNode -> ptrNext;

    if(sNode == *head)
    {
        *head = ptrNext;
    }
    else sNode -> ptrPrev -> ptrNext = ptrNext; 
    
    if(ptrNext -> ptrNext != nullptr)
    {
        ptrNext -> ptrNext -> ptrPrev = sNode; 
    }

    List* sNodePrev = sNode -> ptrPrev;
    sNode -> ptrPrev = ptrNext;
    sNode -> ptrNext = ptrNext -> ptrNext;
    ptrNext -> ptrNext = sNode;
    ptrNext -> ptrPrev = sNodePrev;
}

void swapNodes(List** head, List* sNode1, List* sNode2)
{
    if(sNode1 -> ptrNext == sNode2)
    {
        swapNext(head, sNode1);
        return;
    }
    if(sNode2 -> ptrNext == sNode1)
    {
        swapNext(head, sNode2);
        return;
    }
    
    if(sNode1 -> ptrPrev == nullptr) *head = sNode2;
    else sNode1 -> ptrPrev -> ptrNext = sNode2; 
    
    if(sNode1 -> ptrNext != nullptr) sNode1 -> ptrNext -> ptrPrev = sNode2;
    
    if(sNode2 -> ptrPrev == nullptr) *head = sNode1;
    else sNode2 -> ptrPrev -> ptrNext = sNode1;
    
    if(sNode2 -> ptrNext != nullptr) sNode2 -> ptrNext -> ptrPrev = sNode1;

    List* ptrTemp = (List*)malloc(sizeof(List));
    ptrTemp -> ptrPrev = sNode1 -> ptrPrev;
    ptrTemp -> ptrNext = sNode1 -> ptrNext;

    sNode1 -> ptrPrev = sNode2 -> ptrPrev; 
    sNode1 -> ptrNext = sNode2 -> ptrNext; 
    sNode2 -> ptrPrev = ptrTemp -> ptrPrev; 
    sNode2 -> ptrNext = ptrTemp -> ptrNext;
    free(ptrTemp);
}

int lenght(List** head)
{
    int iSize = 0;
    List* ptrTemp = (*head);

    while(ptrTemp != nullptr)
    {
        iSize++;
        ptrTemp = ptrTemp -> ptrNext;
    }

    return iSize;
}

void bubbleSort(struct List** head)
{
    // percorre a lista para descobrir o tamanho
    struct List* ptrTemp = *head;
    int iSize = 0;

    while(ptrTemp != nullptr)
    {
        ptrTemp = ptrTemp -> ptrNext;
        iSize++;
    }
    
    // cria loop a partir do tamanho
    for(int i = 1; i < iSize; i++)
    {
        ptrTemp = *head;
        bool Swapped = false;
        for(int j = 0; j < iSize - i; j++)
        {
            if(ptrTemp -> iData > ptrTemp -> ptrNext -> iData) // se itens consecutivos não estiverem ordenados, os nós serão trocados
            {
                displayList(*head);
                swapNext(head, ptrTemp);
                Swapped = true;
            }
            else ptrTemp = ptrTemp -> ptrNext;
        }

        if(!Swapped) break;
    }
}

void selectionSort(struct List** head)
{
    struct List* ptrTemp1 = (*head); // ponteiro temporário para loop externo

    while(ptrTemp1 != nullptr)
    {
        struct List* ptrTemp2 = ptrTemp1 -> ptrNext; // ponteiro temporário para loop interno
        struct List* ptrMin = ptrTemp1;  // ponteiro criado para armazenar o valor mínimo

        while(ptrTemp2 != nullptr)
        {
            if(ptrMin -> iData > ptrTemp2 -> iData)
            {
                ptrMin = ptrTemp2; // se ptrTemp2 é menor que o antigo menor valor, ele passa a ser no novo mínimo
            }
            ptrTemp2 = ptrTemp2 -> ptrNext;
        }

        displayList(*head);
        // após todas as iterações (percorrer a lista de ptrTemp1 até nullptr), ptrMin será o menor elemento da lista a partir de ptrTemp1
        // logo, iremos trocar eles de posição para ordenar a lista de maneira crescente
        swapNodes(head, ptrMin, ptrTemp1);

        ptrTemp1 = ptrMin -> ptrNext;
    }
}

void insertionSort(List** head)
{
    List* ptrTemp = (*head);
    while(ptrTemp -> ptrNext != nullptr)
    {
        ptrTemp = ptrTemp -> ptrNext;
        while(ptrTemp -> iData < ptrTemp -> ptrPrev -> iData)
        {
            displayList(*head);
            swapNodes(head, ptrTemp, ptrTemp -> ptrPrev);
            if(ptrTemp -> ptrPrev == nullptr) break;
        }
    }
}

void shellSort(List** head)
{
    int k = 0;

    while(pow(2,k+1) <= lenght(head))
    {
        k++;
    }
    
    while(k > 0)
    {
        int iGap = pow(2,k)-1;

        // First e second apontam para os 2 primeiros elementos da sub-lista dos elementos separados pelo iGap
        List* ptrFirst = (*head);
        List* ptrSecond = ptrFirst;
        for(int i=0; i<iGap; i++)
        {
            ptrSecond = ptrSecond -> ptrNext;
        }
        
        for(int i = 0; i < iGap; i++)
        {
            // Loop que passa por cada sublista
            List* ptrPrior = ptrFirst;
            List* ptrPost = ptrSecond;
            
            while(ptrPost != nullptr)
            {
                // Faz um insertion sort com essa sub-lista e, a cada loop, ptrPrior e ptrPost andam um elemento na sublista
                List* ptrTemp1 = ptrPrior;
                List* ptrTemp2 = ptrPost;
                
                while(ptrTemp2 -> iData < ptrTemp1 -> iData)
                {
                    displayList(*head);
                    swapNodes(head, ptrTemp1, ptrTemp2);
                    // Garante que os ponteiros continuem apontando para o mesmo índice da lista
                    if(ptrTemp1 == ptrFirst) ptrFirst = ptrTemp2;
                    else if(ptrTemp2 == ptrFirst) ptrFirst = ptrTemp1;

                    if(ptrTemp1 == ptrSecond) ptrSecond = ptrTemp2;
                    else if(ptrTemp2 == ptrSecond) ptrSecond = ptrTemp1;

                    if(ptrTemp1 == ptrPrior) ptrPrior = ptrTemp2;
                    else if(ptrTemp2 == ptrPrior) ptrPrior = ptrTemp1;

                    if(ptrTemp1 == ptrPost) ptrPost = ptrTemp2;
                    else if(ptrTemp2 == ptrPost) ptrPost = ptrTemp1;
                    
                    // Faz com que o ptrTemp1 aponte para o elemento anterior da sub-lista
                    ptrTemp1 = ptrTemp2;
                    for(int i = 0; i < iGap; i++)
                    {
                        ptrTemp1 = ptrTemp1 -> ptrPrev;
                        if(ptrTemp1 == nullptr) break;
                    }
                    if(ptrTemp1 == nullptr) break;
                }
                
                // Faz com que ptrPrior e ptrPost apontem para os próximos elementos da sub-lista
                ptrPrior = ptrPost;
                for(int i = 0; i < iGap; i++)
                {
                    ptrPost = ptrPost -> ptrNext;
                    if(ptrPost == nullptr) break;
                }
            }

            // Atualiza os ponteiros first e second para próxima sub-lista
            ptrFirst = ptrFirst -> ptrNext;
            ptrSecond = ptrSecond -> ptrNext;
            if(ptrSecond == nullptr) break;
        }
        
        k--;
    }
}

List* treeToList(Node* root)
{
    if(root == nullptr) return nullptr; // Se a raíz é nullptr a árvore é vazia

    List* ptrList = newList(root -> iData); // Cria um nó da lista com o valor da raíz
    List* ptrLeft = treeToList(root -> ptrLeft); // Cria uma lista com os nós da sub-árvore a esquerda
    List* ptrRight = treeToList(root -> ptrRight); // Cria uma lista com os nós da sub-árvore a direita

    if(ptrLeft != nullptr) 
    {
        ptrList -> ptrNext = ptrLeft; // Conecta o primeiro nó da lista com o primeiro nó da lista da sub-árvore a esquerda
        ptrLeft -> ptrPrev = ptrList; // Conecta o primeiro nó da lista da sub-árvore a esquerda com o primeiro nó da lista
    }

    List* ptrListTail = ptrList; // Cria um ponteiro para o último nó da lista

    while(ptrListTail -> ptrNext != nullptr) 
    {
        ptrListTail = ptrListTail -> ptrNext; 
    }

    if(ptrRight != nullptr) 
    {
        ptrListTail -> ptrNext = ptrRight; // Conecta o último nó da lista com o primeiro nó da lista da sub-árvore a direita
        ptrRight -> ptrPrev = ptrListTail; // Conecta o primeiro nó da lista da sub-árvore a direita com o último nó da lista
    }

    // Retorna o primeiro nó da lista
    return ptrList;
}

void printList(List* head)
{
    while(head -> ptrNext != nullptr)
    {
        cout << head -> iData << ' ';
        head = head -> ptrNext;
    }

    cout << head -> iData << endl;
}