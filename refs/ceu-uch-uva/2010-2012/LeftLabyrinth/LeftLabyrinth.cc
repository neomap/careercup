#include <cstdio>
#include <cstdlib>

//#define DEBUG

#define ERROR	       -1
#define ABAJO		0
#define IZQUIERDA	1
#define DERECHA		2
#define ARRIBA		3

#define PASILLO '.'
#define MURO    '#'
#define OCUPADA 'O'

#define mover_izquierda --c,dir=IZQUIERDA
#define mover_derecha   ++c,dir=DERECHA
#define mover_arriba    --f,dir=ARRIBA
#define mover_abajo     ++f,dir=ABAJO

#define mirar_izquierda l[f][c-1]
#define mirar_derecha   l[f][c+1]
#define mirar_arriba    l[f-1][c]
#define mirar_abajo     l[f+1][c]

class Laberinto {
  int	 num_filas, num_columnas;
  char	*data;
public:
  Laberinto(FILE *f) {
    fscanf(f, "%d", &num_filas);
    fscanf(f, "%d", &num_columnas);
    char salto_de_linea;
    fscanf(f, "%c", &salto_de_linea);
    data   = new char[num_filas * num_columnas];
    int	 k = 0;
    for (int i=0; i<num_filas; ++i) {
      for (int j=0; j<num_columnas; ++j)
	fscanf(f, "%c", &data[k++]);
      fscanf(f, "%c", &salto_de_linea);
    }
  }
  ~Laberinto() { delete[] data; }
  void print() {
    int k=0;
    for (int i=0; i<num_filas; ++i) {
      for (int j=0; j<num_columnas; ++j)
	printf ("%c", data[k++]);
      printf ("\n");
    }
  }
  char *operator[](int fila) {
    return data + fila * num_columnas;
  }
  bool damePosicionEntrada(int &f, int &c) {
    // Busca primera pared
    bool encontradoMuro = false;
    f = 0; c = 0;
    int k=0;
    for (int i=0; i<num_filas && !encontradoMuro; ++i) {
      for (int j=0; j<num_columnas && !encontradoMuro; ++j) {
	if (data[k++] == MURO) {
	  f = i;
	  c = j-1;
	  encontradoMuro = true;
	}
      }
    }
    if (!encontradoMuro) return ERROR;
    
    // ya sabemos que el primer muro esta en (f,c+1)
    bool	 encontrada = false;
    int		 dir	    = ABAJO;
    Laberinto	&l	    = *this;
    
    while(!encontrada) {
#ifdef DEBUG
      l[f][c] = 'P';
      printf ("%d %d %d\n", f, c, dir);
      print();
#endif
      
      if ((l[f+1][c] == MURO && l[f-1][c] == MURO) ||
	  (l[f][c+1] == MURO && l[f][c-1] == MURO))
	encontrada = true;
      else {
	switch(dir) {
	case ABAJO:
	  if (mirar_abajo == MURO) mover_izquierda;
	  else if (mirar_derecha == PASILLO) mover_derecha;
	  else mover_abajo;
	  break;
	case ARRIBA:
	  if (mirar_arriba == MURO) mover_derecha;
	  else if (mirar_izquierda == PASILLO) mover_izquierda;
	  else mover_arriba;
	  break;
	case IZQUIERDA:
	  if (mirar_izquierda == MURO) mover_arriba;
	  else if (mirar_abajo == PASILLO) mover_abajo;
	  else mover_izquierda;
	  break;
	case DERECHA:
	  if (mirar_derecha == MURO) mover_abajo;
	  else if (mirar_arriba == PASILLO) mover_arriba;
	  else mover_derecha;
	  break;
	}
      }
    }
    return dir;
  }
  bool esPlaza(int f, int c) {
    Laberinto &l = *this;
    int ocupada_arriba    = (mirar_arriba    == OCUPADA);
    int ocupada_abajo     = (mirar_abajo     == OCUPADA);
    int ocupada_izquierda = (mirar_izquierda == OCUPADA);
    int ocupada_derecha   = (mirar_derecha   == OCUPADA);
    if (ocupada_arriba && ocupada_abajo &&
	ocupada_derecha && ocupada_izquierda) return true;
    return false;
  }
  bool mover(int &f, int &c, int &dir) {
    Laberinto &l = *this;
    // miramos en las cuatro direcciones
    int ocupada_arriba    = (mirar_arriba    != PASILLO);
    int ocupada_abajo     = (mirar_abajo     != PASILLO);
    int ocupada_izquierda = (mirar_izquierda != PASILLO);
    int ocupada_derecha   = (mirar_derecha   != PASILLO);
    switch(dir) {
    case ARRIBA: {
      int n = ocupada_derecha + ocupada_izquierda + ocupada_arriba;
      if (n == 3) return false;
      if (!ocupada_izquierda) mover_izquierda;
      else if (!ocupada_arriba) mover_arriba;
      else if (!ocupada_derecha) mover_derecha;
      else return false;
    }
      break;
    case ABAJO: {
      int n = ocupada_derecha + ocupada_izquierda + ocupada_abajo;
      if (n == 3) return false;
      if (!ocupada_derecha) mover_derecha;
      else if (!ocupada_abajo) mover_abajo;
      else if (!ocupada_izquierda) mover_izquierda;
      else return false;
    }
      break;
    case IZQUIERDA: {
      int n = ocupada_izquierda + ocupada_arriba + ocupada_abajo;
      if (n == 3) return false;
      if (!ocupada_abajo) mover_abajo;
      else if (!ocupada_izquierda) mover_izquierda;
      else if (!ocupada_arriba) mover_arriba;
      else return false;
    }
      break;
    case DERECHA: {
      int n = ocupada_derecha + ocupada_arriba + ocupada_abajo;
      if (n == 3) return false;
      if (!ocupada_arriba) mover_arriba;
      else if (!ocupada_derecha) mover_derecha;
      else if (!ocupada_abajo) mover_abajo;
      else return false;
    }
      break;
    }
    l[f][c] = OCUPADA;
#ifdef DEBUG
    printf ("%d %d %d\n", f, c, dir);
    l.print();
#endif
    return true;
  }
};

  int main() {
    int f, c;
    Laberinto l(stdin);
    int dir = l.damePosicionEntrada(f, c);
    if (dir == -1) {
      printf ("NO\n");
      return 0;
    }
    l[f][c] = OCUPADA;
    // algoritmo de laberinto a izquierdas
    if (!l.mover(f,c,dir)) {
      printf ("NO\n");
      return 0;
    }
    while(!l.esPlaza(f,c)) {
      if (!l.mover(f,c,dir)) {
	printf ("NO\n");
	return 0;
      }
    }
    if (l.esPlaza(f,c)) printf ("YES\n");
    else printf ("NO\n");
    return 0;
  }
