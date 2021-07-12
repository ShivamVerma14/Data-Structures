/* Program to add two large integers using doubly linked list
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No: 19HCS4048
*/

#include <bits/stdc++.h>

using namespace std;

class Node
{
    Node* previous;
    Node* next;
    int info;

    public: 

        // A constructor
        Node(int info = 0)
        {
            previous = NULL;
            next = NULL;
            this->info = info;
        }

        // A friend class
        friend class Integer;
};

class Integer
{
    Node* header;
    Node* trailer;

    public: 

        // A constructor
        Integer()
        {
            header = new Node();
            trailer = new Node();

            header->next = trailer;          
            trailer->previous = header;
        }

        // A destructor
        ~Integer()
        {
            Node* ptr = header->next, *old;

            while(ptr != trailer)
            {
                old = ptr;
                ptr = ptr->next;

                delete old;
            }

            delete header;
            delete trailer;
        }

        // Converts the number to string
        string toString();

        // Function to insert the number in nodes
        void getNumber(string);

        // Function to add number in tail
        void addTail(int); 

        // Function to add number in front
        void addFront(int);

        // Adds the two integers
        Integer operator+ (const Integer&);

        // Assigns the value of one integer to another
        Integer& operator= (const Integer&);
};

void Integer :: getNumber(string number)
{
    reverse(number.begin(), number.end());

    for(int iterator = 0; iterator < number.length(); iterator += 4)
    {
        string subNum = number.substr(iterator, 4);
        reverse(subNum.begin(), subNum.end());

        int num = stoi(subNum);

        addFront(num); 
    }
}

string Integer :: toString()
{
    string number = "", temp = "";

    Node* ptr = header->next;

    while(ptr != trailer)
    {
        temp = to_string(ptr->info);
        ptr = ptr->next;

        string zero = "";

        if(temp.size() != 4)
        {
            int lessZero = 4 - temp.size();

            for(int iterate = 0; iterate < lessZero; ++iterate)
                zero += '0';

            temp = zero + temp;
        }

        number += temp;
    }

    return number;
}

void Integer :: addTail(int num)
{
    Node* newNode = new Node(num);

    newNode->next = trailer;
    newNode->previous = trailer->previous;

    trailer->previous->next = newNode;
    trailer->previous = newNode;
}

void Integer :: addFront(int num)
{
    Node* newNode = new Node(num);

    newNode->previous = header;
    newNode->next = header->next;

    header->next->previous = newNode;
    header->next = newNode;
}

Integer Integer :: operator+ (const Integer& integer)
{
    int carry = 0, sum = 0;

    Integer result;
    Node* a = trailer->previous;
    Node* b = integer.trailer->previous;

    while(a != header || b != integer.header)
    {
        if(a != header && b != integer.header)
        {
            sum = (a->info + b->info + carry) % 10000;
            carry = (a->info + b->info + carry) / 10000;

            a = a->previous;
            b = b->previous;
        }
        else if(a != header && b == integer.header)
        {
            sum = (a->info + carry) % 10000;
            carry = (a->info + carry) / 10000;

            a = a->previous;
        }
        else if(a == header && b != integer.header)
        {
            sum = (b->info + carry) % 10000;
            carry = (b->info + carry) / 10000;

            b = b->previous;
        }

        result.addFront(sum);
    }

    if(carry != 0)
        result.addFront(carry);

    return result;
}

Integer& Integer :: operator= (const Integer& integer)
{
    if(this == &integer)
        return *this;

    Node* ptr = integer.header->next;

    while(ptr != integer.trailer)
    {
        addTail(ptr->info);
        ptr = ptr->next;
    }

    return *this;
}

int main()
{
    string firstNumber, secondNumber, thirdNumber;

    cout << "\nEnter the first number: ";
    cin >> firstNumber;

    cout << "\nEnter the second Number: ";
    cin >> secondNumber;

    Integer first, second, third;

    first.getNumber(firstNumber);
    second.getNumber(secondNumber);

    third = first + second;
    thirdNumber = third.toString();

    cout << "\nAdded Number: " << thirdNumber;

    return 0;
}