#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const char digits_shape[10][5][4] = {
  { " - ", "| |", "   ", "| |", " - " },
  { "   ", "  |", "   ", "  |",	"   " },
  { " - ", "  |", " - ", "|  ",	" - " },
  { " - ", "  |", " - ", "  |", " - " },
  { "   ", "| |", " - ", "  |", "   "},
  { " - ", "|  ", " - ", "  |", " - " },
  { " - ", "|  ", " - ", "| |", " - " },
  { " - ", "  |", "   ", "  |",	"   " },
  { " - ", "| |", " - ", "| |", " - " },
  { " - ", "| |", " - ", "  |", " - " },
};

void DrawDigitRow(char num, int i, int s){
  int med=s+1;
  int ult=(s+1)+med;
  int templaterow;
  int templatedigit=num-'0';

  if(i == 0) templaterow=0;
  else if(i < med) templaterow=1;
  else if(i == med) templaterow=2;
  else if(i < ult) templaterow=3;
  else templaterow=4;

  cout << digits_shape[templatedigit][templaterow][0];
  for(int j=0; j < s; j++){
    cout << digits_shape[templatedigit][templaterow][1];
  }
  cout << digits_shape[templatedigit][templaterow][2];

}

int main() {

  int s,i,j, maxrows;
  string number;
  bool first=true;

  while(cin >> s >> number){
    if(s==0){break;}
    first=false;
    const int numdigits = static_cast<int>(number.size());
    maxrows=2*s+3;
    for(i=0; i<maxrows; i++){
      for(j=0; j<numdigits; j++){
	DrawDigitRow(number[j], i, s);
	if (j < numdigits-1) cout << ' ';
      }
      cout << endl;
    }
    cout << endl;
  }
}
