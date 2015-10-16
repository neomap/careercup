#include "bt_solver.h"

#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

string expresion = "";
int pos = 0;
int val = 0;
int N, resultado;
int valores[5];
int permutados[5];
bool usados[5];


int  exp();
char consultar();
void consumir();
int  operar(char op,int a,int b);
int sigVal();
bool solucionado = false;

class Solver: public BackTrackingSolver {
	public:
		Solver() { 
			solucionado = false;
		}

		virtual void procesar_solucion(int k) {
			solucionado = true;
		}

		virtual bool es_terminal(int k) {
			return ( k == N );
		}

		virtual bool es_factible(int k) {
			pos = val = 0;
			return ( exp() == resultado );
		}

		virtual bool es_prometedor(int i, int k) {
			return ( k <= N && !usados[i] );
		}

		virtual int  numero_hijos(int k) {
			return N;
		}

		virtual void ramificar(int i, int k) {
			usados[i] = true;
			permutados[k] = valores[i];
		}

		virtual void restaurar(int i, int k) {
			usados[i] = false;
		}
	
	private:
		int mapeado[5];
};

int main(int argc, char** argv) {
	while(true) {
		cin >> N;
		for(int i=0;i<N;++i) {
			cin >> valores[i];
			usados[i] = false;
		}
		cin >> resultado;

		if(N == 0 && resultado == 0) break;

		cin >> expresion;
	
		Solver s;
		s.BackTrackingSolver::Solve(0);

		if(solucionado)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}

int exp() {
	if(consultar() == '(') {
		consumir();
		int res1 = exp();
		char op  = consultar();
		consumir();
		int res2 = exp();
		consumir();
		
		return operar(op,res1,res2);
	} else {
		consumir();
		return sigVal();
	}
}

char consultar() {
	return expresion[pos];
}

void consumir() {
	++pos;
}

int operar(char op,int a,int b) {
	switch(op) {
		case '+':return (a+b);
		case '-':return (a-b);
		case '*':return (a*b);
	}
}

int sigVal() {
	return permutados[val++];
}
