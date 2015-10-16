#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

void processDigit(char digit, int size, int numdigit);

char display[23][103];

int main(void) {
	int s;
	string n;
	
	while(cin >> s >> n) {
		if(s == 0) break; //end of input file

		//reset the display
		int width  = n.size()*(s+2) + n.size() - 1;
		int height = 2*s + 3;
		for(int row=0; row<height; ++row)
			for(int col=0; col<width; ++col) display[row][col] = ' ';

		//process each digit
		for(int i=0; i<n.size(); ++i) processDigit(n[i], s, i);

		//show the display
		for(int row=0; row<height; ++row) {
			for(int col=0; col<width; ++col) cout << display[row][col];
			cout << endl;
		}

		cout << endl; //blank line at the end of each test case
	}

	return 0;
}

void processDigit(char digit, int size, int numdigit) {
	int offset = numdigit*(size + 2) + numdigit;
	int row = 0, col = offset;

	switch(digit) {
		case '0':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			++row;
			
			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
		case '1':
			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			++row;

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			++row;

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			break;
		case '2':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = ' ';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
		case '3':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
		case '4':
			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			++row;

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			break;
		case '5':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = ' ';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
		case '6':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = ' ';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
		case '7':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			++row;

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			for(int i=0; i<size+2; ++i) display[row][col++] = ' ';
			break;
		case '8':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
		case '9':
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = '|';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row++][col] = ' ';

			for(int i=0; i<size; ++i) {
				col = offset;
				display[row][col++] = ' ';
				for(int j=0; j<size; ++j) display[row][col++] = ' ';
				display[row++][col] = '|';
			}

			col = offset;
			display[row][col++] = ' ';
			for(int i=0; i<size; ++i) display[row][col++] = '-';
			display[row][col] = ' ';
			break;
	}
}
