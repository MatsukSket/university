#include <iostream>
#include <algorithm>

int partition(int *arr, int l, int r) {
    int pivot = arr[(l + r) / 2];
    int i = l, j = r;
    while(1) {
        while(arr[i] < pivot) i++;
        while(arr[j] > pivot) j--;
        if(i >= j)  return j;

        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

void quickSort(int *arr, int l, int r) {
    if ( l < r) {
        int pivot = partition(arr, l, r);
        quickSort(arr, l, pivot);
        quickSort(arr, pivot+1, r);
    }
}

int main()
{
    int d[]{5, 4, 3, 2, 1, 3, 1};
    quickSort(d, 0, 6);
    for (int t : d) {
        printf("%d ", t);
    }
    printf("\n");
    return 0;
}