/* Implementation of Postfix Expression using Stack
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
*/

#include <iostream>
#include <ctype.h>
#include <math.h>
#include <string>

using namespace std;

template <class T>
class Node
{
    T element;
    Node* next;

    public:

        // A constructor
        Node(const T& element = NULL, Node* next = NULL) : element(element), next(next) {}

        // Friend class declaration
        template <class U>
        friend class Stack;
};

template <class T>
class Stack
{
    Node<T> *top;
    Node<T> *head;
    int noOfElements;

    public:

        // A constructor
        Stack() : top(NULL), head(NULL), noOfElements(0) {}

        // Displays the Stack
        void display() const;

        // Returns true if Stack is empty
        bool empty() const;

        // Returns the top element of Stack
        const T& topElement() const throw();

        // Pushes the element in the Stack
        void push(const T& element);

        // Pops the element from the Stack
        void pop() throw();
};

template <class T>
void Stack<T> :: display() const
{
    if(empty())
    {
        cout << "Stack is empty!!!";
        return;
    }

    Node<T> *ptr = head;
    while(ptr != NULL)
    {
        cout << ptr->element << "  ";
        ptr = ptr->next;
    }

    cout << endl;
}

template <class T>
bool Stack<T> :: empty() const
{
    return noOfElements == 0;
}

template <class T>
const T& Stack<T> :: topElement() const throw()
{
    if(empty())
        throw "No top element, Stack is empty!!!";

    return top->element;
}

template <class T>
void Stack<T> :: push(const T& element)
{
    Node<T> *newNode = new Node<T>(element);

    if(empty())
    {
        top = head = newNode;
        noOfElements++;
        return;
    }

    top->next = newNode;
    top = newNode;

    noOfElements++;
}

template <class T>
void Stack<T> :: pop() throw()
{
    if(empty())
        throw "Can't pop, Stack is empty!!!";

    if(top == head)
    {
        delete top;
        top = NULL;
        head = NULL;
        noOfElements--;
        return;
    }

    Node<T> *ptr = NULL;
    for(ptr = head; ptr->next != top; ptr = ptr->next);

    delete top;
    top = ptr;
    top->next = NULL;
    noOfElements--;
}

// Returns the precedence for a given operator
int precedence(char op)
{
    if(op == '^')
        return 3;

    else if(op == '*' || op == '/')
        return 2;

    else if(op == '+' || op == '-')
        return 1;

    return -1;
}

// Converts infix to postfix expression
string infixToPostfix(const string& infixExp)
{
    Stack<char> myStack;
    myStack.push('N');

    string postfixExp;

    for(int index = 0; index < infixExp.length(); ++index)
    {
        if((infixExp[index] >= '0' && infixExp[index] <= '9') || (infixExp[index] >= 'a' && infixExp[index] <= 'z') || (infixExp[index] >= 'A' && infixExp[index] <= 'Z'))
            postfixExp += infixExp[index];

        else if(infixExp[index] == '(')
            myStack.push('(');

        else if(infixExp[index] == ')')
        {
            while(myStack.topElement() != 'N' && myStack.topElement() != '(')
            {
                char c = myStack.topElement();
                postfixExp += c;
                myStack.pop();
            }
            if(myStack.topElement() == '(')
                myStack.pop();
        }

        else
        {
            while(myStack.topElement() != 'N' && precedence(infixExp[index]) <= precedence(myStack.topElement()))
            {
                char c = myStack.topElement();
                postfixExp += c;
                myStack.pop();
            }

            myStack.push(infixExp[index]);
        }
    }

    while(myStack.topElement() != 'N')
    {
        char c = myStack.topElement();
        postfixExp += c;
        myStack.pop();
    }

    return postfixExp;
}

// Evaluates the Postfix Expression
int evaluate(const char* postfix)
{
    Stack<int> myStack;

    for(int index = 0; postfix[index]; ++index)
    {
        if(postfix[index] == ' ')
            continue;

        else if(isdigit(postfix[index]))
            myStack.push(postfix[index] - '0');

        else
        {
            int value2 = myStack.topElement();
            myStack.pop();
            int value1 = myStack.topElement();
            myStack.pop();

            switch(postfix[index])
            {
                case '+': myStack.push(value1 + value2);
                          break;
                case '-': myStack.push(value1 - value2);
                          break;
                case '*': myStack.push(value1 * value2);
                          break;
                case '/': myStack.push(value1 / value2);
                          break;
                case '^': myStack.push(pow(value1, value2));
                          break;
            }
        }
    }

    return myStack.topElement();
}

int main()
{
    string infix, postfix;
    int result;

    try
    {
        cout << "Enter the Infix Expression: ";
        cin >> infix;

        postfix = infixToPostfix(infix);

        cout << "\nPostfix Expression:: " << postfix;

        result = evaluate(postfix.c_str());

        cout << "\n\nEvaluated Result:: " << result;

    }
    catch(const string& error)
    {
        cerr << error << '\n';
    }
    
    return 0;
}
