#include <iostream>
#include <cmath>
#include "../headers/list.hpp"





// ========================================================================

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// Função para calcular o número de dígitos de um número
int numDigits(int number)
{
    int digits = 0;

    while (number)
    {
        number /= 10;
        digits++;
    }

    return digits;
}

// Função para calcular o número de hashtags para cada valor na lista vinculada
map<int, int> calculateHashes(struct List* head)
{
    // Cria um vetor para armazenar os valores dos nós
    vector<int> values;
    struct List* node = head;

    // Percorre a lista vinculada e adicionar os valores ao vetor
    while (node != nullptr)
    {
        values.push_back(node->iData);
        node = node->ptrNext;
    }

    // Ordena o vetor em ordem crescente
    sort(values.begin(), values.end());

    // Cria um mapa para armazenar o valor e o número de hashtags correspondente
    map<int, int> hashes;

    // Atribui o número de hashtags para cada valor
    for (vector<int>::size_type i = 0; i < values.size(); ++i)
    {
        hashes[values[i]] = i + 1;
    }

    return hashes;
}

void displayList(struct List* head)
{
    // Calcule o número de hashtags para cada valor
    map<int, int> hashes = calculateHashes(head);

    // Encontra o valor máximo no mapa de hashes
    // Fazemos isso para que nunca tenhamos barras verticais desalinhadas com os números
    int max_val = 0;
    int max_digits = 0;
    for (auto& pair : hashes)
    {
        if (pair.second > max_val)
            max_val = pair.second;
        int digits = numDigits(pair.first);
        if (digits > max_digits)
            max_digits = digits;
    }

    // Imprime as barras
    for (int height = max_val; height >= 1; --height)
    {
        struct List* node = head;
        while (node != nullptr)
        {
            if (hashes[node->iData] >= height)
                cout << string(max_digits, 'O') + " ";
            else
                cout << string(max_digits, ' ') + " ";
            node = node->ptrNext;
        }
        cout << endl;
    }

    // Imprime os números
    struct List* node = head;
    while (node != nullptr)
    {
        cout << setw(max_digits) << node->iData << ' ';
        node = node->ptrNext;
    }
    cout << endl;

    // Espera por meio segundo e apaga 
    this_thread::sleep_for(chrono::milliseconds(500));

   system("clear||cls");
}

// ========================================================================





List* newList(int iVal)
{
    List* ptrNewList = new List;
    ptrNewList->iData = iVal;
    ptrNewList->ptrNext = nullptr;
    ptrNewList->ptrPrev = nullptr;

    return ptrNewList;
}

void swapNext(List** head, List* ptrNo)
{
    List* ptrNext = ptrNo->ptrNext;
    List* ptrTemp;

    if(ptrNo == *head)
    {
        *head = ptrNext;
    }
    else ptrNo->ptrPrev->ptrNext = ptrNext; 
    
    if(ptrNext->ptrNext != nullptr)
    {
        ptrNext->ptrNext->ptrPrev = ptrNo; 
    }

    List* ptrNoPrev = ptrNo->ptrPrev;
    ptrNo->ptrPrev = ptrNext;
    ptrNo->ptrNext = ptrNext->ptrNext;
    ptrNext->ptrNext = ptrNo;
    ptrNext->ptrPrev = ptrNoPrev;
}

void swapNodes(List** head, List* ptrNode1, List* ptrNode2)
{
    if(ptrNode1->ptrNext == ptrNode2)
    {
        swapNext(head, ptrNode1);
        return;
    }
    if(ptrNode2->ptrNext == ptrNode1)
    {
        swapNext(head, ptrNode2);
        return;
    }
    
    if(ptrNode1->ptrPrev == nullptr) *head = ptrNode2;
    else ptrNode1->ptrPrev->ptrNext = ptrNode2; 
    
    if(ptrNode1->ptrNext != nullptr) ptrNode1->ptrNext->ptrPrev = ptrNode2;
    
    if(ptrNode2->ptrPrev == nullptr) *head = ptrNode1;
    else ptrNode2->ptrPrev->ptrNext = ptrNode1;
    
    if(ptrNode2->ptrNext != nullptr) ptrNode2->ptrNext->ptrPrev = ptrNode1;

    List* ptrTemp = (List*)malloc(sizeof(List));
    ptrTemp->ptrPrev = ptrNode1->ptrPrev;
    ptrTemp->ptrNext = ptrNode1->ptrNext;

    ptrNode1->ptrPrev = ptrNode2->ptrPrev; 
    ptrNode1->ptrNext = ptrNode2->ptrNext; 
    ptrNode2->ptrPrev = ptrTemp->ptrPrev; 
    ptrNode2->ptrNext = ptrTemp->ptrNext;
    free(ptrTemp);
}

int lenght(List** head)
{
    int iSize = 0;
    List* ptrTemp = (*head);
    while(ptrTemp != nullptr)
    {
        iSize++;
        ptrTemp = ptrTemp->ptrNext;
    }
    return iSize;
}

void bubbleSort(struct List** head)
{
    struct List* ptrTemp = *head;
    int iSize = 0;
    while(ptrTemp != nullptr)
    {
        ptrTemp = ptrTemp->ptrNext;
        iSize++;
    }

    for(int i=1; i<iSize; i++)
    {
        ptrTemp = *head;
        bool Swapped = false;
        for(int j=0; j<iSize-i; j++)
        {
            if(ptrTemp->iData > ptrTemp->ptrNext->iData)
            {
                displayList(*head);
                swapNext(head, ptrTemp);
                Swapped = true;
            }
            else ptrTemp = ptrTemp->ptrNext;
        }
        if(!Swapped) break;
    }
}

