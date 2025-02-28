#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    //Node node = Node();
    //int k[2] = { 1, 2 };
    //node.SetValues(k);

    Tree tree = Tree();
    tree.Insert(1);
    tree.Insert(6);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(2);
    tree.Insert(9);
    tree.Insert(11);
    tree.Insert(4);
    // currently looks like 
    //              [6, 0]
    //    [3, 0]            [9, 0]
    // [1, 2] [4, 5]    [7, 9]

    // should look like
    //             [6, 0]
    //    [3, 0]            [9, 0]
    // [1, 2] [4, 5]    [7, 0]  [11, 0]

    // split didnt find right parent
    cout << endl;
    cout << "-----" << endl;
    cout << endl;

    cout << tree.ToString() << endl;
}
