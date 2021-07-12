// Program to implement linked list with two pointers head and tail
/* Name: Shivam Verma
   Course: B.Sc.(H) Computer Science 3rd Semester
   Roll No: 19HCS4048
*/

#include <iostream>
#include <string>

using namespace std;

class Node
{
    string element;
    Node* next;

    public:

    // A default Constructor
    Node() {}

    // A constructor to initialise element
    Node(const string& element)
    {
        this->element = element;
        this->next = NULL;
    }

    // A constructor to initialise the instance variable
    Node(const string& element, Node* next)
    {
        this->element = element;
        this->next = next;
    }

    // Declaring DoubleLinkedList as its friend class
    friend class LinkedList;
};

class LinkedList
{
    Node *head, *tail;

    public:

        // A Default Constructor
        LinkedList()
        {
            head = tail = NULL;
        }

        // A destructor
        ~LinkedList()
        {
            while(head != NULL)
            {
                Node* old = head;
                head = head->next;
                delete old;
            }
        } 

        // Function to count nodes of the list
        int countNodes();

        // Function to add element in the front of the list
        void addFront(const string& element);

        // Function to add element in the end of the list
        void addTail(const string& element);

        // Function to add element at a given position
        void addElement(const string& element, int position);

        // Function to remove element from the front of the list
        void removeFront();

        // Function to remove element from the end of the list
        void removeTail();

        // Function to remove element from a given position
        void removeElement(int position);

        // Function to search an element in the list
        Node* searchElement(const string& element);

        // Function to concatenate two lists
        void concatenate(LinkedList& list);

        // Function to output the list
        void output(ostream& out);

        // Overloaded operator to print the list
        friend ostream& operator<< (ostream& out, LinkedList& list);

        // Function to reverse a list
        void reverse();
};

int LinkedList :: countNodes()
{
    Node* ptr = head;
    int count = 0;

    while(ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }

    return count;
}

void LinkedList :: addFront(const string& element)
{
    Node* newNode = new Node(element);

    if(head == NULL)
        head = tail = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

void LinkedList :: addTail(const string& element)
{
    Node* newNode = new Node(element);

    if(head == NULL)
    {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void LinkedList :: addElement(const string& element, int position)
{
    Node* newNode = new Node(element);
    Node* ptr = head;

    if(position == 1)
    {
        newNode->next = head;
        head = newNode;
        tail = newNode;
        return;
    }

    int count = 1;

    while(ptr != NULL && count < position - 1)
    {
        ptr = ptr->next;
        count++;
    }

    if(ptr == NULL)
        throw "Invalid Position!!!";
    
    newNode->next = ptr->next;
    ptr->next = newNode;

    if(ptr == tail)
        tail = newNode;
}

void LinkedList :: removeFront()
{
    if(head == NULL)
        throw "Empty list!!!";
    
    Node* old = head;
    head = head->next;
    delete old;
}

void LinkedList :: removeTail()
{
    if(tail == NULL)
        throw "Empty list!!!";

    Node *ptr = head, *old = tail;
    for(ptr = head; ptr->next != tail; ptr = ptr->next);

    tail = ptr;
    tail->next = NULL;
    delete old;
}

void LinkedList :: removeElement(int position)
{
    Node* old;

    if(position == 1)
    {
        removeFront();
        return;
    }

    int count = 1;
    Node* ptr = head;

    while(ptr != NULL && count < position - 1)
    {
        ptr = ptr->next;
        count++;
    }

    if(ptr == NULL)
        throw "Invalid Position!!!";
    
    old = ptr->next;
    ptr->next = old->next;
    
    if(old == tail)
        tail = ptr;

    delete old;
}

Node* LinkedList :: searchElement(const string& element)
{
    if(head == NULL)
        return NULL;

    Node* ptr = head;

    while(ptr != NULL)
    {
        if(ptr->element == element)
            return ptr;

        ptr = ptr->next;
    }

    return NULL;
}

void LinkedList :: concatenate(LinkedList& list)
{
    if(head == NULL)
    {
        head = list.head;
        return;
    }

    if(list.head == NULL)
        return;

    tail->next = list.head;
    list.head = NULL;
}

void LinkedList :: output(ostream& out)
{
    for(Node* ptr = head; ptr != NULL; ptr = ptr->next)
        out << ptr->element << "  ";
}

ostream& operator<< (ostream& out, LinkedList& list)
{
    list.output(out);
    return out;
}

void LinkedList :: reverse()
{
    if(head == NULL)
        throw "Empty list, can't be reversed!!!";

    Node *ptr1, *ptr2, *ptr3;
    ptr1 = head;
    ptr2 = head->next;

    if(ptr2 == NULL)
        return;
    
    while(ptr2 != NULL)
    {
        ptr3 = ptr2->next;
        ptr2->next = ptr1;
        ptr1 = ptr2;
        ptr2 = ptr3;
    }

    head->next = NULL;
    tail = head;
    head = ptr1;
}


int main()
{
    int size, position;
    string listElement;

    LinkedList firstList, secondList;

    try
    {
        cout << "Enter the size of first List: ";
        cin >> size;

        cout << "Enter the element in first list..." << endl; 
        for(int index = 0; index < size; ++index)
        {
            cin >> listElement;
            firstList.addElement(listElement, index + 1);
        }

        system("cls");

        cout << "Original List:: ";
        cout << firstList;

        cout << "\nNumber of nodes: ";
        cout << firstList.countNodes();

        cout << "\n\nEnter the element to add in the front of the list: ";
        cin >> listElement;
        firstList.addFront(listElement);
        cout << "New List:: ";
        cout << firstList;

        cout << "\n\nEnter the element to add in the end of the list: ";
        cin >> listElement;
        firstList.addTail(listElement);
        cout << "New List:: ";
        cout << firstList; 

        cout << "\n\nEnter the position to insert an element in the list: ";
        cin >> position;
        cout << "Enter the element to insert: ";
        cin >> listElement;
        firstList.addElement(listElement, position);
        cout << "New list:: ";
        cout << firstList;

        cout << "\n\nRemoval of element from the beginning of the list..." << endl;
        firstList.removeFront();
        cout << "New list:: ";
        cout << firstList;

        cout << "\n\nRemoval of element from the end of the list..." << endl;
        firstList.removeTail();
        cout << "New list:: ";
        cout << firstList;

        cout << "\n\nEnter the position to remove an element from: ";
        cin >> position;
        firstList.removeElement(position);
        cout << "New List:: ";
        cout << firstList;

        cout << "\n\nEnter the element to be searched: ";
        cin >> listElement;
        Node* searchResult = firstList.searchElement(listElement);
        if(searchResult == NULL)
            cout << "Element is not found!!!";
        else
            cout << "Element is found in the list.";

        cout << "\n\nEnter the size of secondList: ";
        cin >> size;
        cout << "Enter the elements in the second list..." << endl;
        for(int index = 0; index < size; ++index)
        {
            cin >> listElement;
            secondList.addElement(listElement, index + 1);
        }
        firstList.concatenate(secondList);

        cout << "\nNew List:: ";
        cout << firstList;

        cout << "\n\nReversed list:: ";
        firstList.reverse();
        cout << firstList;
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}