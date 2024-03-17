#include <iostream>
#include "string"

using namespace std;

class BiExpTree
{

public:
    BiExpTree(){

        // setRoot('A');

        // set_left('B', 0);
        // set_right('C', 0);

        // set_left('D', 1);
        // set_right('E', 1);

        // set_left('1', 2);
        // set_right('2', 2);

        // set_left(1, 3);
        // set_right(2, 3);

    };
    ~BiExpTree(){}; // Destructor

    void createExp(const string exp)
    {

        int count = exp.length();
        cout << "The length of the expression is: " << count << endl;

        char *devidedArray = new char[count];

        for (int i = 0; i < count; i++) {
            if (isdigit(exp[i])) {
                cout << "element Num " << i << " : " << exp[i] << " is a digit " << endl;
                addToLastInArray(exp[i], devidedArray, count);
            }
            else {
                cout << i << " : " << exp[i] << " is not a digit " << endl;
                addToFirstInArray(exp[i], devidedArray,count);
            }
            cout << "---\nThe devided array is: ";
            printArray(devidedArray, count);
        }
        
        cout << "building tree" << endl;
        buildTree(devidedArray, count);
    };

    // void infix(){};
    // void evalExp(){};

    template <class T>
    void setRoot(T key) {
        myBinaryTree[0] = key;
    }

    template <class T>
    int set_left(T key, int parent) {
        if (myBinaryTree[parent] == '\0')
        { // checks if parent is empty or not
            cout << "\nCan't set child at " << (parent * 2) + 1 << " , no parent found" << endl;
            return 0;
        }
        else
        {
            myBinaryTree[2 * parent + 1] = key;
            return 1;
        }
    }

    template <class T>
    int set_right(T key, int parent) {
        if (myBinaryTree[parent] == '\0')
        {
            cout << "\nCan't set child at " << (parent * 2) + 1 << " , no parent found" << endl;
            return 0;
        }
        else
        {
            myBinaryTree[2 * parent + 2] = key;
            return 1;
        }
    }

    void printTree() {
        for (int i = 0; i < 100; i++)
        {
            if (myBinaryTree[i] != '\0') {
                std::cout << static_cast<char>(myBinaryTree[i]) << " ";
            }
            if (i == 0 || i == 2 || i == 6 || i == 14 || i == 30 || i == 62) {
                std::cout << std::endl;
            }
        }
    }

private:
    int myBinaryTree[100];

    int findParent(int index)
    {
        return ((index - 1) / 2);
    };
    int findLeftChild(int index)
    {
        return (2 * index) + 1;
    };
    int findRightChild(int index)
    {
        return (2 * index) + 2;
    };

    void addToFirstInArray(const char exp, char array[],int _size)
    {
        if (array[0] == '\0') {
            array[0] = exp;
        }
        else {
            for (int i = 0; i < _size; i++) {
                if (array[i] == '\0') {
                    array[i] = exp;
                    break;
                }
            }
        }
    }
    void addToLastInArray(const char exp, char array[], int _size)
    {
        int size = _size;

        for (int i = size - 1; i > 0; i--) {
            if (array[i] == '\0') {
                array[i] = exp;
                break;
            }
        }
    }

    void printArray(char array[], int size) {
        for (int i = 0; i < size; i++) {
            cout << array[i] << ",";
        }
        cout<<endl;
    }

    void buildTree(char array[], int size) {
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                setRoot(array[i]);
            }

            else {
                if (i % 2 == 0) {
                    set_right(array[i], findParent(i));
                }
                else {
                    set_left(array[i], findParent(i));
                }
            }
        }
    }

};