/* Sorting of arrays using Bubble, Insertion and Selection Sort
Name: Shivam Verma
Course: B.Sc.(H) Computer Science 3rd Semester
Roll No.: 19HCS4048
*/

#include <iostream>

using namespace std;

template <class T>
void bubble_sort(T* array, int size)
{
    bool sorted = false;

    for(int i = 0; !sorted && i < size; i++)
    {
        sorted = true;
        for(int j = 0; j < size - i; j++)
            if(array[j] > array[j + 1])
            {
                sorted = false;
                swap(array[j], array[j + 1]);
            }
    }
}

template <class T>
void selection_sort(T* array, int size)
{
    for(int i = 0; i < size - 1; ++i)
    {
        int smallest = i;

        for(int j = i + 1; j < size; ++j)
            if(array[j] < array[smallest])
                smallest = j;
                
        swap(array[i], array[smallest]);
    }
}

template <class T>
void insertion_sort(T* array, int size)
{
    for(int i = 1; i < size; i++)
    {
        T key = array[i];
        int j = i;
        while(j > 0 && array[j - 1] > key)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}

template <class T>
void print_array(T* array, int size)
{
    for(int index = 0; index < size; ++index)
        cout << array[index] << " ";
    cout << endl;
}

int main()
{
    int size, *array, option;
    
    cout << "Enter the size of the Array: ";
    cin >> size;

    array = new int[size];

    cout << "Enter the elements of the Array...\n";
    for(int index = 0; index < size; index++)
        cin >> array[index];

    system("cls");

    cout << "\t****SORTING MENU****\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "Enter your option: ";
    cin >> option;

    switch(option)
    {
        case 1:
            cout << "Original Array:: ";
            print_array(array, size);
            bubble_sort(array, size);
            cout << "Sorted Array:: ";
            print_array(array, size);
            break;

        case 2:
            cout << "Original Array:: ";
            print_array(array, size);
            selection_sort(array, size);
            cout << "Sorted Array:: ";
            print_array(array, size);
            break;

        case 3:
            cout << "Original Array:: ";
            print_array(array, size);
            insertion_sort(array, size);
            cout << "Sorted Array:: ";
            print_array(array, size);
            break;

        default:
            cout << "Wrong choice of option\n";
            exit(0);
    }

    return 0;
}