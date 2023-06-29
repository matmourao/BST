#include <iostream>
#include <fstream>
#include <time.h>
#include "node.h"
#include "queue.cpp"

using namespace std;

struct List
{
    int iPayload;
    struct List* ptrNext;
    struct List* ptrPrev;
};

Node* newNode(int iVal)
{
    Node* ptrTemp = (Node*) malloc(sizeof(Node));
    ptrTemp -> ptrRight = nullptr;
    ptrTemp -> ptrLeft = nullptr;
    ptrTemp -> iData = iVal;

    return ptrTemp;
}

Node* insertTree(Node* sNode, int iVal)
{
    if(sNode == nullptr) return newNode(iVal);
    
    if(iVal < sNode->iData)
    {
        sNode->ptrLeft = insertTree(sNode->ptrLeft, iVal);
    }
    else
    {
        sNode->ptrRight = insertTree(sNode->ptrRight, iVal);
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

    int iValue = sNode->iData;

    // Verifica se root é o nó pai
    if(root->ptrLeft == sNode) return root;
    if(root->ptrRight == sNode) return root;

    // Se não for, busca para a sub-árvore a direita ou a esquerda
    if(iValue < root->iData) return searchParent(root->ptrLeft, sNode);
    else return searchParent(root->ptrRight, sNode);
}

// Realiza a troca entre um node e a root da sua arvore, retornando o novo root
Node* swapRoot(Node* root, Node* sNode)
{
    //se root for pai do Node, basta realizar a troca dos ponteiros
    if(root->ptrRight == sNode)
    {
        Node* sLeft = root->ptrLeft;
        root->ptrLeft = sNode->ptrLeft;
        root->ptrRight = sNode->ptrRight;
        sNode->ptrRight = root;
        sNode->ptrLeft = sLeft;        
    }
    else if(root->ptrLeft == sNode)
    {
        Node* sRight = root->ptrRight;
        root->ptrLeft = sNode->ptrLeft;
        root->ptrRight = sNode->ptrRight;
        sNode->ptrLeft = root;
        sNode->ptrRight = sRight; 
    }

    //se não for, a troca é mais complicada
    else
    {
        //faz o pai do Node apontar para o filho do root
        Node* sParent = searchParent(root, sNode);
        if(sNode->iData < sParent->iData) sParent->ptrLeft = root;
        else sParent->ptrRight = root;
        
        //troca os ponteiros Right e Left do root com o Node
        Node* sLeft = root->ptrLeft;
        Node* sRight = root->ptrRight;
        root->ptrRight = sNode->ptrRight;
        root->ptrLeft = sNode->ptrLeft;
        sNode->ptrRight = sRight;
        sNode->ptrLeft = sLeft;
    }

    return sNode;
}

// Realiza a troca e retorna o root
Node* swapTree(Node* root, Node* sNode1, Node* sNode2)
{
    //se um dos nodes for o root. chama swapRoot
    if(sNode1 == root) return swapRoot(root, sNode2);
    if(sNode2 == root) return swapRoot(root, sNode1);

    //define os ponteiros dos pais
    Node* sParent1 = searchParent(root, sNode1);
    Node* sParent2 = searchParent(root, sNode2);

    //faz os pais apontarem para seus novos filhos
    if(sNode1->iData < sParent1->iData) sParent1->ptrLeft = sNode2;
    else sParent1->ptrRight = sNode2;
    if(sNode2->iData < sParent2->iData) sParent2->ptrLeft = sNode1;
    else sParent2->ptrRight = sNode1;

    //troca os ponteiros Right e Left do Node1 com o Node2
    Node* sLeft1 = sNode1->ptrLeft;
    Node* sRight1 = sNode1->ptrRight;
    sNode1->ptrRight = sNode2->ptrRight;
    sNode1->ptrLeft = sNode2->ptrLeft;
    sNode2->ptrRight = sRight1;
    sNode2->ptrLeft = sLeft1;

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

        //Troca os nós de lugar e continua o processo para a nova arvore
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
bool isPerfect(Node* root, int iHeight, int iDepth)
{
    if(root == nullptr) return true; // Se a raíz é nula, é perfeita

    // Verifica se o nó é uma folha
    if (root -> ptrLeft == nullptr && root -> ptrRight == nullptr)
    {
        if(iHeight == iDepth + 1) return true; // Se é uma folha, verifica se seu nível é correspondente ao das outras
        return false;
    }
    
    // Se o código chega aqui, então o nó não é uma folha, logo, verifica-se a quantidade de filhos, se algum for nulo, não é perfeita
    if (root -> ptrLeft == nullptr || root -> ptrRight == nullptr) return false;
    
    // Verifica se as sub-árvores também são perfeitas, aumentando em 1 o nível atual
    if(isPerfect(root -> ptrLeft, iHeight, iDepth + 1) && isPerfect(root -> ptrRight, iHeight, iDepth + 1)) return true;
    return false;
}

Node* buildFile()
{
    clock_t start = clock();
    Node* root = nullptr;

    string strPath;
    cout << "Digite o path do arquivo: ";
    cin >> strPath;

    fstream fsFile(strPath);
    string strVal;
    while(getline(fsFile, strVal))
    {
        root = insertTree(root, stoi(strVal));
    }
    
    cout << "Árvore criada!" << endl;
    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
    return root;
}

Node* buildInput()
{
    cout << "Digite um a um os elementos da árvore" << endl;
    cout << "Digite 'N' quando tiver acabado" << endl;

    clock_t start = clock();
    Node* root = nullptr;

    while(true)
    {
        string strInput;
        cin >> strInput;

        if(strInput == "N") break;

        root = insertTree(root, stoi(strInput));
    }

    cout << "Árvore criada!" << endl;
    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
    return root;
}

Node* buildTree()
{
    cout << "Para construir uma árvore através de arquivo, digite 'file' " << endl;
    cout << "Para construir uma árvore através de input, digite 'input' " << endl;

    string strInput;
    cin >> strInput;

    if(strInput == "file")
    {
        return buildFile();
    }

    if(strInput == "input")
    {
        return buildInput();
    }

    cout << "Input inválido!" << endl;
    return buildTree();
}

void printInstruc()
{
    cout << "Instruções" << endl;
}

void altura(Node* root)
{
    clock_t start = clock();

    cout << "Altura = " << treeHeight(root) << endl;
    
    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void tamanho(Node* root)
{
    clock_t start = clock();

    cout << "Tamanho = " << treeSize(root) << endl;

    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void inserir(Node* root)
{
    int iData;
    cout << "Digite o valor a ser inserido: ";
    cin >> iData;

    clock_t start = clock();

    insertTree(root, iData);
    cout << "Nó inserido!" << endl;

    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

Node* remove(Node* root)
{
    int iData;
    cout << "Digite o valor a ser removido: ";
    cin >> iData;

    clock_t start = clock();
    Node* ptrTemp = deleteNode(root, iData, root);
    clock_t end = clock();

    cout << "Nó removido!" << endl;
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
    
    return ptrTemp;
}

void search(Node* root)
{
    int iData;
    cout << "Digite o valor que deseja encontrar o endereço: ";
    cin >> iData;

    clock_t start = clock();
    Node* ptrNode = searchNode(root, iData);
    clock_t end = clock();

    if(ptrNode == nullptr)
    {
        cout << "Valor não encontrado!" << endl;
    }
    else cout << "Endereço: " << ptrNode << endl;

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}


void completa(Node* root)
{
    clock_t start = clock();

    if(isComplete(root))
    {
        cout << "A árvore é completa";
    }
    else cout << "A árvore não é completa";
    cout << endl;

    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void perfeita(Node* root)
{
    clock_t start = clock();

    int iHeight = leftHeight(root);
    if(isPerfect(root, iHeight, 0))
    {
        cout << "A árvore é perfeita";
    }
    else cout << "A árvore não é perfeita";
    cout << endl;

    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

// Printa a lista por BFS
void print(Node* root) {
    // Enfileira o nó raiz.
    enfileirar(root);

    while(!isQueueEmpty()) 
    { 
        // Desenfileira o próximo nó.
        Node* currentNode = desenfileirar();

        // Imprime o valor do nó.
        cout << currentNode->iData << ' ';

        // Enfileira os filhos (se existirem).
        if(currentNode->ptrLeft != nullptr) {
            enfileirar(currentNode->ptrLeft);
        }

        if(currentNode->ptrRight != nullptr) {
            enfileirar(currentNode->ptrRight);
        }
    }
}

List* newList(int iData)
{
    List* ptrNewList = new List;
    ptrNewList->iPayload = iData;
    ptrNewList->ptrNext = nullptr;
    ptrNewList->ptrPrev = nullptr;

    return ptrNewList;
}

List* treeToList(Node* ptrStartingNode)
{
    if(ptrStartingNode == nullptr) return nullptr; // Se a raíz é nullptr a árvore é vazia

    List* ptrList = newList(ptrStartingNode->iData); // Cria um nó da lista com o valor da raíz
    List* ptrLeft = treeToList(ptrStartingNode->ptrLeft); // Cria uma lista com os nós da sub-árvore a esquerda
    List* ptrRight = treeToList(ptrStartingNode->ptrRight); // Cria uma lista com os nós da sub-árvore a direita

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


void menu(Node* root)
{
    printInstruc();

    while(true)
    {
        string strInput;
        cin >> strInput;

        if(strInput == "exit")
        {
            return;
        }

        if(strInput == "instructions")
        {
            printInstruc();
            continue;
        }

        if(strInput == "altura")
        {
            altura(root);
            continue;
        }

        if(strInput == "tamanho")
        {
            tamanho(root);
            continue;
        }

        if(strInput == "inserir")
        {
            inserir(root);
            continue;
        }

        if(strInput == "remove")
        {
            root = remove(root);
            cout << "Nó removido!" << endl;
            continue;
        }

        if(strInput == "search")
        {
            search(root);
            continue;
        }

        if(strInput == "completa")
        {
            completa(root);
            continue;
        }

        if(strInput == "perfeita")
        {
            perfeita(root);
            continue;
        }

        if(strInput == "print")
        {
            print(root);
            cout << endl;
            continue;
        }

        if(strInput == "bubble")
        {
            //
            continue;
        }

        if(strInput == "selection")
        {
            //
            continue;
        }

        if(strInput == "insertion")
        {
            //
            continue;
        }

        if(strInput == "shell")
        {
            //
            continue;
        }

        cout << "Input inválido! Digite 'instructions' para rever as instruções." << endl;
    }
}

int main()
{
    cout << "Bem vindo!" << endl;

    Node* root = buildTree();

    menu(root);

    cout << "Tchau!" << endl;

    return 0;
}