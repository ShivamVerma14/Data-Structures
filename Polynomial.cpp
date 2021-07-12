/* A program that adds two polynomials entered by user
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No: 19HCS4048
*/

#include <iostream>

using namespace std;

class Node
{
    int exponent;
    int coefficient;
    Node* next;

    public:

        // A constructor
        Node(int exp, int coef, Node* ptr = NULL)
        {
            exponent = exp;
            coefficient = coef;
            next = ptr;
        }

        // A friend class
        friend class Polynomial;
};

class Polynomial
{
    Node* head;
    Node* tail;

    public:

        // A constructor
        Polynomial()
        {
            head = tail = NULL;
        }

        // Function to add node at tail
        void addTail(int, int);

        // Function to insert information in node
        void insert();

        // Overloaded + operator to add two polynomial expressions
        Polynomial operator+ (const Polynomial&);

        // Function to display the expression
        void display();
};

void Polynomial :: addTail(int exp, int coef)
{
    Node* newNode = new Node(exp, coef);

    if(head == NULL)
    {
        head = tail = newNode;
        return;
    }
    
    tail->next = newNode;
    tail = newNode;
}

void Polynomial :: insert()
{
    int exp, coef;

    cout << "Enter the exponent of x: ";
    cin >> exp;
    cout << "Enter the coefficient: ";
    cin >> coef;

    system("cls");

    if(coef != 0)
        addTail(exp, coef);
}

Polynomial Polynomial :: operator+ (const Polynomial& poly)
{
    if(head == NULL)
        return poly;

    else if(poly.head == NULL)
        return *this;

    else
    {
        Polynomial result;

        Node *ptr1 = head, *ptr2 = poly.head;
        int sum = 0;

        while(ptr1 != NULL && ptr2 != NULL)
        {
            if(ptr1->exponent == ptr2->exponent)
            {
                sum = ptr1->coefficient + ptr2->coefficient;
                result.addTail(ptr1->exponent, sum);

                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }

            else if(ptr1->exponent > ptr2->exponent)
            {
                result.addTail(ptr1->exponent, ptr1->coefficient);

                ptr1 = ptr1->next;
            }

            else
            {
                result.addTail(ptr2->exponent, ptr2->coefficient);

                ptr2 = ptr2->next;
            }
        }

        while(ptr1 != NULL)
        {
            result.addTail(ptr1->exponent, ptr1->coefficient);
            ptr1 = ptr1->next;
        }

        while(ptr2 != NULL)
        {
            result.addTail(ptr2->exponent, ptr2->coefficient);
            ptr2 = ptr2->next;
        }

        return result;
    }
}

void Polynomial :: display()
{
    for(Node* ptr = head; ptr != NULL; ptr = ptr->next)
    {
        cout << ptr->coefficient;
        if(ptr->exponent != 0)
            cout << "x^" << ptr->exponent;
        if(ptr->next != NULL)
            cout << " + ";
    }
}

int main()
{
    Polynomial firstExp, secondExp, thirdExp;
    int terms;

    cout << "Enter the number of terms in first expression: ";
    cin >> terms;

    for(int iterator = 0; iterator < terms; ++iterator)
        firstExp.insert();

    cout << "Enter the number of terms in second expression: ";
    cin >> terms;

    for(int iterator = 0; iterator < terms; ++iterator)
        secondExp.insert();

    thirdExp = firstExp + secondExp;

    cout << "\nFirst Expression : ";
    firstExp.display();
    cout << "\nSecond Expression : ";
    secondExp.display();
    cout << "\nAdded Expression : ";
    thirdExp.display();

    return 0;
}