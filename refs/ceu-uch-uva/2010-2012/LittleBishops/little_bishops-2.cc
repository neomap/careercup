#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "backtracking_solver.h"

#define VACIO -1111

class LittleBishops : public BackTrackingSolver {
  int B;
  int N;
  int num_bishops_en_tablero;
  int *diag1, *diag2, *pos;
  int num_solutions;
public:
  LittleBishops(int B, int N) : B(B), N(N) {
    num_solutions          = 0;
    num_bishops_en_tablero = 0;
    diag1 = new int[2*N-1];
    diag2 = new int[2*N-1];
    pos = new int[2*N-1];
    for (int i=0; i<2*N-1; ++i)
      diag1[i] = diag2[i] = 0;
  }
  ~LittleBishops() {
    delete[] diag1;
    delete[] diag2;
    delete[] pos;
  }
  void procesar_solucion(int k) {
    ++num_solutions;
    for (int i=0; i<2*N-1; ++i)
      printf ("%d ", pos[i]);
    printf ("\n");
  }
  bool es_terminal(int k) {
    return (k == 2*N-1);
  }
  bool es_factible(int k) {
    return num_bishops_en_tablero == B;
  }
  bool es_prometedor(int i, int k) {
    if (i == 0) return true;
    if (i != 0 && num_bishops_en_tablero+1 > B)
      return false;
    if (k < N) {
      int div2 = int(ceilf(float(N)/2));
      printf ("%d %d\n", N, div2);
      if (k < div2) {
	if (i >= div2 + k - 1) return false;
	if (i <= 0 - k + 1) return false;
      }
      else {
	if (i >= N-1 - (k - div2)) return false;
	if (i <= -1 + (k - div2)) return false;
      }
      return diag1[i] == 0;
    }
    else {
      int div2 = N/2;
      if (k < div2) {
	if (i >= div2 + k - 1) return false;
	if (i <= 0 - k + 1) return false;
      }
      else {
	if (i >= N-1 - (k - div2)) return false;
	if (i <= -1 + (k - div2)) return false;
      }
      return diag2[i] == 0;
    }
    return true;
  }
  int numero_hijos(int k) {
    return N+1;
  }
  void ramificar(int i, int k) {
    if (i != 0) {
      if (k < N)
	diag1[i] = 1;
      else diag2[i] = 1;
      ++num_bishops_en_tablero;
    }
    pos[k] = i;
  }
  void restaurar(int i, int k) {
    if (i != 0) {
      if (k < N)
	diag1[i] = 0;
      else diag2[i] = 0;
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
