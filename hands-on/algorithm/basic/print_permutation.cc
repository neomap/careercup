#include <cstdio>

using namespace std;

void print_permutation_swap(int *A, int n, int cur);
void print_permutation_tag(int *A, int n, int cur);

const int maxn = 1024;
int A[maxn+10];
int main()
{
  int n;
  while(scanf("%d", &n) == 1) {
      if(n>maxn) {
          printf("n is too large(>1024)!\n");
          return -1;
      }
//      for(int i=0; i<n; ++i) A[i] = i+1;
//      print_permutation_swap(A,n,0);
      print_permutation_tag(A,n,0);
  }
  return 0;
}


void print_permutation_swap(int *A, int n, int cur)
{
    if (cur == n) {
        for (int i=0; i<n; ++i) printf ("%d ", A[i]);
        printf("\n");
        return;
    }
    int key = A[cur];
    for (int i=cur; i<n; ++i) {
        A[cur] = A[i];
        A[i] = key;
        print_permutation_swap(A,n,cur+1);
        A[i] = A[cur];
    }
    // !!make sure to restore A[cur], otherwise its value will be n after return
    A[cur] = key;
}

void print_permutation_tag(int *A, int n, int cur) {
    if (cur == n) {
        for (int i=0; i<n; ++i) printf("%d ", A[i]);
        printf("\n");
        return;
    }
    for (int i=1; i<=n; ++i) {
        bool used = false;
        for (int j=0; j<=cur; ++j) {
            if (A[j] == i) {
                used = true;
                break;
            }
        }
        if (!used) {
            A[cur] = i;
            print_permutation_tag(A,n,cur+1);
        }
    }
}
