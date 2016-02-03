#include "101_sort.h"
void sort::insert_sort(int a[], int len)
{
    int temp;
    for(int i=1; i < len; ++i)
    {
        temp = a[i];
        int k = i-1;
        while(a[k] > temp && k >=0)
        {
            a[k+1] = a[k];
            k--;
        }
        a[k+1] = temp;
    }
}
