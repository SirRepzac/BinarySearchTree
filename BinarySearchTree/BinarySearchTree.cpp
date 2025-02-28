#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    Node node = Node();
    node.SetValues(1, 2, 3);
    cout << node.ToString() << endl;
}
