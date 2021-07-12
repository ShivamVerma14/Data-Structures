// Safe 1D Array

#include <iostream>

using namespace std;

class Array1D
{
    private:
        int size;
        int* elements;

    public:
        // Constructor to initialise the instance variables
        Array1D(int size = 0)
        {
            if(size < 0)
                throw "Bad Initialiser";
            this->size = size;
            elements = new int[size];
        }

        // A copy constructor to generate a copy
        Array1D(const Array1D &obj)
        {
            size = obj.size;
            for(int index = 0; index < size; ++index)
                elements[index] = obj.elements[index];
        }

        // Destructor to de-allocate the memory
        ~Array1D()
        {
            delete[] elements;
        }

        // Accessor function to get the size of array
        int Size() const
        {
            return size;
        }

        // Overloading [] operator
        int& operator[] (int index) const
        {
            if(index >= size || index < 0)
                throw "Array out of bound";
            return elements[index];
        }

        // Function prototype for overloading = operator
        Array1D& operator= (const Array1D &obj);

        // Function prototype for overloading + operator
        Array1D operator+ (const Array1D &obj);

        // Function prototype for overloading - operator
        Array1D operator- (const Array1D &obj);

        // Function prototype for overloading * operator
        Array1D operator* (const Array1D &obj);

        // Function prototype for overloading - (unary minus) operator
        Array1D operator- ();
        
        // Function prototype for overloading stream insertion operator
        friend ostream& operator<< (ostream &out, const Array1D &obj);

        // Function prototype for overloading stream extraction operator
        friend istream& operator>> (istream &in, Array1D &obj);
};

// Function Defintion to overload = operator
Array1D& Array1D :: operator= (const Array1D &obj)
{
    if(this == &obj)
        return *this;
    
    if(size != obj.size)
    {
        size = obj.size;
        delete[] elements;
        elements = new int[size];
    }

    for(int index = 0; index < size; ++index)
        elements[index] = obj.elements[index];

    return *this;
}

// Function Definition to overload + operator
Array1D Array1D :: operator+ (const Array1D &obj)
{
    if(size != obj.size)
        throw "Sizes are not equal.";
    
    Array1D temp(size);
    for(int index = 0; index < size; ++index)
        temp.elements[index] = elements[index] + obj.elements[index];

    return temp;
}

// Function Definition to overload - operator
Array1D Array1D :: operator- (const Array1D &obj)
{
    if(size != obj.size)
        throw "Sizes are not equal.";
    
    Array1D temp(size);
    for(int index = 0; index < size; ++index)
        temp.elements[index] = elements[index] - obj.elements[index];

    return temp;
}

// Function Definition to overload * operator
Array1D Array1D :: operator* (const Array1D &obj)
{
    if(size != obj.size)
        throw "Sizes are not equal.";
    
    Array1D temp(size);
    for(int index = 0; index < size; ++index)
        temp.elements[index] = elements[index] * obj.elements[index];

    return temp;
}

// Function definition to overload - (unary minus) operator
Array1D Array1D :: operator- ()
{
    Array1D temp(size);
    for(int index = 0; index < size; ++index)
        temp.elements[index] = -1 * elements[index];

    return temp;
}

// Function Definition of stream insertion overloading
ostream& operator<< (ostream &out, const Array1D &obj)
{
    for(int index = 0; index < obj.Size(); ++index)
        out << obj.elements[index] << " ";
    
    return out;
}

// Function Definition of stream extraction overloading
istream& operator>> (istream &in, Array1D &obj)
{
    for(int index = 0; index < obj.Size(); ++index)
        in >> obj.elements[index];

    return in;
}

int main()
{
    int firstSize, secondSize, option1, option2;
    char choice;

    try
    {
        cout << "Enter the size of first Array: ";
        cin >> firstSize;
        Array1D firstArray(firstSize);
        cout << "Enter the elements in the Array: " << endl;
        cin >> firstArray;

        cout << "Enter the size of second Array: ";
        cin >> secondSize;
        Array1D secondArray(secondSize);
        cout << "Enter the elements in the Array: " << endl;
        cin >> secondArray;

        do
        {
            system("cls");
            
            cout << "\t****Menu****\n";
            cout << "1. Addition of two Arrays\n";
            cout << "2. Subtraction of two Arrays\n";
            cout << "3. Multiplication of two Arrays\n";
            cout << "4. Negation of all elements in the Array\n";
            cout << "Enter your choice: ";
            cin >> option1;

            system("cls");

            switch(option1)
            {
                case 1: 
                {
                    Array1D addedArray = firstArray + secondArray;
                    cout << "First Array: " << firstArray << endl;
                    cout << "Second Array: " << secondArray << endl;
                    cout << "Addition: " << addedArray << endl;
                    break;
                }

                case 2:
                {
                    Array1D subArray = firstArray - secondArray;
                    cout << "First Array: " << firstArray << endl;
                    cout << "Second Array: " << secondArray << endl;
                    cout << "Subtraction: " << subArray << endl;
                    break;
                }

                case 3:
                {
                    Array1D mulArray = firstArray * secondArray;
                    cout << "First Array: " << firstArray << endl;
                    cout << "Second Array: " << secondArray << endl;
                    cout << "Multiplication: " << mulArray << endl;
                    break;
                }

                case 4:
                {
                    cout << "\t****Menu****\n";
                    cout << "1. Unary minus of first Array\n";
                    cout << "2. Unary minus of second Array\n";
                    cout << "Choose the option: ";
                    cin >> option2;

                    system("cls");

                    switch(option2)
                    {
                        case 1:
                        {
                            Array1D negFirstArray = -firstArray;
                            cout << "First Array: " << firstArray << endl;
                            cout << "Negation: " << negFirstArray << endl;
                            break;
                        }

                        case 2:
                        {
                            Array1D negSecondArray = -secondArray;
                            cout << "Second Array: " << secondArray << endl;
                            cout << "Negation: " << negSecondArray << endl;
                            break;
                        }

                        default:
                        {
                            cout << "Choose correct option!!!\n";
                        }
                    }
                    break;
                }

                default:
                {
                    cout << "Choose correct option!!!\n";
                }
            }

            cout << "Do you want to continue (Y/N): ";
            cin >> choice;

        } while (choice == 'Y' || choice == 'y');
        
    }
    catch(const char* exception)
    {
        cerr << exception << '\n';
    }
    
}
// It's a comment added by cmd 
