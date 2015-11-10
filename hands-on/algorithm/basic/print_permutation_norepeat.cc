#include <cstdio>
#include <algorithm>
using namespace std;

void print_permutation(int *A, int n, int cur);
void print_permutation_swap(int *A, int n, int cur);
const int maxn = 1024;
int A[maxn+10];
int P[maxn+10];
int id=0;
int main()
{
  int n;
  while(scanf("%d", &n) == 1) {
      if(n>maxn) {
          printf("n is too large(>1024)!\n");
          return -1;
      }
      for(int i=0; i<n; ++i) scanf("%d", P+i); 
      sort(P,P+n);
      printf("==============\n");
      do {
        for (int i=0; i<n; ++i) printf ("%d ", P[i]);
        printf("\n");
      } while(next_permutation(P, P+n));
      printf("==============\n");
      sort(P,P+n);
      id=0;
      print_permutation(A,n,0);
      copy(P,P+n,A);
      id=0;
      printf("==============\n");
      print_permutation_swap(A,n,0);
  }
  return 0;
}


void print_permutation_swap(int *A, int n, int cur)
{
    if (cur == n) {
        printf("%d. ",++id);
        for (int i=0; i<n; ++i) printf ("%d ", A[i]);
        printf("\n");
        return;
    }
    int key = A[cur];
    for (int i=cur; i<n; ++i) {
        // skip swapping if values are equal ** and it's not equal to previous one after it's sorted**
        if (i != cur && (A[i] == key || A[i] == A[i-1])) continue; 
        A[cur] = A[i];
        A[i] = key;
        print_permutation_swap(A,n,cur+1);
        A[i] = A[cur];
    }
    A[cur] = key;
}

void print_permutation(int *A, int n, int cur) {
    if (cur == n) {
        printf("%d. ",++id);
        for (int i=0; i<n; ++i) printf("%d ", A[i]);
        printf("\n");
        return;
    }
    for (int i=0; i<n; ++i) {
        int c1 = 0, c2 = 0;
        if ( i!=0 && P[i] == P[i-1]) continue; // not to use the same value on the same place for more than one time
        for (int j=0; j<cur; ++j) c1 += (A[j] == P[i]);
        for (int k=0; k<n; ++k) c2 += (P[k] == P[i]);
        if (c1 <c2) {
            A[cur] = P[i];
            print_permutation(A,n,cur+1);
        }
    }
}
