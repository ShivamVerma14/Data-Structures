/* A program implementing circular linked list
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No: 19HCS4048
*/

#include <iostream>

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
                removeBack();
        }

        // Displays the list
        void display();

        // Returns if the list is empty or not
        bool empty() const;

        // Adds an element in front of the list
        void addFront(const string&);

        // Adds an element after an element in the list
        void addElement(const string&, const string&);

        // Adds an element in the back of the list
        void addBack(const string&);

        // Removes an element from the back of the list
        void removeBack();

        // Removes an element from the front of the list
        void removeFront();

        // Removes an element from the list
        void removeElement(const string&);

        // Searches for an element in the list
        Node* search(const string&);

        // Concatenates two list
        void concatenate(CLL&);
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

void CLL :: addFront(const string& info)
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
}

void CLL :: addElement(const string& info, const string& element)
{
    Node* ptr = cursor->next;

    do
    {
        if(ptr->info == element)
        {
            Node* newNode = new Node(info);

            newNode->next = ptr->next;
            ptr->next = newNode;

            if(ptr == cursor)
                cursor = newNode;

            return;
        }

        ptr = ptr->next;

    }while (ptr != cursor->next);

    cout << element << " is not present in the list!!!\n";
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

void CLL :: removeBack()
{
    Node* old = cursor->next;

    if(old == cursor)
    {
        cursor = NULL;
        return;
    }

    while(old->next != cursor)
        old = old->next;

    old->next = cursor->next;
    delete cursor;
    cursor = old;
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

void CLL :: removeElement(const string& element)
{
    Node* previousElement = cursor->next, *old;

    do
    {
        if(previousElement->next->info == element)
        {
            old = previousElement->next;

            previousElement->next = old->next;

            if(old == cursor)
                cursor = previousElement;

            delete old;

            return;
        }

        previousElement = previousElement->next;

    } while (previousElement != cursor->next);
    
    cout << element << " is not fond in the list!!!";
}

Node* CLL :: search(const string& element)
{
    if(empty())
        return NULL;

    Node* ptr = cursor->next;

    do
    {
        if(ptr->info == element)
            return ptr;

        ptr = ptr->next;
        
    } while (ptr != cursor->next);

    return NULL;    
}

void CLL :: concatenate(CLL& list)
{
    if(empty())
    {
        cursor = list.cursor;
        list.cursor = NULL;
        return;
    }

    if(list.empty())
        return;

    Node* temp = list.cursor->next;
    list.cursor->next = cursor->next;
    cursor->next = temp;

    cursor = list.cursor;
    list.cursor = NULL;
}

int main()
{
    int size;
    string listElement, element;

    CLL firstList, secondList;

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

        cout << "\n\nEnter the element after which new element to be inserted in the list: ";
        cin >> element;
        cout << "Enter the element to insert: ";
        cin >> listElement;
        firstList.addElement(listElement, element);
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

        cout << "\n\nEnter the element to remove from the list: ";
        cin >> element;
        firstList.removeElement(element);
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