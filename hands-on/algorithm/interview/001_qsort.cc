/*
 * sample test command: bin/generator.out prime 2000000 -r | bin/001_qsort.out
 */

#include <iostream>
#include <algorithm>
#include "alib.h"

using namespace std;

typedef int (*pfP)(int *A, int p, int q);
int stable_partition(int *A, int p, int q) {
    int i,j;
    i = p-1;
    j = p;
    int k = A[q-1];
    while (j < q-1) {
        if(A[j] < k) {
            i++;
            swap(A[i], A[j]);
        }
        j++;
    }
    i++;
    swap(A[i], A[q-1]);
    return i;
}

int partition(int *A, int p, int q) {
    int m=p+(q-p)/2;
    swap(A[p], A[m]);
    int i,j;
    i = p+1;
    j = q-1;
    int pivot=A[p];
    while (i<=j){
        while (i < q && A[i]<=pivot) i++;
        while (j >=p && A[j]>pivot) j--;
        if (i<j) swap(A[i], A[j]);
    }
    swap(A[p],A[j]);
    return j;
}

const int qsort_threshold = 5;

void insert_sort(int *A, int p, int q) {
    for (int i=p+1; i<q; ++i) {
        int key = A[i];
        int j = i;
        while(j>p && key < A[j-1]) {
            A[j] = A[j-1];
            j--;
        }
        A[j] = key;
    }
}

void qsort(int *A, int p, int q, pfP partition) { 
    if (p>=q) return;
    if (q-p <= qsort_threshold) {
       insert_sort(A, p, q);
       return;
    }
    int m = partition(A, p, q);
    qsort(A, p, m, partition);
    qsort(A, m+1, q, partition);
}

const int maxn = 1024*1024;
int buffer[maxn+1];
int buffer2[maxn+1];
int buffer3[maxn+1];
int main() {
    int N;
    cin>>N;
    for(int i=0; i<N; ++i) cin>>buffer[i];
    copy(buffer,buffer+N, buffer2);
    copy(buffer,buffer+N, buffer3);
    al::sw sw;
    sw.start();
    sort(buffer2,buffer2+N);
    sw.end("STL sort");
    sw.start();
    qsort(buffer, 0, N, partition);
    sw.end("my qsort");
    sw.start();
    qsort(buffer3, 0, N, stable_partition);
    sw.end("my qsort(stable)");
    if (!equal(buffer,buffer+N,buffer2)) {
        cerr << "Failed!!!"<<endl;
        copy(buffer, buffer+N, ostream_iterator<int>(cout, " "));
    } 
    else {
        cout << "OK!!!";
    }
    cout << endl;
    return 0;
}
