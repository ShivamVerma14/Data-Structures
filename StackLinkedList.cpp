/* Implementation of Stacks using linked list
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Sem
Roll No.: 19HCS4048
*/

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class StackEmpty : public exception
{
    string message;

    public:

        // A constructor
        StackEmpty(const string& error = NULL)
        {
            message = error;
        }

        // Overriding what()
        const char* what() const noexcept
        {
            return message.c_str();
        } 
};

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

        // Returns the size of the Stack
        int size() const;

        // Returns true if Stack is empty
        bool empty() const;

        // Returns the top element of the Stack
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
int Stack<T> :: size() const
{
    return noOfElements;
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
        throw StackEmpty("No top element, Stack is empty!!!");

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
        throw StackEmpty("Can't pop, Stack is empty!!!");

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

int main()
{
    int size;
    string element;

    try
    {
        cout << "Enter the size of Stack: ";
        cin >> size;

        Stack<string> myStack;

        cout << "Enter the elements to push in the Stack...\n";
        for(int iterate = 0; iterate < size; ++iterate)
        {
            cin >> element;
            myStack.push(element);
        }

        system("cls");

        cout << "Stack:: ";
        myStack.display();

        cout << "Element at the top of the Stack:: " << myStack.topElement();

        cout << "\nPopping an element from the Stack...\n";
        myStack.pop();

        cout << "New Stack:: ";
        myStack.display();

    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return 0;
}