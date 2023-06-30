#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include "../headers/visualize.hpp"
#include <unistd.h>

using namespace std;

// Função para calcular o número de dígitos de um número
int numDigits(int iNumber)
{
    int iDigits = 0;

    while(iNumber)
    {
        iNumber /= 10;
        iDigits++;
    }

    return iDigits;
}

// Função para calcular o número de hashtags para cada valor na lista vinculada
// Seria mais fácil apenas colocar um número de hashtags correspondente ao número do nó, mas, 
// para números muito grandes, isso dificultaria a visualização
map<int, int> calculateHashes(List* sNode)
{
    // Cria um vetor para armazenar os valores dos nós
    vector<int> viValues;
    List* ptrTemp = sNode;

    // Percorre a lista vinculada e adicionar os valores ao vetor
    while(ptrTemp != nullptr)
    {
        viValues.push_back(ptrTemp -> iData);
        ptrTemp = ptrTemp -> ptrNext;
    }

    // Ordena o vetor em ordem crescente
    sort(viValues.begin(), viValues.end());

    // Cria um mapa para armazenar o valor e o número de hashtags correspondente
    map<int, int> miHashes;

    // Atribui o número de hashtags para cada valor
    for(vector<int>::size_type i = 0; i < viValues.size(); ++i)
    {
        miHashes[viValues[i]] = i + 1;
    }

    return miHashes;
}

void displayList(struct List* sNode)
{
    // Calcule o número de hashtags para cada valor
    map<int, int> miHashes = calculateHashes(sNode);

    int iMaxValue = 0;
    int iMaxDigits = 0;

    // Encontra o valor máximo no mapa de hashes
    // Fazemos isso para que nunca tenhamos barras verticais desalinhadas com os números
    for(auto& pair : miHashes)
    {
        if(pair.second > iMaxValue)
            iMaxValue = pair.second;

        int iDigits = numDigits(pair.first);

        if(iDigits > iMaxDigits)
            iMaxDigits = iDigits;
    }

    // Imprime as barras
    for(int iHeight = iMaxValue; iHeight >= 1; --iHeight)
    {
        List* ptrTemp1 = sNode;
        while(ptrTemp1 != nullptr)
        {
            if(miHashes[ptrTemp1 -> iData] >= iHeight) 
            {
                cout << string(iMaxDigits, '#') + " ";
            }
            else 
            {
                cout << string(iMaxDigits, ' ') + " ";
            }

            ptrTemp1 = ptrTemp1 -> ptrNext;
        }
        cout << endl;
    }

    // Imprime os números
    List* ptrTemp2 = sNode;
    while(ptrTemp2 != nullptr)
    {
        cout << setw(iMaxDigits) << ptrTemp2 -> iData << ' ';
        ptrTemp2 = ptrTemp2 -> ptrNext;
    }
    cout << endl;

    // Espera por um segundo e apaga 
    sleep(1);

   system("clear||cls");
}