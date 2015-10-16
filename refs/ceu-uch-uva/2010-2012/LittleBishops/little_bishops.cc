#include <cstdio>
#include <cstdlib>
#include "backtracking_solver.h"

class LittleBishops : public BackTrackingSolver {
  int B;
  int N;
  int num_bishops_en_tablero;
  int *state, *diag1, *diag2;
  int num_solutions;
public:
  LittleBishops(int B, int N) : B(B), N(N) {
    num_solutions          = 0;
    num_bishops_en_tablero = 0;
    state = new int[N*N];
    diag1 = new int[2*N];
    diag2 = new int[2*N];
    for (int i=0; i<2*N; ++i)
      diag1[i] = diag2[i] = 0;
  }
  ~LittleBishops() {
    delete[] state;
    delete[] diag1;
    delete[] diag2;
  }
  void procesar_solucion(int k) {
    ++num_solutions;
    
    int l=0;
    for (int i=0; i<N; ++i) {
      for (int j=0; j<N; ++j)
	printf ("%c ", (state[l++])?'X':'O');
      printf ("\n");
    }
    printf ("\n");
  }
  bool es_terminal(int k) {
    return (k == N*N);
  }
  bool es_factible(int k) {
    return num_bishops_en_tablero == B;
  }
  int diagonal1(int k) {
    int f = k/N;
    int c = k%N;
    return diag1[f+c];
  }
  int diagonal2(int k) {
    int f = k/N;
    int c = k%N;
    return diag2[N-1+f-c];
  }
  void set_diagonal1(int k, int v) {
    int f = k/N;
    int c = k%N;
    diag1[f+c] = v;
  }
  int set_diagonal2(int k, int v) {
    int f = k/N;
    int c = k%N;
    diag2[N-1+f-c] = v;
  }
  bool es_prometedor(int i, int k) {
    if ((i == 0) ||
	((i == 1) &&
	 (num_bishops_en_tablero+1 <= B) &&
	 (diagonal1(k) == 0) &&
	 (diagonal2(k) == 0)))
      return true;
    return false;
  }
  int numero_hijos(int k) {
    return 2;
  }
  void ramificar(int i, int k) {
    if (i == 1) {
      set_diagonal1(k, 1);
      set_diagonal2(k, 1);
      state[k] = 1;
      ++num_bishops_en_tablero;
    }
  }
  void restaurar(int i, int k) {
    if (i == 1) {
      set_diagonal1(k, 0);
      set_diagonal2(k, 0);
      state[k] = 0;
      --num_bishops_en_tablero;
    }
  }
  void print() { printf ("%d\n", num_solutions); }
};

int main(int argc, char **argv) {
  int N, B;
  N = atoi(argv[1]);
  B = atoi(argv[2]);
  LittleBishops problem(B,N);
  problem.Solve(0);
  problem.print();
  return 0;
}
