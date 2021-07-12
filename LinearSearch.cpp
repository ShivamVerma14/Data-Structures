/* Linearly searching elements in the array
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No: 19HCS4048
*/

#include <iostream>

using namespace std;

template <typename T>
class Array1D
{
    private:
        int size;
        T* elements;

    public:

        // Default constructor
        Array1D(int size = 0)
        {
            if(size < 0)
                throw "Bad Initialisers";
            this->size = size;
            elements = new T[size];
        }

        // Destructor to deallocate the memory
        ~Array1D()
        {
            delete[] elements;
        }

        // Overloading [] operator
        int& operator[] (int index) const
        {
            if(index < 0 || index >= size)
                throw "Array out of Bound";
            return elements[index];
        }

        
        // Function prototype to linearly search an element
        template <typename U>
        friend int linearSearch(const Array1D<U> obj, U searchElement);

        // Function prototype for overloading stream insertion operator
        template <typename U>
        friend ostream& operator<< (ostream &out, const Array1D<U> &obj);

        // Function prototype for overloading stream extraction operator
        template <typename U>
        friend istream& operator>> (istream &in, Array1D<U> &obj);
};

// Function Definition for linear search
template <typename T>
int linearSearch(const Array1D<T> obj, T searchElement)
{
    for(int index = 0; index < obj.size; ++index)
        if(obj[index] == searchElement)
            return index;
    
    return -1;
}

// Function Definition of stream insertion overloading
template <typename T>
ostream& operator<< (ostream &out, const Array1D<T> &obj)
{
    for(int index = 0; index < obj.size; ++index)
        out << obj.elements[index] << " ";
    
    return out;
}

// Function Definition of stream extraction overloading
template <typename T>
istream& operator>> (istream &in, Array1D<T> &obj)
{
    for(int index = 0; index < obj.size; ++index)
        in >> obj.elements[index];

    return in;
}

int main()
{
    int sizeOfArray, searchElement;

    cout << "Enter the size of the Array: ";
    cin >> sizeOfArray;

    Array1D<int> array(sizeOfArray);

    cout << "Enter the elements in the Array..." << endl;
    cin >> array;

    cout << "Enter the element to be searched in the Array: ";
    cin >> searchElement;

    int position = linearSearch(array, searchElement);

    if(position == -1)
        cout << searchElement << " is not found in the Array." << endl;
    else
        cout << searchElement << " is found at " << position + 1 << "th position in the Array." << endl;

    return 0;    
}