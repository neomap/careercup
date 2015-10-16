#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;

// tipo par, sirve para guardar en memoria el grafo que representa las
// relaciones parentales
struct pair_t {
  int a, b;
  pair_t() : a(-1), b(-1) { }
  pair_t(int a, int b) : a(a), b(b) { }
  bool operator<(const pair_t &other) const {
    if (a < other.a) return true;
    if (a > other.a) return false;
    if (b < other.b) return true;
    return false;
  }
};

// para acelerar los calculos, asignamos a pares de numeros el grado
// de parentesco que se calculo en un momento anterior
map<pair_t,double> mem;

// numero de monstruos
int	 num_monsters;
// grafo de dependencias [i] -> (a,b) 
pair_t	*monsters;
// guarda el orden topologico de los monstruos
int	*topologic_order;
// indica en que posicion del orden topologico esta cada monstruo
int     *inv_top_order;
// para el orden topologico (auxiliar)
bool    *visitado;

// calcula el grado de relacion de monstruos
double degree(int a, int b) {
  // si es -1, no tienen padre, luego no tienen relacion
  if (a == -1 || b == -1) return 0.0f;
  // siempre necesitamos que se cumpla la condicion inv_top_order[a] >= inv_top_order[b]
  if (inv_top_order[a] < inv_top_order[b]) swap(a,b);
  // si son el mismo, la relacion es 100%
  if (a == b) return 1.0;
  pair_t p(a,b);
  // buscamos en la memoria el par actual
  map<pair_t,double>::iterator it = mem.find(p);
  if (it != mem.end()) return it->second;
  // calculamos la relacion entre ambos monstruos
  double d = 0.5 * degree(monsters[a].a, b) + 0.5 * degree(monsters[a].b, b);
  // memorizamos
  mem[p]   = d;
  return d;
}

// calcula el orden topologico
void topologic_sort(int m, int &stack_top) {
  if (visitado[m]) return;
  visitado[m]		     = true;
  if (monsters[m].a != -1)
    topologic_sort(monsters[m].a, stack_top);
  if (monsters[m].b != -1)
    topologic_sort(monsters[m].b, stack_top);
  topologic_order[stack_top] = m;
  inv_top_order[m]	     = stack_top;
  ++stack_top;
}

int main() {
  scanf("%d", &num_monsters);
  int	n;
  scanf("%d", &n);
  monsters	  = new pair_t[num_monsters];
  topologic_order = new int[num_monsters];
  inv_top_order	  = new int[num_monsters];
  visitado        = new bool[num_monsters];
  for (int i=0; i<num_monsters; ++i)
    visitado[i]	  = false;
  //fprintf(stderr, "Digraph wop{\n");
  for (int i=0; i<n; ++i) {
    int c, p1, p2;
    // cargamos una arista del grafo de dependencias
    scanf("%d %d %d", &c, &p1, &p2);
    // OJO: -1 para que todo empiece en 0
    monsters[c-1].a = p1-1;
    monsters[c-1].b = p2-1;
    //fprintf(stderr, "%d -> %d;\n%d -> %d;\n", c, p1, c, p2);
  }
  //fprintf(stderr, "}\n");
  int stack_top = 0;
  for (int i=0; i<num_monsters; ++i)
    topologic_sort(i, stack_top);
  scanf("%d", &n);
  for (int i=0; i<n; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    // resolvemos el caso actual
    double d = degree(a-1, b-1);
    printf("%g%%\n", d*100);
  }
  return 0;
}
