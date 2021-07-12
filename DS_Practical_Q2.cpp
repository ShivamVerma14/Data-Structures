/* Data Structures Practical Q2. Sorted Linked List
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
University Roll No.: 19015570031
*/

#include <iostream>

using namespace std;

template <class T>
class Node
{
    T data;
    Node *next, *previous;

    public:
        // A parameterized constructor
        Node(const T& element = NULL) : data(element), next(NULL), previous(NULL) {}

        template <class U>
        friend class SortedLinkedList;
};

template <class T>
class SortedLinkedList
{
    Node<T> *head, *tail;

    public:
        // A constructor
        SortedLinkedList() : head(NULL), tail(NULL) {}

        // A destructor
        ~SortedLinkedList()
        {
            Node<T> *pointer = head, *old;
            while(pointer != NULL)
            {
                old = pointer;
                pointer = pointer->next;

                delete old;
            }
        }

        // Displays the Sorted Linked List
        void display()
        {
            Node<T> *node = head;
            display(node);
        }

        // Inserts an element in the Sorted Linked List
        void insert(const T&);

        // Deletes an element from the Sorted Linked List
        void delete_from_list(const T&);

    protected:
        void display(Node<T>*);
};

template <class T>
void SortedLinkedList<T> :: display(Node<T> *node)
{
    if(node == NULL)
        return;

    cout << node->data << " ";
    display(node->next);
}

template <class T>
void SortedLinkedList<T> :: insert(const T& element)
{
    Node<T> *newNode = new Node<T>(element);

    if(head == NULL)
    {
        head = tail = newNode;
        return;
    }

    if(element <= head->data)
    {
        head->previous = newNode;
        newNode->next = head;
        head = newNode;
        return;
    }

    Node<T> *pointer = head;

    while(pointer->next != NULL && element > pointer->next->data)
        pointer = pointer->next;

    newNode->previous = pointer;
    newNode->next = pointer->next;
    if(pointer->next != NULL)
        pointer->next->previous = newNode;
    pointer->next = newNode;

    if(pointer == tail)
        tail = newNode;
}

template <class T>
void SortedLinkedList<T> :: delete_from_list(const T& element)
{
    Node<T> *pointer = head;

    if(head->data == element)
    {
        head = head->next;
        delete pointer;
        return;
    }

    while(pointer->next != NULL && element > pointer->next->data)
        pointer = pointer->next;

    if(pointer->next->data != element || (pointer == tail && pointer->data != element))
        throw "Element to be deleted is not in the list!!!";

    Node<T> *old = pointer->next;
    
    pointer->next = old->next;
    if(old != tail)
        old->next->previous = pointer;

    if(old == tail)
        tail = old->previous;
    delete old;
}

int main()
{
    int element, size;
    SortedLinkedList<int> myList;

    try
    {
        cout << "Enter the number of elements in the list: ";
        cin >> size;

        cout << "Enter the elements in the list...\n";

        for(int iterate = 0; iterate < size; ++iterate)
        {
            cin >> element;
            myList.insert(element);
        }

        cout << "List:: ";
        myList.display();

        cout << "\nEnter an element to delete from the list:: ";
        cin >> element;

        myList.delete_from_list(element);

        cout << "List:: ";
        myList.display();
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }
    
    return 0;
}