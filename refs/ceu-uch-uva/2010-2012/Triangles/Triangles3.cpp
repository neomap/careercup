/** 11866
 * 
 * Triangles.cpp
 * 
 **/
#include <iostream>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

int main()
{
  int cont = 0;
  int rangomin = 0;
  int rangomax = 0;
  int n = 0;
	
  cin >> n;
	
  for(int x = 0; x<n; ++x) {
    cin >> rangomin >> rangomax;
    int cont1 = 0;
    int cont3 = 0;

    // sum(R2*i - 2*i*i + 2*i, i, R1, (R2+1)/2), simpsum;
    int m1 = MIN(rangomax,(rangomax+1)/2);
    int rangomax_plus_one  = rangomax+1;
    int rangomin_minus_one = rangomin-1;
    int sum_R2i = rangomax*(( rangomax_plus_one*rangomax_plus_one/4 +
			      rangomax_plus_one/2)/2 -
			    (rangomin + rangomin_minus_one*rangomin_minus_one - 1)/2);
    int sum_2ii = 2*((rangomax_plus_one*rangomax_plus_one*rangomax_plus_one/4 + 
		      3*rangomax_plus_one*rangomax_plus_one/4 +
		      rangomax_plus_one/2)/6 -
		     (rangomin + 2*rangomin_minus_one*rangomin_minus_one*rangomin_minus_one +
		      3*rangomin_minus_one*rangomin_minus_one - 1)/6);
    int sum_2i = 2*(( rangomax_plus_one*rangomax_plus_one/4 + rangomax_plus_one/2)/2 -
		    (rangomin + rangomin_minus_one*rangomin_minus_one - 1)/2);
    int cont2 = sum_R2i - sum_2ii + sum_2i;
    for(int i = rangomin; i<=rangomax; ++i) {
      if (i > 2) {
	int	m		    = MAX(i, rangomax-i+2);
	// maxima: sum(R - j + 1, j, m, R-1), simpsum;
	//
	// latex: \sum_{j=m}^{R-1} ( R - j + 1 )
	int	sum_R		    = (rangomax-m)*rangomax;
	int	sum_1		    = rangomax-m;
	int	rangomax_minus_one  = rangomax-1;
	int	m_minus_one	    = m-1;
	int	sum_J		    =
	  (rangomax+rangomax_minus_one*rangomax_minus_one-1)/2 - (m+m_minus_one*m_minus_one-1)/2;
	cont1			   += sum_R + sum_1 - sum_J;
      }
      if(2*i <= rangomax+1) cont3 += (rangomax-2*i+2)*i;
      cont1++;
    }
    if(rangomin==1) --cont1;
    cout << cont1 + cont2 << " " << cont2 << " " << cont3 << endl;
  }
}
