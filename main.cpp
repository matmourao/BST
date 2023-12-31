#include <iostream>
#include "sources/nodes.cpp"
#include "sources/queue.cpp"
#include "sources/tree.cpp"
#include "sources/visualize.cpp"
#include "sources/list.cpp"
#include "sources/menu.cpp"

using namespace std;

int main()
{
    cout << "####################################################" << endl;
    cout << "#                   BEM VINDO!                     #" << endl;
    cout << "####################################################" << endl;

    Node* root = buildTree();

    menu(root);

    cout << "Tchau!" << endl;

    return 0;
}