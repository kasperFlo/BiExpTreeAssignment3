void createExp(string exp){
            int index = 0;
            
            stack<BTNode<T>*> operatorStack; 
            stack<BTNode<T>*> operandsStack; 

            BTNode<T>* root = createNode(exp, index, operatorStack, operandsStack);
        }
        
        BTNode<T>* createNode (string exp, int &index, stack<BTNode<T>*> operatorStack, stack<BTNode<T>*> operandsStack){
            if (index >= exp.length()){ // base case
                return nullptr;
            } else if (exp[index] == '(') { 
                index ++;
                BTNode<T>* subTreeRoute = createNode(exp, index, operatorStack, operandsStack);
                return subTreeRoute;
            } else if (exp[index] == ')') {
               
                while (!operatorStack.empty() && getOperatorPrecedence(exp[index]) <= getOperatorPrecedence(operatorStack.top()->getData()))
                {
                    BTNode<T>* newNode = new BTNode<T>(operatorStack.top());
                    operatorStack.pop();
                    newNode->left = operandsStack.top();
                    operandsStack.pop();
                    newNode->right = operandsStack.top();
                    operandsStack.pop();
                }
                index ++;
                
            }
            else if ( isOperator(exp[index])) { // Operator

                while (!operatorStack.empty() && getOperatorPrecedence(exp[index]) <= getOperatorPrecedence(operatorStack.top()->getData()))
                {
                    BTNode<T>* OperatorNode = new BTNode<T>(operatorStack.top());
                    OperatorNode->left = operandsStack.top();
                    operandsStack.pop();

                    OperatorNode->right = operandsStack.top();
                    operandsStack.pop();
                }
                operatorStack.push(exp[index]);
                index++;
            
                // return OperatorNode;
            } 
            else { // Number/Operand   
                BTNode<T>* leafNode = new BTNode<T>(exp[index]); // Assuming only single-digit operands
                index++;
                operandsStack.push(leafNode);
                // return leafNode; //might not be necessary
            }
        }