void selectionSort(struct List** head)
{
    struct List* ptrTemp1 = (*head);

    while (ptrTemp1 != nullptr)
    {
        struct List* ptrTemp2 = ptrTemp1->ptrNext;
        struct List* ptrMin = ptrTemp1;

        while (ptrTemp2 != nullptr)
        {
            if (ptrMin->iData > ptrTemp2->iData)
            {
                ptrMin = ptrTemp2;
            }
            ptrTemp2 = ptrTemp2->ptrNext;
        }

        displayList(*head);
        swapNodes(head, ptrMin, ptrTemp1);

        ptrTemp1 = ptrMin->ptrNext;
    }
}

void insertSort(List** head)
{
    List* ptrTemp = (*head);
    while(ptrTemp->ptrNext != nullptr)
    {
        ptrTemp = ptrTemp->ptrNext;
        while(ptrTemp->iData < ptrTemp->ptrPrev->iData)
        {
            displayList(*head);
            swapNodes(head, ptrTemp, ptrTemp->ptrPrev);
            if(ptrTemp->ptrPrev == nullptr) break;
        }
    }
}

void shellSort(List** head)
{
    int k = 0;
    while(pow(2,k+1)<=lenght(head))
    {
        k++;
    }
    
    while(k > 0)
    {
        int iGap = pow(2,k)-1;
        //first e second apontam para os 2 primeiros elementos
        //da sublista dos elementos separados pelo iGap
        List* ptrFirst = (*head);
        List* ptrSecond = ptrFirst;
        for(int i=0; i<iGap; i++)
        {
            ptrSecond = ptrSecond->ptrNext;
        }
        
        for(int i=0; i<iGap; i++)
        {
            //loop que passa por cada sublista
            List* ptrPrior = ptrFirst;
            List* ptrPost = ptrSecond;
            
            while(ptrPost != nullptr)
            {
                //faz um insertion sort com essa sublista
                //a cada loop ptrPrior e ptrPost andam um elemento na sublista
                List* ptrTemp1 = ptrPrior;
                List* ptrTemp2 = ptrPost;
                
                while(ptrTemp2->iData < ptrTemp1->iData)
                {
                    displayList(*head);
                    swapNodes(head, ptrTemp1, ptrTemp2);
                    //garante que os ponteiros continuem apontando para o mesmo indice da lista
                    if(ptrTemp1 == ptrFirst) ptrFirst = ptrTemp2;
                    else if(ptrTemp2 == ptrFirst) ptrFirst = ptrTemp1;
                    if(ptrTemp1 == ptrSecond) ptrSecond = ptrTemp2;
                    else if(ptrTemp2 == ptrSecond) ptrSecond = ptrTemp1;
                    if(ptrTemp1 == ptrPrior) ptrPrior = ptrTemp2;
                    else if(ptrTemp2 == ptrPrior) ptrPrior = ptrTemp1;
                    if(ptrTemp1 == ptrPost) ptrPost = ptrTemp2;
                    else if(ptrTemp2 == ptrPost) ptrPost = ptrTemp1;
                    
                    //faz com que o ptrTemp1 aponte para o elemento anterior da sublista
                    ptrTemp1 = ptrTemp2;
                    for(int i=0; i<iGap; i++)
                    {
                        ptrTemp1 = ptrTemp1->ptrPrev;
                        if(ptrTemp1 == nullptr) break;
                    }
                    if(ptrTemp1 == nullptr) break;
                }
                
                //faz com que ptrPrior e ptrPost apontem para os prox elementos da sublista
                ptrPrior = ptrPost;
                for(int i=0; i<iGap; i++)
                {
                    ptrPost = ptrPost->ptrNext;
                    if(ptrPost == nullptr) break;
                }
            }

            //atualiza os ponteiros first e second para proxima sublista
            ptrFirst = ptrFirst->ptrNext;
            ptrSecond = ptrSecond->ptrNext;
            if(ptrSecond == nullptr) break;
        }
        
        k--;
    }
}

List* treeToList(Node* root)
{
    if(root == nullptr) return nullptr; // Se a raíz é nullptr a árvore é vazia

    List* ptrList = newList(root->iData); // Cria um nó da lista com o valor da raíz
    List* ptrLeft = treeToList(root->ptrLeft); // Cria uma lista com os nós da sub-árvore a esquerda
    List* ptrRight = treeToList(root->ptrRight); // Cria uma lista com os nós da sub-árvore a direita

    if(ptrLeft != nullptr) 
    {
        ptrList->ptrNext = ptrLeft; // Conecta o primeiro nó da lista com o primeiro nó da lista da sub-árvore a esquerda
        ptrLeft->ptrPrev = ptrList; // Conecta o primeiro nó da lista da sub-árvore a esquerda com o primeiro nó da lista
    }

    List* ptrListTail = ptrList; // Cria um ponteiro para o último nó da lista

    while(ptrListTail->ptrNext != nullptr) 
    {
        ptrListTail = ptrListTail->ptrNext; 
    }

    if(ptrRight != nullptr) 
    {
        ptrListTail->ptrNext = ptrRight; // Conecta o último nó da lista com o primeiro nó da lista da sub-árvore a direita
        ptrRight->ptrPrev = ptrListTail; // Conecta o primeiro nó da lista da sub-árvore a direita com o último nó da lista
    }

    // Retorna o primeiro nó da lista
    return ptrList;
}