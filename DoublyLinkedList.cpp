/* A  program to implement doubly linked list
Name:  Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No: 19HCS4048
*/

#include <iostream>
#include <string>

using namespace std;

class Node
{
    string info;
    Node* previous;
    Node* next;

    public: 

        // A constructor
        Node(const string& element = "")
        {
            info = element;
            previous = NULL;
            next = NULL;
        }

        friend class DLL;
};

class DLL
{
    Node* header;
    Node* trailer;

    public: 

        // A constructor
        DLL()
        {
            header = new Node();
            trailer = new Node();

            header->next = trailer;
            trailer->previous = header;
        }

        // A destructor
        ~DLL()
        {
            Node *ptr = header->next, *old;
            while(ptr != trailer)
            {
                old = ptr;
                ptr = ptr->next;

                delete old;
            }

            delete header;
            delete trailer;
        }

        // Returns if the list is empty or not
        bool empty();

        // Displays the list
        void display();

        // Adds an element in the front of DLL
        void addFront(const string&);

        // Adds an element at a position in DLL
        void addElement(const string&, int);

        // Adds an element at the back of DLL
        void addBack(const string&);

        // Removes an element from the beginning of DLL
        void removeFront();

        // Removes an element from a position in DLL
        void removeElement(int);

        // Removes an element from the back of DLL
        void removeBack();

        // Searches an element and return its pointer
        Node* search(const string&);

        // Concatenates two DLL
        void concatenate(DLL&);
};

bool DLL :: empty()
{
    return header->next == trailer;
}

void DLL :: display()
{
    for(Node* ptr = header->next; ptr != trailer; ptr = ptr->next)
        cout << ptr->info << "  ";
}

void DLL :: addFront(const string& info)
{
    Node* newNode = new Node(info);

    newNode->previous = header;
    newNode->next = header->next;

    header->next->previous = newNode;
    header->next = newNode;
}

void DLL :: addElement(const string& info, int position)
{
    if(position == 0)
        throw "Invalid Position!!!";

    Node* newNode = new Node(info);

    Node* ptr = header->next;
    int count = 0;

    while(ptr != NULL && count < position - 1)
    {
        count++;
        ptr = ptr->next;
    }

    if(ptr == NULL)
        throw "Invalid Position!!!";

    newNode->next = ptr;
    newNode->previous = ptr->previous;

    ptr->previous->next = newNode;
    ptr->previous = newNode;
}

void DLL :: addBack(const string& info)
{
    Node* newNode = new Node(info);

    newNode->next = trailer;
    newNode->previous = trailer->previous;

    trailer->previous->next = newNode;
    trailer->previous = newNode;
}

void DLL :: removeFront()
{
    Node* old = header->next;

    header->next = old->next;
    old->next->previous = header;

    delete old;
}

void DLL :: removeElement(int position)
{
    if(position == 0)
        throw "Invalid Position!!!";

    int count = 0;
    Node* old = header->next;

    while(old != NULL && count < position - 1)
    {
        count++;
        old = old->next;
    }

    if(old == NULL)
        throw "Invalid Position!!!";

    old->previous->next = old->next;
    old->next->previous = old->previous;

    delete old;
}

void DLL :: removeBack()
{
    Node* old = trailer->previous;

    trailer->previous = old->previous;
    old->previous->next = trailer;

    delete old;
}

Node* DLL :: search(const string& info)
{
    if(empty())
        return NULL;
    
    Node* ptr = header->next;

    while(ptr != trailer)
    {
        if(ptr->info == info)
            return ptr;

        ptr = ptr->next;
    }

    return NULL;
}

void DLL :: concatenate(DLL& list)
{
    if(empty())
    {
        header->next = list.header->next;
        return;
    }

    if(list.empty())
        return;

    trailer->previous->next = list.header->next;
    trailer->previous = list.trailer->previous;

    delete list.header;
    delete list.trailer;
}

int main()
{
    int size, position;
    string listElement;

    DLL firstList, secondList;

    try
    {
        cout << "Enter the size of first List: ";
        cin >> size;

        cout << "Enter the element in first list..." << endl; 
        for(int index = 0; index < size; ++index)
        {
            cin >> listElement;
            firstList.addBack(listElement);
        }

        system("cls");

        cout << "Original List:: ";
        firstList.display();

        cout << "\n\nEnter the element to add in the front of the list: ";
        cin >> listElement;
        firstList.addFront(listElement);
        cout << "New List:: ";
        firstList.display();

        cout << "\n\nEnter the element to add in the end of the list: ";
        cin >> listElement;
        firstList.addBack(listElement);
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

        cout << "\n\nRemoval of element from the end of the list..." << endl;
        firstList.removeBack();
        cout << "New list:: ";
        firstList.display();

        cout << "\n\nEnter the position to remove an element from: ";
        cin >> position;
        firstList.removeElement(position);
        cout << "New List:: ";
        firstList.display();

        cout << "\n\nEnter the element to be searched: ";
        cin >> listElement;
        Node* searchResult = firstList.search(listElement);
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
            secondList.addBack(listElement);
        }
        firstList.concatenate(secondList);

        cout << "\nNew List:: ";
        firstList.display();
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}