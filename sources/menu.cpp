#include <iostream>
#include <fstream>
#include <time.h>
#include "../headers/menu.hpp"

using namespace std;

Node* buildFile()
{
    clock_t start = clock();
    Node* root = nullptr;

    string strFile;
    cout << "Digite o nome do arquivo localizado na pasta 'arvores': ";
    cin >> strFile;
    string strPath = "arvores/" + strFile;

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
        cout << "Valor não encontrado!";
    }
    else cout << "Endereço: " << ptrNode;
    cout << endl;

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

    int iLevel = leftHeight(root) + 1;
    if(isPerfect(root, iLevel, 0))
    {
        cout << "A árvore é perfeita";
    }
    else cout << "A árvore não é perfeita";
    cout << endl;

    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void print(struct Node* root)
{
    clock_t start = clock();

    BFS(root);
    cout << endl;
    
    clock_t end = clock();
    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void bubble(Node* root)
{
    clock_t start = clock();

    List* head = treeToList(root);
    bubbleSort(&head);
    printList(head);

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void selection(Node* root)
{
    clock_t start = clock();

    List* head = treeToList(root);
    selectionSort(&head);
    printList(head);

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void insertion(Node* root)
{
    clock_t start = clock();
    
    List* head = treeToList(root);
    insertionSort(&head);
    printList(head);

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void shell(Node* root)
{
    clock_t start = clock();

    List* head = treeToList(root);
    shellSort(&head);
    printList(head);

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
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
            continue;
        }

        if(strInput == "bubble")
        {
            bubble(root);
            continue;
        }

        if(strInput == "selection")
        {
            selection(root);
            continue;
        }

        if(strInput == "insertion")
        {
            insertion(root);
            continue;
        }

        if(strInput == "shell")
        {
            shell(root);
            continue;
        }

        cout << "Input inválido! Digite 'instructions' para rever as instruções." << endl;
    }
}