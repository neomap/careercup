#include <iostream>
#include <algorithm>
using namespace std;

int main(void) {
	int T, K, N;
	int *L = new int[5000];
	int **F = new int*[4999];
	for(int i=0; i<4999; ++i) F[i] = new int[1008];

	cin >> T;
	for(int caso=0; caso<T; ++caso) {
		cin >> K >> N;
		K += 8;

		for(int i=0; i<N-1; ++i) {
			for(int j=0; j<K; ++j) {
				F[i][j] = 99999999;
			}
		}
		
		//leer los palillos
		for(int l=0; l<N; ++l) cin >> L[l];

		//inicializar
		for(int i=0; i<N-3*(K-1)-2; ++i) {
			int aux = (L[i+1] - L[i]);
			F[i][0] = aux*aux;
		}

		//prog. dinamica
		for(int k=1; k<K; ++k) {

			for(int i=2;i<N-3*(K-(k+1))-2;++i)
				F[i][k] = min(F[i-1][k], F[i-2][k-1]);

		    //suma badness
			for(int i=0;i<N-1;++i) {
				int aux = L[i] - L[i+1];
				F[i][k] += aux*aux;
			}
			

		}

		#if 0
		cout << "N: " << N << endl;
		cout << "K: " << K << endl;
		for(int i=0; i<N-1 +i) {
			for(int j=0; j<K; ++j) {
				cout << F[i][j] << ' ';
			}
			cout << endl;
		}
        #endif

		int minimo = F[0][K-1];
		for(int i=1; i<N-1; ++i) {
				minimo = min(minimo, F[i][K-1]);
		}

		cout << minimo << endl;

	}

	return 0;
}

