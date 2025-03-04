#include <iostream>
#include "BTreeTree.h"
#include "BSTTree.h"


using namespace std;

int main()
{
    //BTreeTree t = BTreeTree();
    BSTTree t = BSTTree();

    srand(29324);

    int numbers[] = {4, 7, 6, 8, 9, 1, 2, 5, 3};

    for (unsigned i = 0; i < 9; ++i)
    {
        int p = numbers[i];
        std::cout << "\n## inserting " << p << "...\n\n";
        t.Insert(p);
        cout << "Tree looks like: \n" + t.ToString() << endl;
    }
    t.Delete(6);
    cout << "Tree looks like: \n" + t.ToString() << endl;
}
