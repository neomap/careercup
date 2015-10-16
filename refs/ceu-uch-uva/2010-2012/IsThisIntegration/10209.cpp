// JOAN CLIMENT CÍSCAR     <joandelason@gmail.com>

#include <stdio.h>


#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace::std;

#define PI 3.14159265358979323846

int main(){

    float a ;
    cin >> a;
    float A = a*a;
    float B = a*a*PI/4;

    float C = A - B;
    float E = A/4;
    float F = 2*E - C;

    float G = a*a*sqrt(3)/4;


    float h = a*sqrt(3)/2;
    float d = h - a/2;
    float l = d/sqrt(2);
    float H = B/3 - l*sqrt(a*a-l*l);
    float I = l*l;
          float X = 4*I + 4*H;

    float J = 2*E - B/2;
    float K = 2*E - X/2 - 2*J;


          float Y = 4*K;

          float Z = A - X - Y;


    printf("%.3f %.3f %.3f", X, Y, Z);



 printf("\n\n\n");
 system("PAUSE");
 return 0;

}
