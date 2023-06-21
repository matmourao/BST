#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int iData;
    Node* ptrLeft;
    Node* ptrRight;
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

Node* buildFile()
{
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

Node* deleteNode(struct Node* sNode, int iValue)
{
    // Se o nó é nulo, não tem o que remover
    if(sNode == nullptr) return sNode;

    // Procura o nó a ser removido
    if(iValue < sNode -> iData) sNode -> ptrLeft = deleteNode(sNode -> ptrLeft, iValue);
    else if(iValue > sNode -> iData) sNode -> ptrRight = deleteNode(sNode -> ptrRight, iValue);

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

        /***************************************************
        Parte temporária:
        Troca o valor do nó, o ideal é trocar os nós em si, mas a função já funciona do jeito que tá
        ****************************************************/
        sNode -> iData = ptrTemp -> iData;

        sNode -> ptrRight = deleteNode(sNode -> ptrRight, ptrTemp -> iData);
    }

    return sNode;
}

Node* buildInput()
{
    cout << "Digite um a um os elementos da árvore" << endl;
    cout << "Digite 'N' quando tiver acabado" << endl;

    Node* root = nullptr;

    while(true)
    {
        string strInput;
        cin >> strInput;

        if(strInput == "N") break;

        root = insertTree(root, stoi(strInput));
    }

    cout << "Árvore criada!" << endl;
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
            //
            continue;
        }

        if(strInput == "tamanho")
        {
            //
            continue;
        }

        if(strInput == "insert")
        {
            //
            continue;
        }

        if(strInput == "remove")
        {
            //
            continue;
        }

        if(strInput == "search")
        {
            //
            continue;
        }

        if(strInput == "completa")
        {
            //
            continue;
        }

        if(strInput == "perfeita")
        {
            //
            continue;
        }

        if(strInput == "print")
        {
            //
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