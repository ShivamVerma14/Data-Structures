/* Data Structures Practical Q1. Binary Search Tree
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
    Node *left, *right;

    public:
        // A parameterized constructor
        Node(const T& element = NULL) : data(element), left(NULL), right(NULL) {}

        template <class U>
        friend class BST;
};

template <class T>
class BST
{
    public:
        // A constructor
        BST() : root(NULL) {}

        // A destructor
        ~BST()
        {
            clear();
        }

        // Clears the tree
        void clear()
        {
            clear(root);
            root = NULL;
        }

        // PreOrder Traversal in the tree
        void preOrder_traversal()
        {
            preOrder_traversal(root);
        }

        // Inserts an element in the tree
        void insert(const T& element)
        {
            insert(root, element);
        }

        // Deletes an element in the tree
        void delete_by_copying(const T&);

    protected:
        Node<T> *root;

        void clear(Node<T>*);
        void preOrder_traversal(Node<T>*);
        void insert(Node<T>* &, const T&);

        // Prints the data stored in Nodes
        virtual void visit(Node<T> *node)
        {
            cout << node->data << " ";
        }
};

template <class T>
void BST<T> :: clear(Node<T> *node)
{
    if(node == NULL)
        return;
    
    clear(node->left);
    clear(node->right);

    delete node;
}

template <class T>
void BST<T> :: preOrder_traversal(Node<T> *node)
{
    if(node == NULL)
        return;

    visit(node);
    preOrder_traversal(node->left);
    preOrder_traversal(node->right);
}

template <class T>
void BST<T> :: insert(Node<T>* &node, const T& element)
{
    if(node == NULL)
    {
        Node<T> *newNode = new Node<T>(element);
        node = newNode;
        return;
    }

    if(element == node->data)
        throw "Element is already present in the tree!!!";
    
    if(element < node->data)
        insert(node->left, element);
    else if(element > node->data)
        insert(node->right, element);
}

template <class T>
void BST<T> :: delete_by_copying(const T& element)
{
    if(root == NULL)
        throw "Empty Tree!!!";

    Node<T> *p = root, *fp = NULL;
    bool left;

    // Traversing to find the element's node and its parent node
    while(p != NULL && p->data != element)
    {
        fp = p;
        if(element < p->data)
            p = p->left;
        else
            p = p->right;
    }

    if(p == NULL)
        throw "Element is not present in the tree!!!";

    if(fp != NULL)
        left = element < fp->data ? true : false;

    // If element is present at leaf node
    if((p->left == NULL) && (p->right == NULL))
    {
        if(fp == NULL)
        {
            root = NULL;
            return;
        }
        if(left)
            fp->left = NULL;
        else
            fp->right = NULL;
    }

    // If element's node has one child i.e. left child
    else if(p->right == NULL)
    {
        if(fp == NULL)
        {
            root = p->left;
            return;
        }
        if(left)
            fp->left = p->left;
        else
            fp->right = p->left;
    }

    // If element's node has one child i.e. right child
    else if(p->left == NULL)
    {
        if(fp == NULL)
        {
            root = p->right;
            return;
        }
        if(left)
            fp->left = p->right;
        else
            fp->right = p->right;
    }

    // If element's node has both child
    else
    {
        Node<T> *q = p->right, *fq = p;
        while(q->left != NULL)
        {
            fq = q;
            q = q->left;
        }

        p->data = q->data;

        if(q->data < fq->data)
            fq->left = q->right;
        else
            fq->right = q->right;

        delete q;
    }
}

int main()
{
    int size;
    string element;
    BST<string> myTree;

    try
    {
        cout << "Enter the number of elements: ";
        cin >> size;

        cout << "Enter the elements in Binary Search Tree...\n";
        for(int iterate = 0; iterate < size; ++iterate)
        {
            cin >> element;
            myTree.insert(element);
        }

        cout << "Elements of the Tree (Pre Order Traversal) : ";
        myTree.preOrder_traversal();

        cout << "\nEnter the element to delete: ";
        cin >> element;
        myTree.delete_by_copying(element);

        cout << "Elements of the Tree (Pre Order Traversal) : ";
        myTree.preOrder_traversal();
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}