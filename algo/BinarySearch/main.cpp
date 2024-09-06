#include <stdio.h>
#include <iostream>

using namespace std;

int BinarySearch (int num[], int size, int x)
{
    int low  = 0;
    int high = (size - 1);
    int mid  = 0;
    while (low <= high)
    {
        mid = ((low + high)/ 2);
        
        if (x == num[mid])
        {
            return mid;
        }
        else
        {
            if (x < num[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
    }
    
    return -1;
}

int BinarySearch (int arr[], int low, int high, int x)
{
    if (low <= high)
    {
        int mid = ((low + high)/ 2);

        if (x == arr[mid])
        {
            return mid;
        }
        else
        {
            if (x < arr[mid])
            {
                return BinarySearch(arr, low, mid - 1, x);
            }
            else
            {
                return BinarySearch(arr, mid + 1, high, x);
            }
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    int sortedArr[] = {1, 2, 3, 4, 5, 8, 15, 28, 54};
    int n        = sizeof(sortedArr)/sizeof(sortedArr[0]);
    int target   = 15;
    int position = BinarySearch (sortedArr, n, target);
    
    cout << "Using Brute Force Binary Search." << endl;
    if (position == -1)
    {
        cout << "Target not found."<< endl;
    }
    else
    {
        cout << "Target found at position " << position << "." << endl;
    }
    
    cout << "Using Recursive Binary Search." << endl;
    position = BinarySearch (sortedArr, 0, (n-1), target);
    if (position == -1)
    {
        cout << "Target not found." << endl;;
    }
    else
    {
        cout << "Target found at position "<< position << "." << endl;
    }

    return 0;
}