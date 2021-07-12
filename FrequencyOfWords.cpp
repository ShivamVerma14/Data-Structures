/* Frequency of words in a file
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
Exam Roll No.: 19015570031
Paper Title: Data Structures
*/

#include <bits\stdc++.h>
#include <fstream>
#include <algorithm>

using namespace std;

template <class T>
class Node
{
    T words;
    int count;
    Node *left, *right;

    public:
        // A parameterized Constructor
        Node(const T& element = NULL) : words(element), count(1), left(NULL), right(NULL) {}

        // A friend class declaration
        template <class U>
        friend class AVL;
};

template <class T>
class AVL
{
    public:
        // A constructor
        AVL() : root(NULL) {}

        // A destructor
        ~AVL()
        {
            clear();
        }

        // Clears the AVL Tree
        void clear()
        {
            clear(root);
            root = NULL;
        }

        // Returns true if AVL Tree is empty
        bool empty() const
        {
            return root == NULL;
        }

        // InOrder traversal
        void inOrder()
        {
            inOrder(root);
        }

        // Inserts an element in AVL Tree
        void insert(const T& element)
        {
            root = insert(root, element);
        }

        // Returns Balance-Factor
        int difference(Node<T>*) const;

        // Balances and selects the rotation to be performed
        Node<T>* balance(Node<T>*);

        // Returns the height of AVL Tree
        int height() const
        {
            return height(root);
        }

    protected:
        Node<T>* root;

        void clear(Node<T>*);
        void inOrder(Node<T>*);
        Node<T>* insert(Node<T>* &, const T&);
        int height(Node<T>*) const;

        // RR Rotation
        Node<T>* rr_rotation(Node<T>*);

        // LL Rotation
        Node<T>* ll_rotation(Node<T>*);

        // LR Rotation
        Node<T>* lr_rotation(Node<T>*);

        // RL Rotation
        Node<T>* rl_rotation(Node<T>*);

        // Prints the words of nodes
        virtual void visit(Node<T>* pointer)
        {
            cout << pointer->words << "\t : " << pointer->count << '\n';
        }
};

template <class T>
void AVL<T> :: clear(Node<T>* node)
{
    if(node == NULL)
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

template <class T>
void AVL<T> :: inOrder(Node<T>* node)
{
    if(node == NULL)
        return;

    inOrder(node->left);
    visit(node);
    inOrder(node->right);
}

template <class T>
Node<T>* AVL<T> :: insert(Node<T>* &node, const T& element)
{
    if(node == NULL)
    {
        Node<T>* newNode = new Node<T>(element);
        return newNode;
    }
    else if(node->words == element)
    {
        node->count++;
        return node;
    }
    else if(element < node->words)
    {
        node->left = insert(node->left, element);
        node = balance(node);
    }
    else
    {
        node->right = insert(node->right, element);
        node = balance(node);
    }
    return node;
}

template <class T>
int AVL<T> :: difference(Node<T>* node) const
{
    return height(node->left) - height(node->right);
}

template <class T>
Node<T>* AVL<T> :: balance(Node<T>* node)
{
    int balance_factor = difference(node);
    if(balance_factor > 1)
    {
        if(difference(node->left) > 0)
            node = ll_rotation(node);
        else
            node = lr_rotation(node);
    }
    else if(balance_factor < -1)
    {
        if(difference(node->right) > 0)
            node = rl_rotation(node);
        else
            node = rr_rotation(node);
    }
    return node;
}

template <class T>
Node<T>* AVL<T> :: rr_rotation(Node<T>* parent)
{
    Node<T>* node = parent->right;
    parent->right = node->left;
    node->left = parent;

    return node;
}

template <class T>
Node<T>* AVL<T> :: ll_rotation(Node<T>* parent)
{
    Node<T>* node = parent->left;
    parent->left = node->right;
    node->right = parent;

    return node;
}

template <class T>
Node<T>* AVL<T> :: lr_rotation(Node<T>* parent)
{
    Node<T>* node = parent->left;
    parent->left = rr_rotation(node);

    return ll_rotation(parent);
}

template <class T>
Node<T>* AVL<T> :: rl_rotation(Node<T>* parent)
{
    Node<T>* node = parent->right;
    parent->right = ll_rotation(node);

    return rr_rotation(parent);
}

template <class T>
int AVL<T> :: height(Node<T>* node) const
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
    string word, line;
    AVL<string> myTree;
    try
    {
        fstream file;
        file.open("source.txt", ios :: in);

        system("cls");

        cout << "Contents of the file...\n\n";

        while(!file.eof())
        {
            getline(file, line);
            cout << line << endl;
        }

        file.seekg(0);

        while(!file.eof())
        {
            file >> word;
            
            string temp = "";
            for(int index = 0; index < word.length(); index++)
                if(word[index] != '.' && word[index] != '!')
                    temp += word[index];

            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

            myTree.insert(temp);
        }

        cout << "\n\nFrequency of the words...\n";
        myTree.inOrder();

        file.close();
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }

    return 0;
}