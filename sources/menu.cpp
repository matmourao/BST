#include <iostream>
#include <fstream>
#include <time.h>
#include "../headers/menu.hpp"

using namespace std;

Node* buildFile()
{
    clock_t start = clock();
    Node* root = nullptr; // Inicializa o root com nullptr

    // Salva o arquivo .txt:
    string strFile;
    cout << "Digite o nome do arquivo (com a extenção) localizado na pasta 'arvores': (fileName.txt)" << endl;
    cin >> strFile;
    string strPath = "arvores/" + strFile;

    fstream fsFile(strPath);
    string strVal;

    while(getline(fsFile, strVal))
    {
        root = insertTree(root, stoi(strVal)); // Insere o valor de cada linha do arquivo na arvore
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
    Node* root = nullptr; // Inicializa o root com nullptr

    while(true)
    {
        // Salva o input
        string strInput;
        cin >> strInput;

        if(strInput == "N") break; // Indica quando acabaram os elementos

        root = insertTree(root, stoi(strInput)); // Adiciona o valor do input na arvore
    }

    cout << "Árvore criada!" << endl;

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;

    return root;
}

// Chama as funcoes buildFile ou buildInput, dependendo do input recebido
Node* buildTree()
{
    cout << "===========================================" << endl;
    cout << "              MENU DE OPÇÕES               " << endl;
    cout << "===========================================" << endl;
    cout << "| Para construir uma árvore através de   |" << endl;
    cout << "| arquivo, digite 'file'                 |" << endl;
    cout << "| Para construir uma árvore através de   |" << endl;
    cout << "| input, digite 'input'                  |" << endl;
    cout << "===========================================" << endl;

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

// Imprime o valor retornado por treeHeight(root)
void altura(Node* root)
{
    clock_t start = clock();

    cout << "Altura = " << treeHeight(root) << endl;
    
    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

// Imprime o valor retornado por treeSize(root)
void tamanho(Node* root)
{
    clock_t start = clock();

    cout << "Tamanho = " << treeSize(root) << endl;

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

// Chama a funcao insertTree com o root dado e o valor recebido por input
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

// Chama a funcao deleteNode com o root dado e o valor recebido por input 
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


// Imprime o endereço do elemento a ser buscado
void search(Node* root)
{
    // Salva o valor do elemento, recebido por input
    int iData;
    cout << "Digite o valor que deseja encontrar o endereço: ";
    cin >> iData;

    clock_t start = clock();
    Node* ptrNode = searchNode(root, iData); // atribui a ptrNode o ponteiro retornado
    clock_t end = clock();

    if(ptrNode == nullptr)
    {
        cout << "Valor não encontrado!"; // Se for nullptr, imprime "Valor não encontrado!" 
    }
    else cout << "Endereço: " << ptrNode; // Se não for, imprime o endereço do elemento
    cout << endl; // Quebra a linha

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

// Imprime se a árvore é completa ou não, dependendo do retorno da funcao isComplete
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

// Imprime se a árvore é perfeita ou não, dependendo do retorno da funcao isPerfect
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

    List* head = treeToList(root); // Atribui a árvore convertida em lista a head
    bubbleSort(&head); // Chama a bubbleSort com essa lista
    printList(head); // Imprime a lista ordenada

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void selection(Node* root)
{
    clock_t start = clock();

    List* head = treeToList(root); // Atribui a árvore convertida em lista a head
    selectionSort(&head); // Chama a selectionSort com essa lista
    printList(head); // Imprime a lista ordenada

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void insertion(Node* root)
{
    clock_t start = clock();
    
    List* head = treeToList(root); // Atribui a árvore convertida em lista a head
    insertionSort(&head); // Chama a insertionSort com essa lista
    printList(head); // Imprime a lista ordenada

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

void shell(Node* root)
{
    clock_t start = clock();

    List* head = treeToList(root); // Atribui a árvore convertida em lista a head
    shellSort(&head); // Chama a shellSort com essa lista
    printList(head); // Imprime a lista ordenada

    clock_t end = clock();

    double elapsed = double(end - start)/double(CLOCKS_PER_SEC);
    cout << "Tempo levado: " << elapsed << " seg" << endl;
}

// Imprime as intrucoes
void printInstruc()
{
    cout << "####################################################" << endl;
    cout << "#                    INSTRUÇÕES                    #" << endl;
    cout << "####################################################" << endl;
    cout << "# Digite 'altura' para ver a altura da árvore;     #" << endl;
    cout << "# Digite 'tamanho' para ver o tamanho da árvore;   #" << endl;
    cout << "# Digite 'inserir' para inserir um novo nó;        #" << endl;
    cout << "# Digite 'remove' para remover um nó da árvore;    #" << endl;
    cout << "# Digite 'search' para buscar um elemento;         #" << endl;
    cout << "# Digite 'completa' para saber se é completa;      #" << endl;
    cout << "# Digite 'perfeita' para saber se é perfeita;      #" << endl;
    cout << "# Digite 'print' para exibir a árvore (BFS);       #" << endl;
    cout << "# Digite 'bubble' para ordenar com Bubble Sort;    #" << endl;
    cout << "# Digite 'selection' para ordenar com Selection;   #" << endl;
    cout << "# Digite 'insertion' para ordenar com Insertion;   #" << endl;
    cout << "# Digite 'shell' para ordenar com Shell Sort;      #" << endl;
    cout << "# Digite 'exit' para sair do programa.             #" << endl;
    cout << "####################################################" << endl;
}

void menu(Node* root)
{
    printInstruc(); // Imprime as intrucoes na primeira vez que for chamada

    while(true)
    {
        // A cada loop, imprime o input para rever as intrucoes
        cout << "Digite 'instructions' para rever as instruções" << endl;
        string strInput;
        cin >> strInput;
        system("clear||cls"); // Depois do input ser dado, apaga o que foi printado antes

        // Chama cada funcao relativa ao input dado e continua para o proximo loop:

        if(strInput == "exit")
        {
            return; // Para sair do menu, da return, encerrando a funcao
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

        // Se nao entrou em nenhum if, informa que o input é invalido e continua o loop
        cout << "Input inválido!" << endl;
    }
}