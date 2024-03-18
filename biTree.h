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
        cout << "The expression is: " << exp << endl;

        for (int i = 0; i < count; i++)
        {
            if (isdigit(exp[i]))
            {
                // cout << "element Num " << i << " : " << exp[i] << " is a digit " << endl;
                addToLastInArray(exp[i], myBinaryTree, count);
            }
            else
            {
                // cout << i << " : " << exp[i] << " is not a digit " << endl;
                addToFirstInArray(exp[i], myBinaryTree, count);
            }
        }

        int firstNonNumber = 0;
        for (int i = count - 1; i > 0; i--)
        {
            if (!isdigit(myBinaryTree[i]))
            {
                firstNonNumber = i;
                break;
            }
        }

        reverseArrayFrom(myBinaryTree, count, firstNonNumber);
        // printTreeAsArray();
    };

    // void infix(){};
    // displays the prefix form of the expression stored in the calling myBinaryTree

    void prefix()
    {
        int root = 0;
        int size = sizeof(myBinaryTree) / sizeof(myBinaryTree[0]);
        char *prefixArray = new char[size];
        prefixStep(root, prefixArray, size);

        cout << "The prefix form of the expression is: ";
        printArray(prefixArray, size);
    };

    // void evalExp(){};

    template <class T>
    void setRoot(T key)
    {
        myBinaryTree[0] = key;
    }

    template <class T>
    int set_left(T key, int parent)
    {
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
    int set_right(T key, int parent)
    {
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

    void printTree()
    {
        cout << "Printing Binary Tree : " << endl;
        for (int i = 0; i < 100; i++) {
            if (myBinaryTree[i] != '\0') {
                std::cout << static_cast<char>(myBinaryTree[i]) << " "; 
            } else {
                break;
            }

            if (i == 0 || i == 2 || i == 6 || i == 14 || i == 30 || i == 62) {
                std::cout << std::endl;
            }
        }
        cout << endl;
    }
    void printTreeAsArray()
    {
        cout << "Printing Binary Tree As Array : " ;
        for (int i = 0; i < 100; i++)
        {
            if (myBinaryTree[i] != '\0')
            {
                std::cout << myBinaryTree[i] << " ";
            }
        }
        cout << endl;
    }

private:
    char myBinaryTree[100];

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

    void prefixStep(int root, char returnedPrefixArray[], int &sizeOfPreArray) {
        char currentChildElement = myBinaryTree[root];
        if (currentChildElement != '\0') {
            addToFirstInArray(myBinaryTree[root],returnedPrefixArray,sizeOfPreArray);
            

            prefixStep(findLeftChild(root), returnedPrefixArray, sizeOfPreArray);
            prefixStep(findRightChild(root), returnedPrefixArray, sizeOfPreArray);
        }
    }

    void addToFirstInArray(const char exp, char array[], int _size)
    {
        for (int i = 0; i < _size; i++)
        {
            if (array[i] == '\0')
            {
                array[i] = exp;
                break;
            }
        }
    }
    void addToLastInArray(const char exp, char array[], int _size)
    {
        int size = _size;

        for (int i = size - 1; i > 0; i--)
        {
            if (array[i] == '\0')
            {
                array[i] = exp;
                break;
            }
        }
    }

    void printArray(char array[], int size)
    {
        for (int i = 0; i < size; i++) {
            if (myBinaryTree[i] != '\0') {
                cout << array[i] << " ";
            }
        }
        cout << endl;
    }
    void buildTree(char array[], int size) {
        int i = 0;
        while (array[i * 2 + 1] != '\0')
        {
            if (i == 0)
            {
                setRoot(array[i]);
                set_left(array[(i * 2) + 1], findParent(i));
                set_right(array[(i * 2) + 2], findParent(i));
            }
            else
            {
                set_left(array[(i * 2) + 1], i);
                set_right(array[(i * 2) + 2], i);
            }
            i++;
        }
    }

    void reverseArrayFrom(char *arr, int size, int firstNonNumber)
    {
        int start = firstNonNumber + 1;
        int end = size - 1;

        while (start < end)
        {
            char temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
};