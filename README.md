# BST
## Descrição do projeto:

Projeto desenvolvido para a disciplina de Estrutura de Dados do curso de Matemática Aplicada e Ciência de Dados. O BST, como o nome sugere, possibilita a criação e manipulação de árvores binárias de busca (Binary Search Tree).

A interação do usuário com o sistema é possibilitada através de um menu ASCII.

## Código e desenvolvimento:

Todo o trabalho foi desenvolvido em notação húngara para melhor entendimento e organização do código.

O código é dividido em diferentes módulos, que podem ser encontrados na pasta [headers](headers).

### Menu:
O módulo [menu](headers/menu.hpp) inclui todas as funções que serão utilizadas para criar a interface gráfica e para responder as requisições feitas pelo usuário.

- Na pasta [sources](sources), podemos encontrar o arquivo [menu.cpp](sources/menu.cpp) onde as funções do menu estão realmente desenvolvidas.

### Tree:
O módulo [tree.hpp](headers/tree.hpp) abrange todas as funções que dizem respeito a uma árvore binária de busca, desde a inserção de nós para sua criação, feita através de um arquivo .txt ou a partir de dados inseridos pelo próprio usuário, até funções de pesquisa ou informação.

- Os arquivos .txt, para a criação de BST’s, estão disponíveis na pasta [arvores](arvores), além da representação gráfica das árvores construídas a partir deles. Os elementos a serem adicionados à árvore devem estar dispostos um em cada linha do arquivo .txt.

- Mais uma vez, o código de desenvolvimento pode ser encontrado em [sources](sources), no arquivo [tree.cpp](sources/tree.cpp). Nele se encontram funções que verificam se a árvore é perfeita ou se está completa, qual é sua altura ou tamanha, e que inserem, deletam ou buscam elementos.

### Queue:
O módulo [queue.hpp](headers/queue.hpp) inclui as funções de fila, desenvolvidas no arquivo [queue.cpp](sources/queue.cpp) e utilizadas como auxiliares na criação da visualização gráfica das árvores. Uma biblioteca pronta poderia ter sido utilizada, mas optamos pelo desenvolvimento das nossas próprias funções.

### List:
O módulo [list.hpp](headers/list.hpp), por sua vez, apresenta todas as funções relacionadas a listas duplamente encadeadas. Uma dessas funções (treeToList) transforma uma árvore em uma lista. Assim, é possível aplicar diversos métodos de ordenação a lista criada. Entre os métodos desenvolvidos nesse projeto estão: Bubble Sort, Selection Sort, Insertion Sort e Shell Sort.
	
- O desenvolvimento dos algoritmos de ordenamento e outras funções relacionadas a listas duplamente encadeadas podem ser encontrados em [list.cpp](sources/list.cpp).

### Visualize:
O módulo [visualize.hpp](headers/visualize.hpp) inclui as funções de visualização desenvolvidas em [visualize.cpp](sources/visualize.cpp). Através delas, foram incluídas representações gráficas para os algoritmos de ordenação citados anteriormente.

### Main:
Finalmente, através do arquivo [main.cpp](main.cpp) podemos executar todo o código.
Na pasta [output](output) estão os arquivos .exe.

## Checklist objetivos:
- [x] Menu ASCII: [menu.hpp](headers/menu.hpp) e [menu.cpp](sources/menu.cpp)
- [x] Tempo de processamento: clock() no começo e no fim de cada função
- [x] Construção de BST por .txt: buildFile() em [menu.cpp](sources/menu.cpp)
- [x] Construção de BST por usário: buildInput() em [menu.cpp](sources/menu.cpp)
- [x] Altura da árvore: treeHeight() em [tree.cpp](sources/tree.cpp)
- [x] Tamanho da árvore: treeSize() em [tree.cpp](sources/tree.cpp)
- [x] Inserção de elemento por usuário: insertTree() em [tree.cpp](sources/tree.cpp)
- [x] Remoção de elemento por usuário: deleteNode() em [tree.cpp](sources/tree.cpp)
- [x] Busca de elemento por usuário: searchNode() em [tree.cpp](sources/tree.cpp)
- [x] Árvore completa: isComplete em [tree.cpp](sources/tree.cpp)
- [x] Árvore perfeita: isPerfect() em [tree.cpp](sources/tree.cpp)
- [x] Visualização da árvore: BFS() em [tree.cpp](sources/tree.cpp)
- [x] Conversão da árvore em lista: treeToList em [list.cpp](sources/list.cpp)
- [x] Bubble Sort: bubbleSort em [list.cpp](sources/list.cpp)
- [x] Selection Sort: selectionSort em [list.cpp](sources/list.cpp)
- [x] Insertion Sort: insertionSort em [list.cpp](sources/list.cpp)
- [x] Shell Sort: shellSort em [list.cpp](sources/list.cpp)
- [x] Representação gráfica das ordenações: [visualize.hpp](visualize/visualize.hpp) e [visualize.cpp](sources/visualize.cpp)

## Desenvolvedores:

O trabalho foi desenvolvido pelos alunos: [Guilherme Queiroz](https://github.com/guilhermeqcl), [Luana Hatab](https://github.com/luanahatab), [Luiza Schneider](https://github.com/luizasch2) e [Mateus Mourão](https://github.com/matmourao).

