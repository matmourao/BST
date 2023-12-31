#include <iostream>
#include "../headers/tree.hpp"

using namespace std;

Node* newNode(int iValue)
{
    Node* ptrTemp = (Node*) malloc(sizeof(Node));
    ptrTemp -> ptrRight = nullptr;
    ptrTemp -> ptrLeft = nullptr;
    ptrTemp -> iData = iValue;

    return ptrTemp;
}

Node* insertTree(Node* sNode, int iValue)
{
    if(sNode == nullptr) return newNode(iValue);
    
    if(iValue < sNode->iData)
    {
        sNode -> ptrLeft = insertTree(sNode -> ptrLeft, iValue);
    }
    else
    {
        sNode -> ptrRight = insertTree(sNode -> ptrRight, iValue);
    }

    return sNode;
}

// Função que dado um elemento, busca o endereço dele na árvore
Node* searchNode(Node* root, int iData)
{
    if(root == nullptr) return nullptr; // Se a árvore é nula então retornará nulo

    if(root -> iData == iData) return root; // Se o nó atual é o nó procurado, retorna o endereço dele

    if(iData < root -> iData) return searchNode(root -> ptrLeft, iData); // Se o nó procurado é menor que o nó atual, procura na sub-árvore a esquerda

    return searchNode(root -> ptrRight, iData); // Se o nó procurado é maior que o nó atual, procura na sub-árvore a direita
}

// Função que dado um nó e a raiz da árvore, busca seu nó pai nessa árvore
Node* searchParent(Node* root, Node* sNode)
{
    if(sNode == root) return nullptr; // Se o nó dado é nulo então retornará nulo
    if(root == nullptr) return nullptr; // Se a árvore é nula então retornará nulo

    int iValue = sNode -> iData;

    // Verifica se root é o nó pai
    if(root -> ptrLeft == sNode) return root;
    if(root -> ptrRight == sNode) return root;

    // Se não for, busca para a sub-árvore a direita ou a esquerda
    if(iValue < root->iData) return searchParent(root -> ptrLeft, sNode);
    else return searchParent(root -> ptrRight, sNode);
}

// Realiza a troca entre um node e a root da sua arvore, retornando o novo root
Node* swapRoot(Node* root, Node* sNode)
{
    // Se root for pai do Node, basta realizar a troca dos ponteiros
    if(root -> ptrRight == sNode)
    {
        Node* sLeft = root -> ptrLeft;
        root -> ptrLeft = sNode -> ptrLeft;
        root -> ptrRight = sNode -> ptrRight;
        sNode -> ptrRight = root;
        sNode -> ptrLeft = sLeft;        
    }
    else if(root -> ptrLeft == sNode)
    {
        Node* sRight = root -> ptrRight;
        root -> ptrLeft = sNode -> ptrLeft;
        root -> ptrRight = sNode -> ptrRight;
        sNode -> ptrLeft = root;
        sNode -> ptrRight = sRight; 
    }

    // Se não for, a troca é mais complicada
    else
    {
        // Faz o pai do Node apontar para o filho do root
        Node* sParent = searchParent(root, sNode);
        if(sNode -> iData < sParent -> iData) sParent -> ptrLeft = root;
        else sParent -> ptrRight = root;
        
        // Troca os ponteiros Right e Left do root com o Node
        Node* sLeft = root -> ptrLeft;
        Node* sRight = root -> ptrRight;
        root -> ptrRight = sNode -> ptrRight;
        root -> ptrLeft = sNode -> ptrLeft;
        sNode -> ptrRight = sRight;
        sNode -> ptrLeft = sLeft;
    }

    return sNode;
}

// Realiza a troca e retorna o root
Node* swapTree(Node* root, Node* sNode1, Node* sNode2)
{
    // Se um dos nodes for o root. chama swapRoot
    if(sNode1 == root) return swapRoot(root, sNode2);
    if(sNode2 == root) return swapRoot(root, sNode1);

    // Define os ponteiros dos pais
    Node* sParent1 = searchParent(root, sNode1);
    Node* sParent2 = searchParent(root, sNode2);

    // Faz os pais apontarem para seus novos filhos
    if(sNode1 -> iData < sParent1 -> iData) sParent1 -> ptrLeft = sNode2;
    else sParent1 -> ptrRight = sNode2;
    if(sNode2 -> iData < sParent2 -> iData) sParent2 -> ptrLeft = sNode1;
    else sParent2 -> ptrRight = sNode1;

    // Troca os ponteiros Right e Left do Node1 com o Node2
    Node* sLeft1 = sNode1 -> ptrLeft;
    Node* sRight1 = sNode1 -> ptrRight;
    sNode1 -> ptrRight = sNode2 -> ptrRight;
    sNode1 -> ptrLeft = sNode2 -> ptrLeft;
    sNode2 -> ptrRight = sRight1;
    sNode2 -> ptrLeft = sLeft1;

    return root;
}

// Calcula a altura de uma árvore
int treeHeight(Node* sNode)
{
    if(sNode == nullptr) return -1; // Ao atingirmos uma folha, diminui 1 do total de nós caminhados
    else
    {
        // Calcula recursivamente a altura das sub-árvores
        int iRightHeight = treeHeight(sNode -> ptrRight);
        int iLeftHeight = treeHeight(sNode -> ptrLeft);

        // Ao atingir uma folha, a função irá voltar de nó em nó até a raiz somando 1 às alturas em cada subida e retorna a maior
        if(iRightHeight > iLeftHeight) return iRightHeight + 1;
        else return iLeftHeight + 1;
    }
}

