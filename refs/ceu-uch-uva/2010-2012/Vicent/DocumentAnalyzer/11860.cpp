#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

/*
Limpia las palabras de un documento sucio y las almacena en un vector
*/
void limpiarDocumento( string documento_sucio, vector<string> &documento );

int main( void ) {

  vector<string> documento; //contiene todo el documento limpio
  map<string,int> palabras; //sirve para saber cuantas veces esta metida cierta palabra en nuestro intervalo
  
  int T;
  cin >> T; //leer numero de documentos
  
  string palabra; //leeremos palabras y las iremos almacenando en el documento sucio
  string documento_sucio = ""; //guardara el documento sucio, tal cual se lee
  
  for ( int i = 0; i < T; ++i ) { //para cada documento...
    while ( cin >> palabra ) { //leer palabra
      if ( palabra == "END" ) break; //si la palabra es "END" hemos terminado
      
      documento_sucio += palabra; //agregamos la palabra al documento sucio
      documento_sucio += " "; //agregamos un espacio en blanco ( cin lee palabras separas por espacios, los espacios tambien hay que meterlos en el documento )
    }
    
    limpiarDocumento( documento_sucio, documento ); //limpiamos el documento
    
    for ( unsigned int k = 0; k < documento.size(); ++k ) { //metemos las palabras del documento limpio en el mapa de palabras
      palabras[ documento[k] ] = 0; //inicializamos a cero porque todavia no hemos metido esa palabra en nuestro intervalo
    }
    
    int N = palabras.size(); //numero de palabras DIFERENTES en nuestro documento
    int sum = 0; //cantidad de palabras diferentes que tenemos metidas en nuestro intervalo
    
    int p = 0; //extremo inferior de nuestro intervalo
    int q = 0; //extremo superior de nuestro intervalo
    
    int min_p; //extremo inferior del intervalo que contiene todas las palabras diferentes del documento
    int min_q; //extremo superior del intervalo que contiene todas las palabras diferentes del documento
    
    int min_width = documento.size(); //inicializamos el ancho minimo del intervalo al valor maximo que puede tomar, para despues ir actualizandolo
    
    while ( q < documento.size() ) { //mientras el extremo superior del intervalo no alcance el final del documento...
      if ( palabras[ documento[q] ] == 0 ) { //si la palabra todavia no estaba dentro del intervalo
        sum++; //sumamos uno a la cantidad de palabras diferentes que tenemos dentro del intervalo
      }
      palabras[ documento[q] ]++; //la palabra aparece una vez mas dentro del intervalo
      
      if ( sum == N ) { //si tenemos todas las palabras diferentes metidas dentro del intervalo...
        if ( (q-p) < min_width ) { //si el intervalo actual es mas pequenyo que el que habia antes...
          min_width = (q-p); //actualizamos el tamanyo del intervalo
          min_p = p+1; //actualizamos el extremo inferior del intervalo que contiene a todas las palabras diferentes
          min_q = q+1; //actualizamos el extremo superior del intervalo que contiene a todas las palabras diferentes
        }
        
        /*
        Ahora que tenemos todas las palabras diferentes dentro del intervalo
        vamos a intentar acortar el tamanyo de ese intervalo moviendo el
        extremo inferior del intervalo
        */
        while ( true ) {
          if ( palabras[ documento[p] ] == 1 ) { //si la palabra que hay en extremo inferior del intervalo solo existe una vez dentro del intervalo...
            sum--; //ahora tenemos una palabra diferente menos dentro del intervalo
          }
          palabras[ documento[p] ]--; //esa palabra aparece una vez menos dentro del intervalo
          
          if ( sum == N ) { //si todavia tenemos todas las palabras diferentes dentro del intervalo...
            p++; //avanzamos el extremo inferior
            
            if ( (q-p) < min_width ) { //si el intervalo actual es mas pequenyo que el que habia antes...
              min_width = (q-p); //actualizamos el tamanyo del intervalo
              min_p = p+1; //actualizamos el extremo inferior del intervalo que contiene a todas las palabras diferentes
              min_q = q+1; //actualizamos el extremo superior del intervalo que contiene a todas las palabras diferentes
            }
          }
          else { //si hemos quitado una palabra que solo aparecia una vez dentro del intervalo...
            palabras[ documento[p] ]++; //volvemos a meter esa palabra en el intervalo
            sum++; //volvemos a tener todas las palabras diferentes dentro del intervalo
            break; //dejamos de intentar reducir el intervalo moviendo el extremo inferior
          }
        }
      }
      
      q++; //aumentamos el extremo superior del intervalo
    }

    cout << "Document " << (i+1) << ": " << min_p << " " << min_q << endl;
    
    documento_sucio = ""; //limpiar documento sucio 
    documento.clear(); //limpiar documento
    palabras.clear(); //limpiar mapa
  }
  
  return 0;
  
}

void limpiarDocumento( string documento_sucio, vector<string> &documento ) {
  string palabra = "";
  
  for ( unsigned int i = 0; i < documento_sucio.size(); ++i )
    if ( documento_sucio[i] > 96 && documento_sucio[i] < 123 )
      palabra += documento_sucio[i];
    else
      if ( palabra != "" ) {
        documento.push_back( palabra );
        palabra = "";
      }
}
