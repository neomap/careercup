#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/// para evitar problemas de estabilidad numerica
#define EPSILON .00001
/// funcion inline para calcular el area de un triangulo
#define triangle_area(a, b ,c) fabs(signed_triangle_area((a), (b), (c)))

/// Clase punto
struct Point {
  double x;
  double y;
  
  Point(){}
  
  Point(double x, double y) : x(x), y(y) {}
  
  // RESTA de puntos
  Point operator-(const Point &other) const {
    return Point(x - other.x, y - other.y);
  }
  
  // SUMA de puntos
  Point operator+(const Point &other) const {
    return Point(x + other.x, y + other.y);
  }
  
  // modulo del vector representado por dicho punto
  double modulo() const { return sqrt(x*x + y*y); }
  
  /// ordena de abajo a arriba y de izquierda a derecha
  bool operator<(const Point &other) const {
    if (y != other.y) return y<other.y;
    return x < other.x;
  }
  
  bool operator!=(const Point &other) const{
    return (x!=other.x || y!=other.y);
  }
  
  // DIVISION por un escalar
  Point operator/(double a) const {
    return Point(x/a, y/a);
  }
  
  // para DEBUG ;)
  friend ostream &operator<<(ostream &os, const Point &p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
  }
};

/// Clase para rectas
struct Line {
  // a * x b * y + c = 0
  double a; // x-coeff
  double b; // y-coeff
  double c; // constante
  
  Line() { }
  
  // construye una recta dados dos puntos
  Line(const Point &p1, const Point &p2) {
    if (p1.x == p2.x) {
      a = 1;
      b = 0;
      c = -p1.x;
    }
    else {
      b = 1;
      a = (p2.y-p1.y) / (p1.x-p2.x);
      c = -(a * p1.x) - (b * p1.y);
    }
  }
  
  // construye una recta dado un punto y la pendiente
  Line(const Point &p, double m) {
    a = -m;
    b = 1;
    c = -((a*p.x) + (b*p.y));
  }
  
  // devuelve una recta paralela a partir de la recta actual y un
  // punto por donde queremos que pase la paralela
  Line paralel_at(const Point &p) {
    Line l;
    l.a = a;
    l.b = b;
    l.c = -(a * p.x) - (b * p.y);
    return l;
  }
  
  // construye una recta perpendicular a dos puntos dados, y que pasa
  // por el punto medio de ambos
  static Line mediatriz(const Point &p1, const Point &p2) {
    Point medio = (p1 + p2) / 2.0;
    return mediatriz(p1, p2, medio);
  }
  
  // construye una recta perpendicular a dos puntos dados, y que pasa
  // por un tercero
  static Line mediatriz(const Point &p1, const Point &p2, const Point &p3) {
    Line  l(p1, p2);
    //cout << "linea: " << l << endl;
    if (l.a == 0) {
      l.a = 1;
      l.b = 0;
    }
    else if (l.b == 0) {
      l.a = 0;
      l.b = 1;
    }
    else l.a = -1/l.a;
    l.c = -(l.a * p3.x) - (l.b * p3.y);
    return l;
  }
  
  // indica si son paralelas
  bool paralelQ(const Line &l) {
    return ( (fabs(a - l.a) <= EPSILON) &&
	     (fabs(b - l.b) <= EPSILON) );
  }
  
  // indica si son la misma recta
  bool same_lineQ(const Line &l) {
    return ( paralelQ(l) && (fabs(c - l.c) <= EPSILON) );
  }
  
  // devuelve el punto interseccion de dos rectas
  Point intersect(const Line &l) {
    // requiere comprobar primero que no sean paralelas y que no sean
    // la misma
    Point p;
    p.x = ( (l.b * c - b*l.c)  / (l.a*b - a*l.b) );
    if (fabs(b) > EPSILON) /* test for vertical line */
      p.y = -(a * p.x + c) / b;
    else p.y = -(l.a * p.x + l.c) / l.b;
    return p;
  }
  
  // evalua la ecuacion de la recta sobre el punto dado
  double solve(const Point &p) {
    return a*p.x + b*p.y + c;
  }
  
  // indica si un punto esta en la recta
  bool is_inline(const Point &p) {
    return fabs(solve(p)) < EPSILON;
  }
  
  // devuelve el punto de la recta mas cercano al punto dado
  Point clossest_point(const Point &p) {
    Point c;
    if (fabs(b) <= EPSILON) { /* vertical */
      c.x = -this->c;
      c.y = p.y;
    }
    else if (fabs(a) <= EPSILON) { /* horizontal */
      c.x = p.x;
      c.y = this->c;
    }
    else {
      Line perp(p, 1/a);
      c = intersect(perp);
    }
    return c;
  }
  
  // indica si el tercer punto esta dentro del segmento formado por p1
  // y p2. p1 y p2 deben ser puntos de una misma recta
  static bool is_in_segment(const Point &p1, const Point &p2, const Point &p) {
    return ( (p.x >= min(p1.x, p2.x)) &&
	     (p.x <= max(p1.x, p2.x)) &&
	     (p.y >= min(p1.y, p2.y)) &&
	     (p.y <= max(p1.y, p2.y)) );
  }
  
  // para DEBUG
  friend ostream &operator<<(ostream &os, const Line &l) {
    os << l.a << "x + " << l.b << "y + " << l.c;
    return os;
  }

};

/* calcula el area del triangulo (con signo) */
double signed_triangle_area(const Point &a, const Point &b, const Point &c)
{
  return ((a.x*b.y - a.y*b.x + a.y*c.x - a.x*c.y + b.x*c.y - c.x*b.y) / 2.0 );
}

