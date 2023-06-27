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

Node* searchParent(Node* root, Node* sNode)
{
    if(sNode == root) return nullptr;
    if(root == nullptr) return nullptr;

    int iValue = sNode->iData;

    if(root->ptrLeft == sNode) return root;
    if(root->ptrRight == sNode) return root;

    if(iValue < root->iData) return searchParent(root->ptrLeft, sNode);
    else return searchParent(root->ptrRight, sNode);
}

Node* swapRoot(Node* root, Node* sNode)
{
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

    else
    {
        Node* sLeft = root->ptrLeft;
        Node* sRight = root->ptrRight;
        Node* sParent = searchParent(root, sNode);
        if(sNode->iData < sParent->iData) sParent->ptrLeft = root;
        else sParent->ptrRight = root;

        root->ptrRight = sNode->ptrRight;
        root->ptrLeft = sNode->ptrLeft;
        sNode->ptrRight = sRight;
        sNode->ptrLeft = sLeft;
    }

    return sNode;
}

Node* swapTree(Node* root, Node* sNode1, Node* sNode2)
{
    //realiza a troca e retorna o root
    if(sNode1 == root) return swapRoot(root, sNode2);
    if(sNode2 == root) return swapRoot(root, sNode1);

    Node* sParent1 = searchParent(root, sNode1);
    Node* sParent2 = searchParent(root, sNode2);

    if(sNode1->iData < sParent1->iData) sParent1->ptrLeft = sNode2;
    else sParent1->ptrRight = sNode2;
    if(sNode2->iData < sParent2->iData) sParent2->ptrLeft = sNode1;
    else sParent2->ptrRight = sNode1;

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

void altura(Node* root)
{
    cout << "Altura = ";
    cout << treeHeight(root);
    cout << endl;
}

void tamanho(Node* root)
{
    cout << "Tamanho = ";
    cout << treeSize(root);
    cout << endl;
}

void inserir(Node* root)
{
    cout << "Digite o valor a ser inserido: ";
    string strInput;
    cin >> strInput;
    insertTree(root, stoi(strInput));
    cout << "Nó inserido!" << endl;
}

Node* remove(Node* root)
{
    cout << "Digite o valor a ser removido: ";
    string strInput;
    cin >> strInput;
    return deleteNode(root, stoi(strInput), root);
}

void search(Node* root)
{

}

// Verifica se a árvore é completa (nenhuma folha com exatamente um nó)
bool completa(Node* root)
{
    if (root == nullptr) return true; // Se a raíz é nula, a árvore é completa

    if(root -> ptrLeft == nullptr && root -> ptrRight == nullptr) return true; // Se o nó é folha, a árvore é completa

    if(root -> ptrLeft == nullptr || root -> ptrRight == nullptr) return false; // Se o nó tem somente um filho, retorna falso, árvore não é completa

    bool bLeft = completa(root -> ptrLeft); // Flag para mostrar se a sub-árvore a esquerda é completa
    bool bRight = completa(root -> ptrRight); // Flag para mostrar se a sub-árvore a direita é completa

    return bLeft && bRight; // Retorna se as duas sub-árvores são completas
}

void perfeita(Node* root)
{

}

void print(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        print(ptrStartingNode -> ptrLeft);
        cout << " " << ptrStartingNode -> iData;
        print(ptrStartingNode -> ptrRight);
    }
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