#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;

// tipo par, sirve para guardar en memoria el grafo que representa las
// relaciones parentales
struct pair_t {
  unsigned long int a, b;
  pair_t() : a(-1), b(-1) { }
  pair_t(unsigned long int a, unsigned long int b) : a(a), b(b) { }
  bool operator<(const pair_t &other) const {
    if (a < other.a) return true;
    if (a > other.a) return false;
    if (b < other.b) return true;
    return false;
  }
};

typedef pair_t frac_t;

// para acelerar los calculos, asignamos a pares de numeros el grado
// de parentesco que se calculo en un momento anterior
typedef map<pair_t,frac_t> mem_t;
mem_t mem;

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
frac_t degree(int a, int b) {
  // si es -1, no tienen padre, luego no tienen relacion
  if (a == -1 || b == -1) return frac_t(0,1);
  // siempre necesitamos que se cumpla la condicion inv_top_order[a] >= inv_top_order[b]
  if (inv_top_order[a] < inv_top_order[b]) swap(a,b);
  // si son el mismo, la relacion es 100%
  if (a == b) return frac_t(1,1);
  pair_t p(a,b);
  // buscamos en la memoria el par actual
  mem_t::iterator it = mem.find(p);
  if (it != mem.end()) return it->second;
  // calculamos la relacion entre ambos monstruos, usando operaciones
  // de fracciones
  frac_t d1 = degree(monsters[a].a, b);
  d1.b *= 2;
  frac_t d2 = degree(monsters[a].b, b);
  d2.b *= 2;
  
  frac_t result(d1.a*d2.b + d2.a*d1.b, d1.b*d2.b);
  if (result.a != 0 && result.a % result.b == 0) {
    result.b = result.b/result.a;
    result.a = 1;
  }
  // memorizamos
  mem[p]   = result;
  return result;
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
    frac_t d = degree(a-1, b-1);
    printf("%g%%\t\t%ld/%ld\n", d.a/double(d.b)*100, d.a, d.b);
  }
  return 0;
}
