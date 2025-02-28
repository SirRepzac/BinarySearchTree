#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    Node node = Node();
    int k[2] = { 1, 2 };
    node.SetValues(k);
    cout << node.ToString() << endl;
}
