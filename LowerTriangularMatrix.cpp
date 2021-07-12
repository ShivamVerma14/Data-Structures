/* Implementation of Lower Triangular Matrix using 1-D Array
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
*/

#include <iostream>

using namespace std;

class LowerTriangularMatrix
{
    int size_of_array;
    int size_of_matrix;
    int *elements;

public:
    // A constructor
    LowerTriangularMatrix(int size = 0)
    {
        if(size <= 0)
            throw "Bad Initializer!!!\n";

        size_of_matrix = size;
        size_of_array = (size * (size + 1)) / 2;
        elements = new int[size_of_array]; 
    }

    // A destructor
    ~LowerTriangularMatrix()
    {
        delete[] elements;
    }

    // Stores the element of Lower Triangular Matrix in the array
    LowerTriangularMatrix& store(const int &, int, int);

    // Retrives the element from the array
    int retrieve(int, int) const;

    // Overloading << operator
    friend ostream& operator<< (ostream&, const LowerTriangularMatrix&);
};

LowerTriangularMatrix& LowerTriangularMatrix ::store(const int& x, int i, int j)
{
    if(i < 1 || i > size_of_array || j < 1 || j > size_of_array)
        throw "Out of Bound!!!";
    if(i < j && x != 0)
        throw "Must be zero!!!";
    if(i >= j)
    {
        int index = ((i * (i - 1)) / 2) + j - 1;
        elements[index] = x;
    }
    return *this;
}

int LowerTriangularMatrix ::retrieve(int i, int j) const
{
    if(i < 1 || i > size_of_array || j < 1 || j > size_of_array)
        throw "Out of Bound!!!";
    if(i >= j)
    {
        int index = ((i * (i - 1)) / 2) + j - 1;
        return elements[index];
    }
    else
        return 0;
}

ostream& operator<< (ostream& out, const LowerTriangularMatrix& obj)
{
    for(int row = 1; row <= obj.size_of_matrix; row++)
    {
        for(int col = 1; col <= obj.size_of_matrix; col++)
            out << obj.retrieve(row, col) << " ";
        out << '\n';
    }
    return out;
}

int main()
{
    try
    {
        LowerTriangularMatrix matrix(4);

        cout << "Enter the elements of Lower Triangular Matrix of size 4*4...\n";
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