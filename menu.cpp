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