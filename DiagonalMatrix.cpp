/* Implementation of Diagonal Matrix using 1-D Array
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
*/

#include <iostream>

using namespace std;

class DiagonalMatrix
{
    int size;
    int *elements;

public:
    // A constructor
    DiagonalMatrix(int size = 0)
    {
        if(size <= 0)
            throw "Bad Initializer!!!";

        this->size = size;
        elements = new int[size];
    }

    // A destructor
    ~DiagonalMatrix()
    {
        delete[] elements;
    }

    // Stores the diagonal element in array
    DiagonalMatrix& store(const int&, int, int);

    // Retrieves the diagonal element from array
    int retrieve(int, int) const;

    // Overloading << operator
    friend ostream& operator<< (ostream&, const DiagonalMatrix&);
};

DiagonalMatrix& DiagonalMatrix ::store(const int &x, int i, int j)
{
    if(i < 1 || i > size || j < 1 || j > size)
        throw "Out of Bound!!!";
    if(i != j && x != 0)
        throw "Must be zero!!!";
    if(i == j)
        elements[i - 1] = x;
    return *this;
}

int DiagonalMatrix ::retrieve(int i, int j) const
{
    if(i < 1 || i > size || j < 1 || j > size)
        throw "Out of Bound!!!";
    if(i == j)
        return elements[i - 1];
    else
        return 0;
}

ostream& operator<< (ostream& out, const DiagonalMatrix& obj)
{
    for(int row = 1; row <= obj.size; row++)
    {
        for(int col = 1; col <= obj.size; col++)
            out << obj.retrieve(row, col) << " ";
        out << '\n';
    }
    return out;
}

int main()
{
    try
    {
        DiagonalMatrix matrix(4);

        cout << "Enter the elements of Diagonal Matrix of size 4*4...\n";
        for(int row = 1; row <= 4; row++)
            for(int col = 1; col <= 4; col++)
            {
                int element;
                cin >> element;
                matrix.store(element, row, col);
            }

        cout << "Matrix is...\n";
        cout << matrix;
        cout << "Retrieved Value at place (1,1): " << matrix.retrieve(1, 1);
    }
    catch (const char* exception) {
        cout << "Exception: " << exception << '\n';
    }

    return 0;
}