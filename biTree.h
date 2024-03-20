#include <iostream>
#include <stack>

using namespace std;

class BiExpTree
{

public:
    BiExpTree() {
        for (int i = 0; i < 100; i++) {
            myBinaryTree[i] = '\0';
        }
    }
    ~BiExpTree() {} 

    void createExp(const string exp) {
        stack<char> operatorStack;
        int count = exp.length();
        int indexForInsertion = 0; 

        for (int i = 0; i < count; i++) {
            char element = exp[i]; 

            if (isdigit(element)) {
                myBinaryTree[indexForInsertion] = element;
                indexForInsertion++;
            } else if (element == '(') {
                operatorStack.push(element);
            } else if (element == ')') {
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    addOperator(operatorStack.top(), indexForInsertion);  
                    operatorStack.pop();
                }
                operatorStack.pop(); 
            } else { 
                while (!operatorStack.empty() && 
                    getOperatorPrecedence(element) <= getOperatorPrecedence(operatorStack.top())) {
                    addOperator(operatorStack.top(), indexForInsertion); 
                    operatorStack.pop();
                }
                operatorStack.push(element);
            }
        }

        // while (!operatorStack.empty()) {
        //     addOperator(operatorStack.top(), indexForInsertion); 
        //     operatorStack.pop();
        // }
    }

    void prefix() {
        cout << "The prefix form of the expression is: ";
        printArray(myBinaryTree, 100);
    }

    void infix() {
        cout << "The infix form of the expression is: ";
        infixStep(0); 
        cout << endl;
    }

    int evalExp() {
        int result = evalExpRecursive(0); 
        cout << "The result of the expression is: " << result << endl;
        return result;
    }
    
    void printTree() {
        cout << "The tree is: " << endl;
        printArray(myBinaryTree, 100);
    }
    
private:
    char myBinaryTree[100];

    int findParent(int index) { return ((index - 1) / 2); }
    int findLeftChild(int index) { return (2 * index) + 1; }
    int findRightChild(int index) { return (2 * index) + 2; }

    int getOperatorPrecedence(char op) {
        switch(op) {
            case '+':
            case '-': return 1; 
            case '*': 
            case '/': return 2;
            default: return 0;  
        }
    }

    void addOperator(char op, int &indexForInsertion) {
        // Handle potential array overflow (add logic here if needed)

        // Special Case: If the array is mostly empty, build the tree normally
        if (indexForInsertion < 3) { 
            myBinaryTree[indexForInsertion] = op;
            indexForInsertion++;
            return;
        }

        // Shifting Strategy
        int targetIndex = indexForInsertion - 2; // Aim to place operator as parent

        // Shift operands if necessary
        if (myBinaryTree[targetIndex] != '\0') {
            shiftRightUntilEmpty(targetIndex); 
        }

        myBinaryTree[targetIndex] = op;
        indexForInsertion++;  
    }

    void shiftSubtreeRight(int subtreeRootIndex) {
        if (myBinaryTree[subtreeRootIndex] == '\0') {
            return;  
        } 

        int rightChildIndex = findRightChild(subtreeRootIndex);
        if (myBinaryTree[rightChildIndex] != '\0') {
            shiftSubtreeRight(rightChildIndex); 
        }

        for (int i = subtreeRootIndex; i < 100 - 1; i++) {
            if (myBinaryTree[i] == '\0') break;
            myBinaryTree[i + 1] = myBinaryTree[i];
        }
    }

    void printArray(char array[], int size) {
        for (int i = 0; i < size; i++) {
            if (array[i] != '\0') {
                cout << array[i] << " ";
            } 
        }
        cout << endl;
    } 

    int evalExpRecursive(int root) {
        char element = myBinaryTree[root];

        if (element == '\0') {
            return 0;  
        }
        if (isdigit(element)) {
            return element - '0'; 
        }

        int leftResult = evalExpRecursive(findLeftChild(root));
        int rightResult = evalExpRecursive(findRightChild(root));

        switch (element) {
            case '+':
                return leftResult + rightResult;
            case '-':
                return leftResult - rightResult;
            case '*':
                return leftResult * rightResult;
            case '/':
                return leftResult / rightResult;
            default: 
                return 0; 
        }
    }

    void shiftRightUntilEmpty(int startIndex) {
    int currentIndex = startIndex;
    while (myBinaryTree[currentIndex] != '\0') {
        int rightChild = findRightChild(currentIndex);
        if (myBinaryTree[rightChild] != '\0') {
            shiftRightUntilEmpty(rightChild);
        }
        for (int i = currentIndex; i < 99; i++) { 
            if (myBinaryTree[i] == '\0') break;
            myBinaryTree[i + 1] = myBinaryTree[i];
        }
        currentIndex = rightChild; // Continue shifting the rightmost nodes 
    }
}
    // void infixStep(int root) {
    //     if (myBinaryTree[root] == '\0') {
    //         return;
    //     }
    //     infixStep(findLeftChild(root)); 
    //     cout << myBinaryTree[root];  // Print the operator
    //     infixStep(findRightChild(root)); 
    // }

    // void infixStep(int root) {
    //     if (myBinaryTree[root] == '\0') {
    //         return;
    //     }

    //     int leftChildIndex = findLeftChild(root);
    //     int rightChildIndex = findRightChild(root);

    //     // Handle potential missing left operand
    //     if (isdigit(myBinaryTree[root]) && myBinaryTree[leftChildIndex] == '\0') {
    //         cout << myBinaryTree[root];  // Print the single operand
    //     } else { 
    //         if (myBinaryTree[leftChildIndex] != '\0') {
    //             cout << "(";  
    //             infixStep(leftChildIndex); 
    //         }

    //         cout << myBinaryTree[root];  // Print the operator

    //         if (myBinaryTree[rightChildIndex] != '\0') {
    //             infixStep(rightChildIndex); 
    //             cout << ")"; 
    //         }
    //     }
    // }
   
};
