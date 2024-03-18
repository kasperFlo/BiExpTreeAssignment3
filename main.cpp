#include <iostream>
#include "biTree.h" // Include the header file that defines the BiExpTree class

using namespace std;

int main() {
    cout << "---- Starting ------" << endl;

    BiExpTree *thing = new BiExpTree(); // Create a pointer to BiExpTree object
    
    thing->createExp("3+4*5*6+7");

    thing->printTree();
    thing->printTreeAsArray();

    thing->prefix();

    return 0;
}

