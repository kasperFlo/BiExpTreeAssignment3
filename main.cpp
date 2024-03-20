#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class BTNode {
public:
    BTNode<T>* left, * right;
    T data;


    /* Constructor */
    BTNode() {
        left = nullptr;
        right = nullptr;
        data = T();
    }

    explicit BTNode(BTNode<T>* node) : data(0), left(node), right(nullptr) {}

    /* Constructor */
    BTNode(T n) {
        left = nullptr;
        right = nullptr;
        data = n;
    }

    BTNode(char n) : data(n), left(nullptr), right(nullptr) {}


    /* Function to set left node */
    void setLeft(BTNode<T>* n) {
        left = n;
    }

    /* Function to set right node */
    void setRight(BTNode<T>* n) {
        right = n;
    }

    /* Function to get left node */
    BTNode<T>* getLeft() {
        return left;
    }

    /* Function to get right node */
    BTNode<T>* getRight() {
        return right;
    }

    /* Function to set data to node */
    void setData(T d) {
        data = d;
    }

    /* Function to get data from node */
    T getData() {
        return data;
    }
};

template <typename T>
class BT {
private:
        BTNode<T>* root;
        /* Function to insert data recursively */
        BTNode<T>* insert(BTNode<T>* node, T data) {
            if (node == nullptr)
                return new BTNode<T>(data);
            else {
                if (node->getRight() == nullptr)
                    node->setRight(insert(node->getRight(), data));
                else
                    node->setLeft(insert(node->getLeft(), data));
            }
            return node;
        }        /* Function to count number of nodes recursively */
        int countNodes(BTNode<T>* r) {
            if (r == nullptr)
                return 0;
            else {
                int l = 1;
                l += countNodes(r->getLeft());
                l += countNodes(r->getRight());
                return l;
            }
        }
        /* Function to search for an element recursively */
        bool search(BTNode<T>* r, T val) {
            if (r->getData() == val)
                return true;
            if (r->getLeft() != nullptr)
                if (search(r->getLeft(), val))
                    return true;
            if (r->getRight() != nullptr)
                if (search(r->getRight(), val))
                    return true;
            return false;
        }
        /* Function for inorder traversal */
        void inorder(BTNode<T>* r) {
            if (r != nullptr) {
                inorder(r->getLeft());
                cout << r->getData() << " ";
                inorder(r->getRight());
            }
        }
        /* Function for preorder traversal */
        void preorder(BTNode<T>* r) {
            if (r != nullptr) {
                cout << r->getData() << " ";
                preorder(r->getLeft());
                preorder(r->getRight());
            }
        }
        /* Function for postorder traversal */
        void postorder(BTNode<T>* r) {
            if (r != nullptr) {
                postorder(r->getLeft());
                postorder(r->getRight());
                cout << r->getData() << " ";
            }
        }
        /* Recursive function to calculate height of the tree */
        int recHeight(BTNode<T>* r) {
            if (r == nullptr)
                return 0;
            else
                return max(recHeight(r->getLeft()), recHeight(r->getRight())) + 1;
        }

    public:
        /* Constructor */
        BT() {
            root;
        }
        /* Function to check if tree is empty */
        bool isEmpty() {
            return root == nullptr;
        }
        /* Functions to insert data */
        void insert(T data) {
            root = insert(root, data);
        }
        /* Function to count number of nodes */
        int countNodes() {
            return countNodes(root);
        }
        /* Function to search for an element */
        bool search(T val) {
            return search(root, val);
        }
        /* Function for inorder traversal */
        void inorder() {
            inorder(root);
            cout << endl;
        }
        /* Function for preorder traversal */
        void preorder() {
            preorder(root);
            cout << endl;
        }
        /* Function for postorder traversal */
        void postorder() {
            postorder(root);
            cout << endl;
        }
        /* Function to calculate height of the tree */
        int height() {
            return recHeight(root);
        }
        int getOperatorPrecedence(char op) {
            switch(op) {
                case '+': 
                case '-': return 1;
                case '*': 
                case '/': return 2;
                default: return 0; // For invalid operators (handling this is important)
            }
        }

        int isOperator(char c) {
            return (c == '+' || c == '-' || c == '*' || c == '/');
        }

        void createExp(string exp) {
            int index = 0;
            BTNode<T>* expRoot = createNode(exp, index);
            root = expRoot;
        }

        BTNode<T>* createNode(string exp, int& index) {
            stack<BTNode<T>*> *operatorStack = new stack<BTNode<T>*>();
            stack<BTNode<T>*> *operandsStack = new stack<BTNode<T>*>();

            while (index < exp.length()) { // base case

                if (exp[index] == '(') {
                    // BTNode<T> *subTreeRoute = createNode(exp, index+=1);
                    operandsStack->push(createNode(exp, index+=1));

                } else if (exp[index] == ')') {

                    while (!operatorStack->empty() && getOperatorPrecedence(exp[index]) <= getOperatorPrecedence(operatorStack->top()->getData() )) {
                        BTNode<T> *newNode = new BTNode<T>(operatorStack->top()->getData());
                        operatorStack->pop();
                        newNode->right = operandsStack->top();
                        operandsStack->pop();
                        newNode->left = operandsStack->top();
                        operandsStack->pop();

                        operandsStack->push(newNode);
                        return newNode;
                    }
                    index++;

                } else if (isOperator(exp[index])) { // Operator

                    while (!operatorStack->empty() && 
                            getOperatorPrecedence(exp[index]) <= getOperatorPrecedence(operatorStack->top()->getData())) {

                        BTNode<T> *OperatorNode = new BTNode<T>(operatorStack->top());
                        operatorStack->pop();
                        
                        OperatorNode->left = operandsStack->top();
                        operandsStack->pop();
                        OperatorNode->right = operandsStack->top();
                        operandsStack->pop();
                    }
                    // BTNode<T> *operatorNode = new BTNode<T>(exp[index]); // Assuming only single-digit operands
                    operatorStack->push(new BTNode<T>(exp[index]));
                    index++;

                } else { // Number/Operand
                    // BTNode<T> *leafNode = new BTNode<T>(exp[index]); // Assuming only single-digit operands
                    operandsStack->push(new BTNode<T>(exp[index]));
                    index++;
                }
            }
            BTNode<T>* toBeReturnedTreeNode = new BTNode<T>();
            toBeReturnedTreeNode = operandsStack->top();
            operandsStack->pop();
            return toBeReturnedTreeNode;
        }

        void prefix(){}
        void infix(){}
        void evalExp(){}

    ~BT() {
        delete root;
    }
};


int main() {
    cout << "---- Starting ------" << endl;
    BT<int> expTree;

    expTree.createExp("((1+2)*(3*6))");

    
    return 0;
}

