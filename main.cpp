    #include <iostream>
    #include <stack>

    using namespace std;

    template <typename T>
    class BTNode {
    public:
        BTNode* left, * right;
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
                root = nullptr;
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
                string ajustedExp = "(" + exp + ")";;
                createNode(ajustedExp, index);
            }

            BTNode<T>* createNode(string exp, int& index) {
                // root = nullptr;

                stack<BTNode<T>*> operatorStack;
                stack<BTNode<T>*> operandsStack;

                while (index < exp.length()) { // base case

                    if (exp[index] == '(') {
                        operandsStack.push(createNode(exp, index+=1));

                    } else if (exp[index] == ')') {

                        while (!operatorStack.empty() && getOperatorPrecedence(exp[index]) <= getOperatorPrecedence(operatorStack.top()->getData() )) {
                            BTNode<T> *newNode = new BTNode<T>(operatorStack.top()->getData());
                            operatorStack.pop();
                            newNode->right = operandsStack.top();
                            operandsStack.pop();
                            newNode->left = operandsStack.top();
                            operandsStack.pop();

                            operandsStack.push(newNode);
                        }
                        index++;
                        return operandsStack.top();

                    } else if (isOperator(exp[index])) { // Operator

                        while (!operatorStack.empty() &&
                                getOperatorPrecedence(exp[index]) <= getOperatorPrecedence(operatorStack.top()->getData())) {

                            BTNode<T> *OperatorNode = new BTNode<T>(operatorStack.top());
                            operatorStack.pop();
                            
                            OperatorNode->left = operandsStack.top();
                            operandsStack.pop();
                            OperatorNode->right = operandsStack.top();
                            operandsStack.pop();
                        }
                        // BTNode<T> *operatorNode = new BTNode<T>(exp[index]); // Assuming only single-digit operands
                        operatorStack.push(new BTNode<T>(exp[index]));
                        index++;

                    } else { // Number/Operand
                        // BTNode<T> *leafNode = new BTNode<T>(exp[index]); // Assuming only single-digit operands
                        operandsStack.push(new BTNode<T>(exp[index]));
                        index++;
                    }
                }


                root = operandsStack.top();
                return operandsStack.top();
            }

            void prefix() {
                prefix(root);
                cout << endl;
            }

            void infix() {
                infix(root);
                cout << endl;
            }
            void evalExp() {
                cout << "Result: " << evalExp(root) << endl;
            }

            /* Function for prefix traversal */
            void prefix(BTNode<T>* r) {
                if (r != nullptr) {
                    cout << static_cast<char>(r->getData()) << " ";
                    prefix(r->getLeft());
                    prefix(r->getRight());
                }
            }

            /* Function for infix traversal */
            void infix(BTNode<T>* r) {
                if (r != nullptr) {
                    infix(r->getLeft());
                    cout << static_cast<char>(r->getData()) << " ";
                    infix(r->getRight());
                }
            }

            
            /* Function to evaluate the expression */
        T evalExp(BTNode<T>* r) {
            if (r == nullptr)
                return T(); // Return default value if node is null

            // If the node is an operand (number)
            if (!isOperator(r->getData())) {
                // Convert the character to integer and return
                return r->getData() - '0';
            }
            else {
                // If the node is an operator, evaluate left and right subtrees
                T left_val = evalExp(r->getLeft());
                T right_val = evalExp(r->getRight());

                // Perform arithmetic operation based on the operator
                switch (r->getData()) {
                    case '+':
                        return left_val + right_val;
                    case '-':
                        return left_val - right_val;
                    case '*':
                        return left_val * right_val;
                    case '/':
                        // Handle division by zero
                        if (right_val == 0) {
                            cerr << "Error: Division by zero!" << endl;
                            exit(1);
                        }
                        return left_val / right_val;
                    default:
                        cerr << "Error: Invalid operator!" << endl;
                        exit(1);
                }
            }
        }


        ~BT() {
            delete root;
        }
    };


    int main() {
        
        // cout << "---- Starting ------" << endl;
        // BT<int> expTree;
        // expTree.createExp("(1+2)*3");
        // expTree.infix();
        // expTree.prefix();
        // expTree.evalExp();
        // cout << "---- Ending ------" << endl;


    cout << "------- Expression Tree Program -------" << endl;

        BT<int> expTree; // Assuming your tree works with integers

        while (true) {
            cout << "\nMenu:" << endl;
            cout << "1. Input new arithmetic expression" << endl;
            cout << "2. Display prefix form of expression" << endl;
            cout << "3. Display infix form of expression" << endl;
            cout << "4. Evaluate expression" << endl;
            cout << "5. Exit" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                string expression;
                cout << "Enter a fully parenthesized arithmetic expression: ";
                cin >> expression;
                expTree.createExp(expression);
            } else if (choice == 2) {
                expTree.prefix();
            } else if (choice == 3) {
                expTree.infix();
            } else if (choice == 4) {  
                // Assuming you've implemented evalExp() in your BT class
                cout << "Result: ";
                expTree.evalExp(); 
            } else if (choice == 5) {
                break; // Exit the loop
            } else {
                cout << "Invalid choice." << endl;
            }
        }


        
        return 0;
    }

