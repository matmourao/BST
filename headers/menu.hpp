#ifndef MENU_HPP
#define MENU_HPP

#include "tree.hpp"
#include "queue.hpp"
#include "list.hpp"

Node* buildFile();
Node* buildInput();
Node* buildTree();
void printInstruc();
void altura(Node* root);
void tamanho(Node* root);
void inserir(Node* root);
Node* remove(Node* root);
void search(Node* root);
void completa(Node* root);
void perfeita(Node* root);
void print(Node* root);
void bubble(Node* root);
void selection(Node* root);
void insertion(Node* root);
void shell(Node* root);
void menu(Node* root);

#endif