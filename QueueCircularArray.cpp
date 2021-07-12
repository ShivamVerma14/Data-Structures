/* Implementation of Queue using Circular Array
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
*/

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Queue
{
    int front;
    int rear;
    int noOfElements;
    int capacity;
    T* array;

    public:

        // A constructor
        Queue(int capacity = 0)
        {
            front = rear = 0;
            noOfElements = 0;

            this->capacity = capacity;
            array = new T[capacity];
        }

        // A destructor
        ~Queue()
        {
            delete[] array;
        }

        // Displays the queue
        void display() const;

        // Returns the size of the queue
        int size() const;

        // Returns true if queue is empty
        bool empty() const;

        // Returns the front element in the queue
        const T& frontElement() const;

        // Pushes the element in the queue
        void push(const T& element);

        // Pops the element from the queue
        void pop();
};

template <class T>
void Queue<T> :: display() const
{
    if(empty())
    {
        cout << "Queue is empty!!!\n";
        return;
    }

    if(rear > front)
        for(int index = front; index < rear; ++index)
            cout << array[index] << "  ";

    else
    {
        for(int index = front; index < capacity; ++index)
            cout << array[index] << "  ";

        for(int index = 0; index < rear; ++index)
            cout << array[index] << "  ";
    }

    cout << endl;
} 

template <class T>
int Queue<T> :: size() const
{
    return noOfElements;
}

template <class T>
bool Queue<T> :: empty() const
{
    return noOfElements == 0;
}

template <class T>
const T& Queue<T> :: frontElement() const
{
    if(empty())
        throw "Empty Queue!!!";

    return array[front];
}

template <class T>
void Queue<T> :: push(const T& element)
{
    if(size() == capacity)
        throw "Queue is full!!!";

    array[rear] = element;
    rear = (rear + 1) % capacity;

    noOfElements++;
}

template <class T>
void Queue<T> :: pop()
{
    if(empty())
        throw "Empty Queue!!!";

    front = (front + 1) % capacity;
    noOfElements--;
}

int main()
{
    int capacity, size;

    try
    {
        cout << "Enter the capacity of the Queue: ";
        cin >> capacity;

        Queue<string> myQueue(capacity);
        string elements;

        cout << "Enter the size of the Queue: ";
        cin >> size;

        cout << "Enter the elements to push in the Queue...\n";
        for(int iterate = 0; iterate < size; ++iterate)
        {
            cin >> elements;
            myQueue.push(elements);
        }

        system("cls");

        cout << "Queue:: ";
        myQueue.display();

        cout << "Front Element of the Queue: " << myQueue.frontElement();

        cout << "\nPopping an element from the Queue...\n";
        myQueue.pop();

        cout << "New Queue:: ";
        myQueue.display();

    }
    catch(const string& exception)
    {
        cerr << exception << '\n';
    }
    
    return 0;
}