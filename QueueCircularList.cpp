/* Implementation of Queue using Circular List
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
*/

#include <bits/stdc++.h>

using namespace std;

class Node
{
    string info;
    Node* next;

    public:

        // A constructor
        Node(const string& info = "")
        {
            this->info = info;
            next = NULL;
        }

        friend class CLL;
};

class CLL
{
    Node* cursor;

    public:

        // A constructor
        CLL()
        {
            cursor = NULL;
        }

        // A destructor
        ~CLL()
        {
            while(!empty())
                removeFront();
        }

        // Displays the list
        void display();

        // Returns the front element in the list
        const string& front() const;

        // Returns if the list is empty or not
        bool empty() const;

        // Adds an element in the back of the list
        void addBack(const string&);

        // Removes an element from the front of the list
        void removeFront();
};

void CLL :: display()
{
    if(empty())
    {
        cout << "List is empty!!!";
        return;
    }

    Node* ptr = cursor->next;

    do
    {
        cout << ptr->info << "  ";
        ptr = ptr->next;

    } while (ptr != cursor->next);
    
}

bool CLL :: empty() const
{
    return cursor == NULL;
}

const string& CLL :: front() const
{
    return cursor->next->info;
}

void CLL :: addBack(const string& info)
{
    Node* newNode = new Node(info);

    if(empty())
    {
        cursor = newNode;
        cursor->next = cursor;
        return;
    }

    newNode->next = cursor->next;
    cursor->next = newNode;
    cursor = newNode;
}

void CLL :: removeFront()
{
    Node* old = cursor->next;

    if(old == cursor)
    {
        cursor = NULL;
        return;
    }

    cursor->next = old->next;
    delete old;
}

class Queue
{
    private:
        CLL list;
        int noOfElements;

    public:
        
        // A constructor
        Queue() : list(), noOfElements(0) {}

        // Returns the size of Queue
        int size() const;

        // Displays the queue
        void display();

        // Returns true if the queue is empty
        bool empty() const;

        // Returns front element of the queue
        const string& front() const;

        // Pushes an element in the back of the queue
        void push(const string& element);

        // Pops an element from the front of the queue
        void pop();
};

int Queue :: size() const
{
    return noOfElements;
}

void Queue :: display() 
{
    list.display();
}

bool Queue :: empty() const
{
    return noOfElements == 0;
}

const string& Queue :: front() const
{
    if(empty())
        throw "Empty list!!!";

    return list.front();
}

void Queue :: push(const string& element)
{
    list.addBack(element);
    noOfElements++;
}

void Queue :: pop()
{
    if(empty())
        throw "Empty list!!!";

    list.removeFront();
    noOfElements--;
}

int main()
{
    int maxElements, size;
    string queueElements;
    Queue myQueue;

    try
    {

        cout << "Enter the number of elements in Queue: ";
        cin >> size;

        cout << "Enter the elements to push in the Queue...\n";
        for(int iterate = 0; iterate < size; ++iterate)
        {
            cin >> queueElements;
            myQueue.push(queueElements); 
        }

        system("cls");

        cout << "\nQueue :: ";
        myQueue.display();

        cout << "\nFront Element of the Queue: " << myQueue.front();

        cout << "\nPopping the element from Queue...\n";
        myQueue.pop();
        cout << "Queue :: ";
        myQueue.display();

    } 
    catch(const int& exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}