#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct word {
  string seq;
  string letters;
};

vector<word> alphabet[17];
vector<word>::iterator it;

struct enigma {
  bool solved;
  string seq;
  string letters;
  string solution;
};

vector<enigma> encrypted_words;
vector<enigma>::iterator it2;

int solved_enigmas;

string makeSequence( string ); //devuelve la secuencia asociada a una cadena

string makeAsterisks( int ); //devuelve una cadena de asteriscos de tamanyo 'n'

void replaceLetters(string crypt, string clear); //reemplaza las letras desencriptadas

void showResult(); //muestra el resultado

void resetSolutions(); //vuelve a poner todas las soluciones a '*'

int main(void)
{
  // CARGAR EL ALFABETO ///////////////////////////////////////////////////////////////
  int n;
  cin >> n; //numero de palabras del alfabeto

  word aux;

  for ( int i = 0; i < n; ++i )
    {
      cin >> aux.letters; //letras de la palabra
      aux.seq = makeSequence( aux.letters ); //secuencia de la palabra
		
      alphabet[ aux.letters.length() ].push_back( aux ); //insertar palabra en el alfabeto
    }
  // FIN CARGAR EL ALFABETO ///////////////////////////////////////////////////////////

  string buffer;
  string letters = "";
  enigma aux2;
	
  while ( getline( cin, buffer ) )
    {
      // CARGAR LINEA ENCRIPTADA ////////////////////////////////////////////////////////
      if ( (buffer != "") && (buffer != "\n") )
	{
	  istringstream iss(buffer);
	  while ( getline( iss, letters, ' ' ) )
	    {
	      aux2.letters = letters;
	      aux2.seq = makeSequence( letters );
	      aux2.solved = false;
	      aux2.solution = makeAsterisks( letters.length() );

	      encrypted_words.push_back( aux2 );

	      letters = "";
	    }
	}
      // FIN CARGAR LINEA ENCRIPTADA ////////////////////////////////////////////////////

      int num_enigmas = encrypted_words.size();
      solved_enigmas = 0;
		
      // RESOLVER EL PROBLEMA ///////////////////////////////////////////////////////////
      for ( unsigned int i = 0; i < encrypted_words.size(); ++i )
	{
	  if ( !encrypted_words[i].solved )
	    {
	      int pos = encrypted_words[i].letters.size();

	      for ( it = alphabet[pos].begin(); it != alphabet[pos].end(); ++it )
		{
		  bool match = true;
					
		  for ( int j = 0; j < pos; ++j )
		    {
		      if ( encrypted_words[i].solution[j] == '*' )
			{
			  if ( encrypted_words[i].seq[j] != it->seq[j] )
			    {
			      match = false;
			      break;
			    }
			}
		      else
			{
			  if ( encrypted_words[i].solution[j] != it->letters[j] )
			    {
			      match = false;
			      break;
			    }
			}
		    }

		  if ( match )
		    {
		      encrypted_words[i].solved = true; //palabra resuelta
		      ++solved_enigmas;
		      encrypted_words[i].solution = it->letters; //anotar solucion

		      replaceLetters(encrypted_words[i].letters, encrypted_words[i].solution); //reemplazar letras desencriptadas
		    }
		}
	    }
	}
      // FIN RESOLVER EL PROBLEMA /////////////////////////////////////////////////////////

      // SI NO HEMOS RESUELTO TODAS LAS PALABRAS LO DEJAMOS COMO ESTABA
      if ( solved_enigmas != num_enigmas )
	resetSolutions();

      //MOSTRAR RESULTADO
      showResult();
		
      //LIMPIAR VECTOR encrypted_words
      encrypted_words.clear();

      //LIMPIAR letters
      letters = "";
    }
	
  return 0;
}

string makeSequence( string letters )
{
  string seq = "";
  char count = '0';

  map<char,int> transform;
	
  for ( unsigned int i = 0; i < letters.length(); ++i )
    {
      if ( transform.find( letters[i] ) == transform.end() )
	transform[ letters[i] ] = count++;

      seq += transform[ letters[i] ];
    }

  return seq;
}

string makeAsterisks( int n )
{
  string seq = "";

  for ( int i = 0; i < n; ++i )
    seq += '*';

  return seq;
}

void replaceLetters(string crypt, string clear)
{
  for ( it2 = encrypted_words.begin(); it2 != encrypted_words.end(); ++it2 )
    {
      if ( !it2->solved )
	{
	  for ( unsigned int j = 0; j < it2->letters.size(); ++j )
	    {
	      for ( unsigned int k = 0; k < crypt.size(); ++k )
		{
		  if (it2->solution[j] == '*' )
		    if ( it2->letters[j] == crypt[k] )
		      it2->solution[j] = clear[k];
		}
	    }

	  bool solved = true;
			
	  for ( unsigned int j = 0; j < it2->letters.size(); ++j )
	    {
	      if ( it2->solution[j] == '*' )
		{
		  solved = false;
		  break;
		}
	    }

	  if ( solved )
	    {
	      it2->solved = true;
	      ++solved_enigmas;
	    }
	}
    }
}

void showResult()
{
  if ( !encrypted_words.empty() )
    {
      for ( it2 = encrypted_words.begin(); it2 != encrypted_words.end() -1; ++it2 )
	{
	  cout << it2->solution << ' ';
	}
      it2 = encrypted_words.end() -1;
      cout << it2->solution << '\n';
    }
}

void resetSolutions()
{
  if ( !encrypted_words.empty() )
    {
      for ( it2 = encrypted_words.begin(); it2 != encrypted_words.end(); ++it2 )
	{
	  for ( unsigned int i = 0; i < it2->solution.length(); ++i )
	    {
	      it2->solution[i] = '*';
	    }
	}
    }
}
