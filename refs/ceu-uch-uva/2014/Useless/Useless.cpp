//
//  Useless.cpp
//
//
//  Created by Andrés on 18/11/14.
//
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;


class Punto {

private:
    float x;
    float y;

public:

    Punto(){}

    Punto(float cordx, float cordy){
        this-> x = cordx;
        this-> y = cordy;
    }

    float coordenada_x() const
    {
        return x;
    }


    float coordenada_y() const
    {
        return y;
    }
    
    bool operator <(const Punto &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }

};

float areaParcial(Punto &a,Punto &b)
{
    float p1_x = a.coordenada_x();
    float p1_y = a.coordenada_y();
    float p2_x = b.coordenada_x();
    float p2_y = b.coordenada_y();
    
    return p1_x * p2_y - p2_x * p1_y;
    
}


float cross(const Punto &O, const Punto &A, const Punto &B)
{
    return (A.coordenada_x() - O.coordenada_x()) * (B.coordenada_y() - O.coordenada_y())
    - (A.coordenada_y() - O.coordenada_y()) * (B.coordenada_x() - O.coordenada_x());
}




class Poligono {

private:

    vector<Punto> Puntos;

public:

    Poligono() {}

    void incluir_punto(float x, float y) {

        Puntos.push_back(Punto(x,y));
    }

    float Area()
    {
        if (Puntos.size() == 0) {
            cerr << "WARNING!!! EMPTY POLYGON. Probably you computed convex hull BEFORE computing area" << endl;
        }
        float result = 0;

        for (int i=0; i<Puntos.size()-1; i++)
        {
            result += areaParcial(Puntos[i], Puntos[i+1]);
        }

        float lastPoint= areaParcial(Puntos[Puntos.size()-1],Puntos[0]);

        return fabs((result+lastPoint) * 0.5);
    }

    Poligono convexHull(){
        
        int k=0;
        Poligono resultado;
        vector<Punto> &H = resultado.Puntos;
        H.resize(2*Puntos.size());
        
        sort(Puntos.begin(), Puntos.end());

        for (int i=0; i <Puntos.size(); i++){
            while (k>=2 && cross(H[k-2], H[k-1], Puntos[i]) <= 0) k--;
            H[k++] = Puntos[i];
        }

        for (int i = Puntos.size()-2 , t=k+1; i>=0 ; i--) {
            while (k>= t && cross(H[k-2], H[k-1], Puntos[i]) <= 0) k--;
            H[k++] = Puntos[i];
        }

        H.resize(k);
        
        Puntos.clear();
        
        return resultado;
    }

};


int main () {

    int npoints;
    float x,y;
    int j=1;

    while( cin >> npoints && npoints != 0) {

        Poligono poligono;
        float B, P, Res,A1;
        
        for (int i=0; i< npoints; ++i) {
            cin >> x >> y;
            poligono.incluir_punto(x,y);
            }
        B= poligono.Area();
        A1= poligono.convexHull().Area();

        P = A1- B;
        Res = (P*100) / A1;
        
        
        printf("Tile #%d\n",j);
        j++;
        printf("Wasted Space = %.2f %%",Res);
        printf("\n\n");
            
            
            //cout << "Wasted Space = "<< Res << " %" << endl;
        }
    

    return 0;
}
