#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>
#include "../headers/visualize.hpp"

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