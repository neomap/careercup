#include <ctime>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

#define MAXLEN     16
#define MAXWORDS 1000

int main(int argc, char **argv)
{
  char char_map[30];
  vector<string> voc;
  int N = atoi(argv[1]);
  srand(time(NULL));
  cout << N << endl;
  for (int i=0; i<N; ++i) {
    int len = (random()%(MAXLEN-1)) + 1;
    char word[len+1];
    for (int j=0; j<len; ++j) 
      word[j] = 'a' + char(random()%('z'-'a'+1));
    word[len] = '\0';
    voc.push_back(string(word));
    cout << word << endl;
  }
  int numwords = random() % 10 + 5;
  for (int i=0; i<'z'-'a'+1; ++i)
    char_map[i] = 'a' + i;
  
  for (int i=0; i<'z'-'a'+1; ++i) {
    int k = random()%('z'-'a'+1);
    char aux = char_map[i];
    char_map[i] = char_map[k];
    char_map[k] = aux;
  }
  for (int i=0; i<numwords; ++i) {
    int k = random() % N;
    cerr << voc[k] << " ";
    for (int j=0; j<voc[k].size(); ++j)
      cout << char_map[voc[k][j]-'a'];
    cout << " ";
  }
  cout << endl;
  cerr << endl;
}
