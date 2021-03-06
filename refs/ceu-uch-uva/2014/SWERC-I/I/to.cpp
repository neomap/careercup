#include <iostream>
#include <map>
#include <string>
#include <queue>
#define DAYS 7
#define MAXWORDS 20000

using namespace std;

map<string,int>words;
int matriz[DAYS][MAXWORDS];
int cuenta[MAXWORDS];
int actday=0;
string optimus[MAXWORDS];

struct StringIntPair {
    
    int id_word;
    
    StringIntPair(int id) {
     
        id = id_word; }
    
    string getWord() const {
        return optimus[id_word];
    }
    
    int getCuenta() const {
        return cuenta[id_word];
    }
    
    bool operator < (const StringIntPair &other) const {
        
        if (cuenta[this -> id_word] > cuenta[other.id_word]) return true;
        else if (cuenta[this -> id_word] < cuenta[other.id_word]) return false;
        else return (optimus[this -> id_word] < optimus[other.id_word]);
    }
};

typedef priority_queue<StringIntPair> heap;

int transformer(const string &w){
    
    map<string,int>::iterator it;

      if(w.size() >= 4){

       it = words.find(w);

       if (it == words.end()){

        words[w]=static_cast<int>(words.size());
           optimus[words.size()-1] = w; // diccionario inverso :D
           
        return static_cast<int>(words.size())-1;

       }
        else{
            return it->second;

        }
      }

      else return -1;

}

int Process_Day(){

    string w;
    int id;
    int matio = actday % DAYS;
    
        if (actday >= DAYS)
        {
            for (int i=0; i < MAXWORDS; ++i)
            {
                cuenta[i] -= matriz[matio][i];
                
                matriz[matio][i] = 0;
            }
        }
    
        while(cin>>w)
        {
            if (w == "</text>"){
                
                break;
            }
            
            id = transformer(w);

            cuenta[id]++;
            matriz[matio][id]++;
        }
    actday++;
    
    return actday;
}

void inicializar()
{
    for (int i=0; i < MAXWORDS; ++i)
    {
        cuenta[i]=0;
    }
    
    for (int i=0; i < DAYS; ++i)
    {
        for(int j=0; j < MAXWORDS; ++j)
        {
            matriz[i][j]=0;
        }
    }
}

void showtopk(int k)
{
    heap aux;
    
    for (int i = 0; i < MAXWORDS; ++i)
    {
        if (cuenta[i] > 0) aux.push(StringIntPair(i));
    }
    
    for (int j = 0; j < k; ++j) {
        
        StringIntPair value = aux.top();
        cout << value.getWord() << " "<< value.getCuenta() << endl;
        aux.pop();
    }
    
}

int main()
{
    string symbol, garbage;
    int K;
    inicializar();
    
    while(cin>>symbol){


        if (symbol == "<text>"){
            Process_Day();

        }

        else if  (symbol == "<top") {
            cin>>K;
            cin>>garbage;
            showtopk(K);
                
            }
    }
    
    return 0;
}
