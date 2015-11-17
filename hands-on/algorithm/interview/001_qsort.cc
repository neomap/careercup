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
    //int m=p+(q-p)/2;
    //swap(A[p], A[m]);
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

void qsort(int *A, int p, int q, pfP partition) { 
    if (p>=q) return; int m = partition(A, p, q);
    qsort(A, p, m, partition);
    qsort(A, m+1, q, partition);
}

const int maxn = 1024*1024;
int buffer[maxn+1];
int buffer2[maxn+1];
int main() {
    int N;
    cin>>N;
    for(int i=0; i<N; ++i) cin>>buffer[i];
    copy(buffer,buffer+N, buffer2);
    al::sw sw;
    sw.start();
    sort(buffer2,buffer2+N);
    sw.end("STL sort");
    sw.start();
    qsort(buffer, 0, N, partition);
    sw.end("my qsort");
    if (!equal(buffer,buffer+N,buffer2)) {
        cerr << "Failed!!!";
        copy(buffer, buffer+N, ostream_iterator<int>(cout, " "));
    } 
    else {
        cout << "OK!!!";
    }
    cout << endl;
    return 0;
}
