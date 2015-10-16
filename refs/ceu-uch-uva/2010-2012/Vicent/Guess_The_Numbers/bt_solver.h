#ifndef BT_SOLVER_H
#define BT_SOLVER_H

class BackTrackingSolver {
	public:
		virtual ~BackTrackingSolver() { }
	virtual void procesar_solucion(int k)    = 0;
	virtual bool es_terminal(int k)          = 0;
	virtual bool es_factible(int k)          = 0;
	virtual bool es_prometedor(int i, int k) = 0;
	virtual int  numero_hijos(int k)         = 0;
	virtual void ramificar(int i, int k)     = 0;
	virtual void restaurar(int i, int k)     = 0;
  
	bool Solve(int k) {
		bool ret = false;
		if (es_terminal(k)) {
			if (es_factible(k)) {
				procesar_solucion(k);
				ret = true;
      		}
    	}
    	else {
      		for (int i=numero_hijos(k)-1; i>=0; --i)
				if (es_prometedor(i,k)) {
	  				ramificar(i,k);
	  				if (Solve(k+1)) ret = true;
	  				restaurar(i,k);
				}
    	}
    	return ret;
	}
};

#endif // BT_SOLVER_H
