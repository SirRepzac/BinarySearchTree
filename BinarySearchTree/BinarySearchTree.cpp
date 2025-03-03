#include <iostream>
#include "Tree.h"


using namespace std;

int main()
{
    Tree t = Tree();

    srand(29324);

    for (unsigned i = 0; i < 15; ++i)
    {
        int p = rand() % 100;
        std::cout << "\n## inserting " << p << "...\n\n";
        t.Insert(p);
    }

    //std::cout << "Hello World!\n";
    //Tree tree = Tree();
    //tree.Insert(1);
    //tree.Insert(6);
    //tree.Insert(3);
    //tree.Insert(5);
    //tree.Insert(7);
    //tree.Insert(2);
    //tree.Insert(9);
    //tree.Insert(11);
    //tree.Insert(4);
    //tree.Insert(8);
    //tree.Insert(13);
    //tree.Insert(12);
    //tree.Insert(14);
    //tree.Insert(15);
    //cout << endl;
    //cout << "-----" << endl;
    //cout << endl;

    //cout << tree.ToString() << endl;
}
