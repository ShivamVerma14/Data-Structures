/* Implementation of Binary Search Tree
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Sem
Roll No.: 19HCS4048
*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

template <class T>
class Node
{
    T key;
    Node *left, *right;

    public:
        // A parameterized Constructor
        Node(const T& element = NULL) : key(element), left(NULL), right(NULL) {}

        // A friend class declaration
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

        // Clears the BST
        void clear()
        {
            clear(root);
            root = NULL;
        }

        // Returns true if BST is empty
        bool empty() const
        {
            return root == NULL;
        }

        // PreOrder traversal
        void preOrder()
        {
            preOrder(root);
        }

        // InOrder traversal
        void inOrder()
        {
            inOrder(root);
        }

        // PostOrder traversal
        void postOrder()
        {
            postOrder(root);
        }

        // Level-by-Level Traversal
        void levelByLevelTraversal();

        // Inserts an element in BST
        void insert(const T& element)
        {
            insert(root, element);
        }

        // Deletes an element in BST
        void deleteByCopying(const T&);

        // Returns the height of BST
        int height() const
        {
            return height(root);
        }

        // Searches an element
        Node<T>* search(const T& element) const
        {
            return search(root, element);
        }

    protected:
        Node<T>* root;

        void clear(Node<T>*);
        Node<T>* search(Node<T>*, const T&) const;
        void preOrder(Node<T>*);
        void inOrder(Node<T>*);
        void postOrder(Node<T>*);
        void insert(Node<T>* &, const T&);
        int height(Node<T>*) const;

        // Prints the key of nodes
        virtual void visit(Node<T>* pointer)
        {
            cout << pointer->key << " ";
        }
};

template <class T>
void BST<T> :: clear(Node<T>* node)
{
    if(node == NULL)
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

template <class T>
void BST<T> :: preOrder(Node<T>* node)
{
    if(node == NULL)
        return;

    visit(node);
    preOrder(node->left);
    preOrder(node->right);
}

template <class T>
void BST<T> :: inOrder(Node<T>* node)
{
    if(node == NULL)
        return;

    inOrder(node->left);
    visit(node);
    inOrder(node->right);
}

template <class T>
void BST<T> :: postOrder(Node<T>* node)
{
    if(node == NULL)
        return;

    postOrder(node->left);
    postOrder(node->right);
    visit(node);
}

template <class T>
void BST<T> :: levelByLevelTraversal()
{
    queue<Node<T>*> myQueue;
    Node<T>* pointer = root;

    if(pointer != NULL)
    {
        myQueue.push(pointer);
        while(!myQueue.empty())
        {
            pointer = myQueue.front();
            visit(pointer);
            myQueue.pop();
            if(pointer->left != NULL)
                myQueue.push(pointer->left);
            if(pointer->right != NULL)
                myQueue.push(pointer->right);
        }
    }
}

template <class T>
void BST<T> :: insert(Node<T>* &node, const T& element)
{
    if(node == NULL)
    {
        Node<T>* newNode = new Node<T>(element);
        node = newNode;
        return;
    }

    if(element < node->key)
        insert(node->left, element);
    else if(element > node->key)
        insert(node->right, element);
}

template <class T>
void BST<T> :: deleteByCopying(const T& element)
{
    if(root == NULL)
        throw "Empty Tree";
    
    Node<T> *p = root, *fp = NULL;
    bool left;

    while(p != NULL && p->key != element)
    {
        fp = p;
        if(element < p->key)
            p = p->left;
        else
            p = p->right;
    }

    if(p == NULL)
        throw "Element not present!!!";

    if(fp != NULL)
        left = element < fp->key ? true : false;

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

    else
    {
        Node<T> *q = p->right, *fq = p;
        while(q->left != NULL)
        {
            fq = q;
            q = q->left;
        }

        p->key = q->key;

        if(q->key < fq->key)
            fq->left = q->right;
        else
            fq->right = q->right;

        delete q;
    }
}

template <class T>
Node<T>* BST<T> :: search(Node<T>* node, const T& element) const
{
    if(node == NULL)
        return node;
    if(node->key == element)
        return node;

    else if(element < node->key)
        return search(node->left, element);
    else
        return search(node->right, element);    
}

template <class T>
int BST<T> :: height(Node<T>* node) const
{
    if(node == NULL)
        return -1;
    else if(node->left == NULL && node->right == NULL)
        return 0;

    else
    {
        int hL = height(node->left);
        int hR = height(node->right);
        int max = hL > hR ? hL : hR;

        return (max + 1);
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
        for(int iterate = 0; iterate < size; iterate++)
        {
            cin >> element;
            myTree.insert(element);
        }

        cout << "\n\nPreOrder Traversal:: ";
        myTree.preOrder();

        cout << "\nInOrder Traversal:: ";
        myTree.inOrder();

        cout << "\nPostOrder Traversal:: ";
        myTree.postOrder();

        cout << "\nLevel By Level Traversal:: ";
        myTree.levelByLevelTraversal();

        cout << "\n\nHeight of the tree:: " << myTree.height();

        cout << "\n\nEnter the element to delete: ";
        cin >> element;
        myTree.deleteByCopying(element);

        cout << "\nInOrder Traversal:: ";
        myTree.inOrder();

        cout << "\n\nElement to be replaced:: ";
        cin >> element;

        if(myTree.search(element))
        {
            myTree.deleteByCopying(element);
            cout << "New Element:: ";
            cin >> element;
            myTree.insert(element);
            cout << "\nInOrder Traversal:: ";
            myTree.inOrder();
        }
        else
            throw "Element to be replaced not found!!!";
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}