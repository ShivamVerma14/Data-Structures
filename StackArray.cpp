/* Implementation of Stack using Array
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

class StackFull : public exception
{
    string message;

    public:

        // A constructor
        StackFull(const string& error = NULL)
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
class Stack
{
    T* array;
    int capacity;
    int top;

    public:

        // A constructor
        Stack(int capacity = 0) : array(new T[capacity]), capacity(capacity), top(-1) {}

        // A destructor
        ~Stack()
        {
            delete[] array;
        }

        // Displays the Stack
        void display() const;

        // Returns the size of the Stack
        int size() const;

        // Returns true if Stack is empty
        bool empty() const;

        // Returns the top element of the Stack
        const T& topElement() const throw();

        // Pushes the element in the Stack
        void push(const T& element) throw();

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

    for(int index = 0; index <= top; ++index)
        cout << array[index] << "  ";

    cout << endl;
}

template <class T>
int Stack<T> :: size() const
{
    return top + 1;
}

template <class T>
bool Stack<T> :: empty() const
{
    return top < 0;
}

template <class T>
const T& Stack<T> :: topElement() const throw()
{
    if(empty())
        throw StackEmpty("Stack is empty!!!");

    return array[top];
}

template <class T>
void Stack<T> :: push(const T& element) throw()
{
    if(size() == capacity)
        throw StackFull("Stack is full!!!");

    array[++top] = element;
}

template <class T>
void Stack<T> :: pop() throw()
{
    if(empty())
        throw StackEmpty("Stack is empty!!!");

    --top;
}

int main()
{
    int capacity, size;

    try
    {
        cout << "Enter the capacity of the Stack: ";
        cin >> capacity;

        Stack<string> myStack(capacity);
        string element;

        cout << "Enter the size of the Stack: ";
        cin >> size;

        cout << "Enter the element to push in the Stack...\n";
        for(int iterate = 0; iterate < size; ++iterate)
        {
            cin >> element;
            myStack.push(element);
        }

        system("cls");

        cout << "Stack:: ";
        myStack.display();

        cout << "Element at the top of the Stack: " << myStack.topElement();

        cout << "\nPopping an element from the top of the Stack...\n";
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
