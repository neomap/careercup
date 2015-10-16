#ifndef PTR_H
#define PTR_H

#define IncRef(x) (x)->incRef()
#define DecRef(x) do { if ((x)->decRef() == 0) {delete (x); }; } while(0);

class Referenced {
  int counts;
public:
  Referenced() : counts(0) { }
  virtual ~Referenced() { }
  void incRef() { ++counts; }
  int decRef() { --counts; return counts; }
  int getCount() { return counts; }
};

// clase para encapsular un puntero, para acelerar la copia de
// objetos
template<typename T>
class Ptr {
private:
  // puntero encapsulado
  T *ptr;
public:
  Ptr() : ptr(0) { }
  
  Ptr(const Ptr &other) : ptr(other.ptr) {
    if (ptr != 0) IncRef(ptr);
  }
  Ptr &operator=(const Ptr &b) {
    if (ptr) DecRef(ptr);
    ptr = b.ptr;
    if (ptr) IncRef(ptr);
    return (*this);
  }
  
  Ptr(T *s) : ptr(s) {
    if (ptr != 0) IncRef(ptr);
  }
  ~Ptr() {
    if (ptr != 0) DecRef(ptr);
  }
  bool Null() const { return ptr == 0; }
  void setNull() { if (ptr) DecRef(ptr); ptr = 0; }
  // sobrecarga de operadores del puntero
  bool operator>(const Ptr &b) const {
    return (*ptr) > (*b.ptr);
  }
  bool operator<(const Ptr &b) const {
    return (*ptr) < (*b.ptr);
  }
  bool operator==(const Ptr &b) const {
    return (*ptr) == (*b.ptr);
  }
  bool operator!=(const Ptr &b) const {
    return (*ptr) != (*b.ptr);
  }
  bool operator<=(const Ptr &b) const {
    return (*ptr) <= (*b.ptr);
  }
  bool operator>=(const Ptr &b) const {
    return (*ptr) >= (*b.ptr);
  }

  // desreferencia del puntero
  T *operator->() {
    return ptr;
  }
  T *operator*() {
    return ptr;
  }
};

#endif