/** ordena y elimina duplicados **/
void sort_and_remove_duplicates(vector<Point> &in)
{  
  sort(in.begin(), in.end());  
  unsigned int copy=0;
  for (unsigned int pos = 1; pos < in.size(); ++pos)
    if (in[copy] != in[pos]) in[++copy] = in[pos];
  in.resize(copy+1);
}

/* dice si tres puntos son colineales */
bool collinear(const Point &a, const Point &b, const Point &c)
{
  return (triangle_area(a, b, c) < EPSILON);
}

/* indica si el giro de estos 3 puntos es a izquierda */
bool ccw(const Point &a, const Point &b, const Point &c)
{
  return (signed_triangle_area(a, b, c) > EPSILON);
}

/** predicado para ordenar por angulo **/
struct sort_points_by_angle{
  Point first_Point;
  sort_points_by_angle(Point p) : first_Point(p) {}
  bool operator()(const Point &p1, const Point &p2) const {
    if(collinear(first_Point, p1, p2)) {
      if( (first_Point - p1).modulo() <= (first_Point - p2).modulo() )  //distancias
	return true;
      else return false;
    }
    if(ccw(first_Point, p1, p2)) return true;
    else return false;
  }
};

/* Clase poligono */
class ConvexPol {
  vector<Point> hull;
public:
  Point &operator[](int i) { return hull[i]; }
  Point  operator[](int i) const { return hull[i]; }
  void clear() { hull.clear(); }
  unsigned int size() const { return hull.size(); }
  void intersect(const Line &lin, vector<Point> &out) {
    // interseccion con todo el convex_hull
    for (unsigned int i=1; i<hull.size(); ++i) {
      Line l(hull[i-1], hull[i]);
      // si no son paralelas y no son la misma, calculamos la
      // interseccion
      if (!l.paralelQ(lin) &&
	  !l.same_lineQ(lin)) {
	Point ipoint = l.intersect(lin); // interseccion
	if (Line::is_in_segment(hull[i-1], hull[i], ipoint))
	  // insertamos el punto en el conjunto de entrada si esta
	  // dentro del segmento definido por los puntos i y el i-1
	  out.push_back(ipoint);
      }
    }    
  }
  
  /** construye el convex hull para los puntos dados **/
  void build_convex_hull(vector<Point> &in) {
    Point first_Point;
    hull.clear();
    /* caso especial */
    if(in.size() <= 3){
      for(unsigned int i=0; i<in.size(); i++) hull.push_back(in[i]);
      if (in.size() > 0) hull.push_back(in[0]);
      return;
    }
    /* eliminamos duplicados */
    sort_and_remove_duplicates(in);
    first_Point = in[0];
    vector<Point>::iterator iter;
    iter = in.begin();
    /* ordenamos por angulos */
    sort(++iter, in.end(), sort_points_by_angle(first_Point));
    hull.push_back(first_Point);
    hull.push_back(in[1]);
    in.push_back(first_Point); //centinela 
    /* bucle general */
    for(unsigned int i=2; i<in.size();) {
      if(!ccw(hull[hull.size()-2],hull[hull.size()-1],in[i])) hull.pop_back();
      else hull.push_back(in[i++]);
    }
  }

  /** devuelve el area del Convex Hull **/
  double get_area() const {
    double area=0;
    if(hull.size() > 3) {
      for(unsigned int i=2; i<hull.size()-1; i++){
	area+= triangle_area(hull[i], hull[i-1], hull[0]);    
      }
    }
    return area;
  }

  // para DEBUG
  friend ostream &operator<<(ostream &os, const ConvexPol &pol) {
    os << "[ ";
    for (unsigned int i=0; i<pol.size(); ++i)
      os << pol[i] << " ";
    os << "]";
    return os;
  }
};

int main()
{
  vector<Point> in;
  
  in.push_back(Point(0,0));
  in.push_back(Point(10,0));
  in.push_back(Point(10,10));
  in.push_back(Point(0,10));
  
  ConvexPol hull;
  Point last(0.0, 0.0);
  double x, y;
  string word;
  
  hull.build_convex_hull(in);
  
  while(cin >> x >> y >> word) {
    Point p(x, y);
    Line mediatriz = Line::mediatriz(last, p);
    if (word == "Same") {
      /* En este caso sabemos que nuestro tesoro esta en la
	 interseccion de la mediatriz del segmento que hay entre el
	 punto anterior y el actual con el convex hull. Por tanto area
	 = 0.00, se encuentra en un segmento de linea */
      cout << "0.00" << endl;
      in.clear();
      hull.intersect(mediatriz, in);
    }
    else {
      bool positive = true;
      double v = mediatriz.solve(p);
      // sacamos el signo que sera el bueno
      positive = ( (v>0 && word == "Hotter") ||
		   (v<0 && word == "Colder") );
      // interseccion con todo el convex_hull
      hull.intersect(mediatriz, in);
      // recorremos los puntos eliminando aquellos que esten en el lado
      // equivocado de la mediatriz
      int j = 0;
      for (unsigned int i=0; i<in.size(); ++i) {
	v = mediatriz.solve(in[i]);
	if (!(!positive || v < -EPSILON) ||
	    !(positive || v > EPSILON))
	  in[j++] = in[i];
      }
      in.resize(j);
    }
    // construimos el convex hull de nuevo
    hull.build_convex_hull(in);
    // calculamos el area
    printf ("%.2f\n", hull.get_area());
    //cout << hull << endl;
    last = p;
  }
  return 0;
}
