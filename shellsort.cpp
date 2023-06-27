#include <cmath>
#include <iostream>
using namespace std;

struct Node
{
    int iData;
    struct Node* ptrNext;
    struct Node* ptrPrev;
};

void swapNext(Node** head, Node* ptrNo)
{
    Node* ptrNext = ptrNo->ptrNext;
    Node* ptrTemp;

    if(ptrNo == *head)
    {
        *head = ptrNext;
    }
    else ptrNo->ptrPrev->ptrNext = ptrNext; 
    
    if(ptrNext->ptrNext != nullptr)
    {
        ptrNext->ptrNext->ptrPrev = ptrNo; 
    }

    Node* ptrNoPrev = ptrNo->ptrPrev;
    ptrNo->ptrPrev = ptrNext;
    ptrNo->ptrNext = ptrNext->ptrNext;
    ptrNext->ptrNext = ptrNo;
    ptrNext->ptrPrev = ptrNoPrev;
}

void swapNodes(Node** head, Node* ptrNode1, Node* ptrNode2)
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

    Node* ptrTemp = (Node*)malloc(sizeof(Node));
    ptrTemp->ptrPrev = ptrNode1->ptrPrev;
    ptrTemp->ptrNext = ptrNode1->ptrNext;

    ptrNode1->ptrPrev = ptrNode2->ptrPrev; 
    ptrNode1->ptrNext = ptrNode2->ptrNext; 
    ptrNode2->ptrPrev = ptrTemp->ptrPrev; 
    ptrNode2->ptrNext = ptrTemp->ptrNext;
    free(ptrTemp);
}

int lenght(Node** head)
{
    int iSize = 0;
    Node* ptrTemp = (*head);
    while(ptrTemp != nullptr)
    {
        iSize++;
        ptrTemp = ptrTemp->ptrNext;
    }
    return iSize;
}

void shellSort(Node** head)
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
        Node* ptrFirst = (*head);
        Node* ptrSecond = ptrFirst;
        for(int i=0; i<iGap; i++)
        {
            ptrSecond = ptrSecond->ptrNext;
        }
        
        for(int i=0; i<iGap; i++)
        {
            //loop que passa por cada sublista
            Node* ptrPrior = ptrFirst;
            Node* ptrPost = ptrSecond;
            
            while(ptrPost != nullptr)
            {
                //faz um insertion sort com essa sublista
                //a cada loop ptrPrior e ptrPost andam um elemento na sublista
                Node* ptrTemp1 = ptrPrior;
                Node* ptrTemp2 = ptrPost;
                
                while(ptrTemp2->data < ptrTemp1->iData)
                {
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