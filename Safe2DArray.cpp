// Safe 2D Array with 1D Array

#include <iostream>

using namespace std;

class Array2D
{
    private:
        int noOfRows;
        int noOfCols;
        int* elements;

    public: 

    // Default Constructor
    Array2D(int rows = 1, int cols = 1)
    {
        if(rows <= 0 || cols <= 0)
            throw "Bad Initialisers";

        noOfRows = rows;
        noOfCols = cols;
        elements = new int[rows * cols];
    }

    // Copy Constructor
    Array2D(const Array2D &obj)
    {
        noOfRows = obj.noOfRows;
        noOfCols = obj.noOfCols;
        elements = new int[noOfRows * noOfCols];

        for(int index = 0; index < noOfRows * noOfCols; ++index)
            elements[index] = obj.elements[index];
    }

    // Destructor to deallocate the memory
    ~Array2D()
    {
        delete[] elements;
    }

    // Overloading () operator
    int& operator() (int row, int col)
    {
        if(row < 0 || row >= noOfRows || col < 0 || col >= noOfCols)
            throw "Array out of Bound";

        // It is a row major form. For column major, use formula (index = col * noOfRows + row)
        int index = row * noOfCols + col;
        return elements[index];
    }

    // Overloading + operator to add two 2D Arrays
    Array2D& operator+ (const Array2D &obj)
    {
        if(noOfRows != obj.noOfRows || noOfCols != obj.noOfCols)
            throw "2D Arrays can't be added";
        
        Array2D temp(noOfRows, noOfCols);
        for(int index = 0; index < noOfRows * noOfCols; ++index)
            temp.elements[index] = elements[index] + obj.elements[index];

        return temp;
    }

    // Overloading - operator to subtract two 2D Arrays
    Array2D& operator- (const Array2D &obj)
    {
        if(noOfRows != obj.noOfRows || noOfCols != obj.noOfCols)
            throw "2D Arrays can't be subtracted";
        
        Array2D temp(noOfRows, noOfCols);
        for(int index = 0; index < noOfRows * noOfCols; ++index)
            temp.elements[index] = elements[index] - obj.elements[index];

        return temp;
    }

    // Overloading = operator to assign the values
    Array2D& operator= (const Array2D &obj)
    {
        if(noOfRows != obj.noOfRows || noOfCols != obj.noOfCols)
        {
            delete[] elements;
            noOfRows = obj.noOfRows;
            noOfCols = obj.noOfCols;
            elements = new int[noOfRows * noOfCols];
        }

        for(int index = 0; index < noOfRows * noOfCols; ++index)
            elements[index] = obj.elements[index];
        
        return *this;
    }

    // Function prototype to overload stream insertion operator
    friend ostream& operator<< (ostream& out, const Array2D &obj);

    // Function prototype to overload stream extraction operator
    friend istream& operator>> (istream& in, const Array2D &obj);
};  

// Function definition to overload stream insertion operator
ostream& operator<< (ostream& out, const Array2D &obj)
{
    int index;

    for(int row = 0; row < obj.noOfRows; ++row)
    {
        for(int col = 0; col < obj.noOfCols; ++col)
        {
            index = row * obj.noOfCols + col; 
            out << obj.elements[index] << " ";
        }
        
        out << endl;
    }
}

// Function definition to overload stream extraction operator
istream& operator>> (istream& in, const Array2D &obj)
{
    for(int index = 0; index < obj.noOfRows * obj.noOfCols; ++index)
        in >> obj.elements[index];
}

int main()
{
    
}