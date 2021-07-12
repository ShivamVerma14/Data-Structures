/* Implementation of singly linked list

Name: Shivam Verma
Course: B.Sc. (H) Computer Science 3rd Sem
Roll No: 19HCS4048
*/

#include <iostream>
#include <string>

using namespace std;

// Class to represent a single node
class Node
{
    private:
        string element;
        Node* next;

    public:

        // A default constructor
        Node() {}

        // Constructor to initialise element
        Node(const string& element)
        {
            this->element = element;
            this->next = NULL;
        }

        // Constructor to initialise the data members
        Node(const string& element, Node* next)
        {
            this->element = element;
            this->next = next;
        }

        // Declaring the friend class LinkedList
        friend class LinkedList;
};

// A class to represent the list
class LinkedList
{
    private:
        Node* head;

    public:

        // Default Constructor
        LinkedList()
        {
            head = NULL;
        }    

        // Function to display the list
        void display()
        {
            Node* ptr = head;

            while(ptr != NULL)
            {
                cout << ptr->element << "  ";
                ptr = ptr->next;
            }
        }  

        // Function to add an element in front of the list
        void addFront(string element);

        // Function to add an element at x position of the list
        void addElement(string element, int position);

        // Function to remove an element from the front of the list
        void removeFront();

        // Function to remove an element from x position of the list
        void removeElement(int position);

        // Function to search an element in the list
        Node* searchElement(string element);

        // Friend function to concatenate two LinkedLists
        LinkedList concatenate(LinkedList& secondList);
};

void LinkedList :: addFront(string element)
{
    Node* newNode = new Node(element);

    if(head == NULL)
        head = newNode;
    else
    {
        newNode->next = head;
        head = newNode;
    }   
}

void LinkedList :: addElement(string element, int position)
{
    Node* newNode = new Node(element);
    Node* ptr = head;

    if(position == 1)
    {
        newNode->next = head;
        head = newNode;
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
}

void LinkedList :: removeFront()
{
    Node* old = head;
    head = head->next;
    delete old;
}

void LinkedList :: removeElement(int position)
{
    Node *old;

    if(position == 1)
    {
        old = head;
        head = head->next;
        delete old;

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
    delete old;
}

Node* LinkedList :: searchElement(string element)
{
    Node* ptr = head;

    while(ptr != NULL)
    {
        if(ptr->element == element)
            return ptr;

        ptr = ptr->next;
    }

    return NULL;
}

LinkedList LinkedList :: concatenate(LinkedList& secondList)
{
    LinkedList concatList;

    if(head == NULL)
    {
        concatList.head = secondList.head;
        return concatList;
    }

    concatList.head = head;

    if(secondList.head == NULL)
        return concatList;
    
    Node* ptr = head;
    while(ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = secondList.head;

    return concatList;
}

int main()
{
    int size, position;
    string listElement;

    LinkedList firstList, secondList, concatList;

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
        firstList.display();

        cout << "\n\nEnter the element to add in front of the list: ";
        cin >> listElement;
        firstList.addFront(listElement);
        cout << "New List:: ";
        firstList.display();

        cout << "\n\nEnter the position to insert an element in the list: ";
        cin >> position;
        cout << "Enter the element to insert: ";
        cin >> listElement;
        firstList.addElement(listElement, position);
        cout << "New list:: ";
        firstList.display();

        cout << "\n\nRemoval of element from the beginning of the list..." << endl;
        firstList.removeFront();
        cout << "New list:: ";
        firstList.display();

        cout << "\n\nEnter the position to remove an element from: ";
        cin >> position;
        firstList.removeElement(position);
        cout << "New List:: ";
        firstList.display();

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
        concatList = firstList.concatenate(secondList);

        cout << "\n\nNew List:: ";
        concatList.display();
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}