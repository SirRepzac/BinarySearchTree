#include <iostream>
#include "BTreeTree.h"
#include "BSTTree.h"


using namespace std;

int main()
{
    //BTreeTree t = BTreeTree();
    BSTTree t = BSTTree();

    srand(29324);

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    int delnumbers[] = {6, 5, 2, 9, 8};

    for (unsigned i = 0; i < 18; ++i)
    {
        int p = numbers[i];
        std::cout << "\n## inserting " << p << "...\n\n";
        t.Insert(p);
        cout << "Tree looks like: \n" + t.ToString() << endl;
    }
    for (unsigned i = 0; i < 5; ++i)
    {
        int p = delnumbers[i];
        std::cout << "\n## deleting " << p << "...\n\n";
        t.Delete(p);
        cout << "Tree looks like: \n" + t.ToString() << endl;
    }
}

//TODO: Make each node know how many nodes are beneath them at all times (update parents when inserting)