// Auxiliar: Procura o nó com o menor valor de uma árvore
Node* lesserLeaf(struct Node* sNode)
{
    struct Node* ptrCurrent = sNode;

    // Anda sempre para a esquerda até chegar uma folha, garantindo que será o nó de menor valor
    while(ptrCurrent && ptrCurrent -> ptrLeft != nullptr) ptrCurrent = ptrCurrent -> ptrLeft;

    return ptrCurrent;
}

// Deleta um nó de uma árvore
Node* deleteNode(struct Node* sNode, int iValue, Node* root)
{
    // Se o nó é nulo, não tem o que remover
    if(sNode == nullptr) return sNode;

    // Procura o nó a ser removido
    if(iValue < sNode -> iData) sNode -> ptrLeft = deleteNode(sNode -> ptrLeft, iValue, root);
    else if(iValue > sNode -> iData) sNode -> ptrRight = deleteNode(sNode -> ptrRight, iValue, root);

    // Ao encontrar o nó, começa o processo de remoção
    else
    {
        struct Node* ptrTemp = nullptr;

        // Se o nó possui somente um filho, o nó é removido e seu filho é o novo filho do nó anterior
        if(sNode -> ptrLeft == nullptr)
        {
            ptrTemp = sNode -> ptrRight;
            free(sNode);

            return ptrTemp;
        }
        else if(sNode -> ptrRight == nullptr)
        {
            ptrTemp = sNode -> ptrLeft;
            free(sNode);

            return ptrTemp;
        }

        // Se o nó possui dois filho, procura o menor nó a direita para substituí-lo, garantindo a estabilidade da árvore 
        ptrTemp = lesserLeaf(sNode -> ptrRight);

        // Troca os nós de lugar e continua o processo para a nova arvore
        root = swapTree(root, sNode, ptrTemp);
        ptrTemp -> ptrRight = deleteNode(ptrTemp -> ptrRight, iValue, root);
        return ptrTemp;
    }

    return sNode;
}

// Calcula o número de nós numa árvore binária
int treeSize(struct Node* root)
{
    if(root == nullptr) return 0; // Se a raíz é nullptr a árvore tem tamanho zero

    int iLeftSize = treeSize(root -> ptrLeft); // Calcula o número de nós na sub-árvore a esquerda
    int iRightSize = treeSize(root -> ptrRight); // Calcula o número de nós na sub-árvore a direita

    int iSize = iLeftSize + iRightSize + 1; // Retorna o tamanho das sub-árvores + 1 (a própria raíz)

    return iSize; 
}

// Verifica se a árvore é completa (nenhuma folha com exatamente um nó)
bool isComplete(Node* root)
{
    if (root == nullptr) return true; // Se a raíz é nula, a árvore é completa

    if(root -> ptrLeft == nullptr && root -> ptrRight == nullptr) return true; // Se o nó é folha, a árvore é completa

    if(root -> ptrLeft == nullptr || root -> ptrRight == nullptr) return false; // Se o nó tem somente um filho, retorna falso, árvore não é completa

    bool bLeft = isComplete(root -> ptrLeft); // Flag para mostrar se a sub-árvore a esquerda é completa
    bool bRight = isComplete(root -> ptrRight); // Flag para mostrar se a sub-árvore a direita é completa

    return bLeft && bRight; // Retorna se as duas sub-árvores são completas
}

// Calcula a altura do ramo que leva ao nó mais a esquerda da árvore
int leftHeight(Node* root)
{
    int iHeight = -1;

    while(root != nullptr)
    {
        iHeight++;
        root = root -> ptrLeft;
    }

    return iHeight;
}

// Verifica se uma árvore é perfeita
bool isPerfect(Node* root, int iLevel, int iHeight)
{
    if(root == nullptr) return true; // Se a raíz é nula, é perfeita

    // Verifica se o nó é uma folha
    if (root -> ptrLeft == nullptr && root -> ptrRight == nullptr)
    {
        if(iLevel == iHeight + 1) return true; // Se é uma folha, verifica se seu nível é correspondente ao das outras
        return false;
    }
    
    // Se o código chega aqui, então o nó não é uma folha, logo, verifica-se a quantidade de filhos, se algum for nulo, não é perfeita
    if (root -> ptrLeft == nullptr || root -> ptrRight == nullptr) return false;
    
    // Verifica se as sub-árvores também são perfeitas, aumentando em 1 o nível atual
    if(isPerfect(root -> ptrLeft, iLevel, iHeight + 1) && isPerfect(root -> ptrRight, iLevel, iHeight + 1)) return true;
    return false;
}

// Printa a lista por BFS
void BFS(Node* root) 
{
    // Enfileira o nó raiz.
    enQueue(root);

    while(!isQueueEmpty()) 
    { 
        // Desenfileira o próximo nó.
        Node* currentNode = deQueue();

        // Imprime o valor do nó.
        cout << currentNode->iData << ' ';

        // Enfileira os filhos (se existirem).
        if(currentNode->ptrLeft != nullptr) {
            enQueue(currentNode->ptrLeft);
        }

        if(currentNode->ptrRight != nullptr) {
            enQueue(currentNode->ptrRight);
        }
    }
}