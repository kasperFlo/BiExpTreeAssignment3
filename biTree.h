#include <iostream>
#include "string"

using namespace std;

class BiExpTree
{

public:
    BiExpTree(){
        setRoot('A');

        set_left('B', 0);
        set_right('C', 0);

        set_left('D', 1);
        set_right('E', 1);

        set_left('1', 2);
        set_right('2', 2);

        set_left(1, 3);
        set_right(2, 3);

    };
    ~BiExpTree(){}; // Destructor

    void createExp(const string exp){
        int count = exp.length();

        for (int i = 0; i < count; i++) {
            if (isdigit(exp[i])){
                cout << i << " : " <<  exp[i] << " is a digit "<< endl;
            } else{
                cout << i << " : " <<  exp[i] << " is not a digit "<< endl;
            }

        
        }

    };
    // void infix(){};
    // void evalExp(){};

    template <class T>
    void setRoot(T key) {
        myBinaryTree[0] = key;
    }

    template <class T>
    int set_left(T key, int parent)
    {
        if (myBinaryTree[parent] == '\0') { // checks if parent is empty or not
            cout << "\nCan't set child at " << (parent * 2) + 1 << " , no parent found" << endl;
            return 0;
        }
        else {
            myBinaryTree[2 * parent + 1] = key;
            return 1;
        }
    }

    template <class T>
    int set_right(T key, int parent) {
        if (myBinaryTree[parent] == '\0') {
            cout << "\nCan't set child at "  << (parent * 2) + 1 << " , no parent found" << endl;
            return 0;
        }
        else {
            myBinaryTree[2 * parent + 2] = key;
            return 1;
        }
    }

    void printArray() {
        for (int i = 0; i < 100; i++) {
            std::cout << myBinaryTree[i] << " ";
        }
    }

    void printTree() {
        for (int i = 0; i < 100; i++) {
            if (myBinaryTree[i] != '\0') {
                std::cout << static_cast<char>(myBinaryTree[i]) << " ";
            }
        }
    }
    
private:
    int myBinaryTree[100];

    int findParent(int index){
        return ((index - 1) / 2);
    };
    int findLeftChild(int index){
        return (2 * index) + 1;
    };
    int findRightChild(int index){
        return (2 * index) + 2;
    };
};