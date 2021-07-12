#include <iostream>
using namespace std;

int min_element(int *a, int low, int up)
{
    int mid = (low + up) / 2;
    if(low == up)
        return a[low];
    if(up < low)
    return a[0];

    if(mid > low)
    {
        if(a[mid - 1] > a[mid])
            return a[mid];
    }
    if(a[up] > a[mid])
        return min_element(a, low, mid - 1);
    else
    return min_element(a, mid + 1, up);

}

int main()
{
    int a[] = {16, 19, 20, 1, 5, 10, 13};
    int size = sizeof(a)/sizeof(a[0]);
    int min = min_element(a, 0, size - 1);

    cout << min;
    return 0;
}