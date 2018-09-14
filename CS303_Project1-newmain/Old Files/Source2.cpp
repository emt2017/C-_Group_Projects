//erich
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>



using namespace std;

int main() {
//Variables
	string poly3 = "5+x-8888885x^-6-3000000+9888888-8888+x-10000000x^-304325345+909098+x^0+x+20920002+1+1+1+1+1";
	//string poly3 = "-1-1-1-1+1-1";
	//cin >> poly3;  
	string poly2 = "~";
	unsigned int it = 0;
	string exp;
	string coe;
	cout << poly3 << endl;
	int polylength = poly3.length();
//Remove spaces from poly string
	//poly3.erase(remove_if(poly3.begin(), poly3.end(), isspace), poly3.end());
//Add '~' to beginning of poly string
	string poly = poly3.insert(0, poly2);
	cout << "poly3 = " << poly3 << endl;
//Start of finding coe and exp
	for (it; it < poly.length()-1; it++) {
		int	find = poly.find_first_of('x', it + 2);
		int find2 = poly.find_first_of('+', it + 2);
		int find3 = poly.find_first_of('-', it + 2);

		char a = poly[it+2];// after current place
		char c = poly[it+1];// current place
		char b = poly[it];// before current place
//special case no coefficient = 1 or -1 :::::::::::::::::: perfect
		if ((c == 'x' && b == '+') ||(c == 'x' && b == '~')) {
			coe = '1';
			cout << "coe = " << coe << endl;
		}
		if (c == 'x' && b == '-') {
			coe = "-1";
			cout << "coe = " << coe << endl;
		}
//Find exponent ::::::::::::::::::::::::::::: perfect
		if (b == '^') {
	
				//int find2 = poly.find_first_of('+', it+2);
				//int find3 = poly.find_first_of('-', it+2);
				if((find3 < find2 && find3 != -1) || find2 == -1){ // find exp between ^ and -
					exp = poly.substr(it + 1, find3 - it - 1);
					cout << "exp = " << exp << endl;
				}
				else if(find3 == -1 || (find2 < find3 && find2 != -1)){  // find exp between ^ and +
					exp = poly.substr(it + 1, find2 - it - 1);
					cout << "exp = " << exp << endl;
				}

		}
		if (c == 'x' && a != '^') { //special case no ^
			exp = '1';
			cout << "exp = " << exp << endl;
		}
//Find coefficient with at the start of the string
if (b == '~' && c != '-' && c != 'x') {
	//	int	find = poly.find_first_of('x', it +2);
		//int erichfind2 = poly.find_first_of('+', it + 2);
		//int find3 = poly.find_first_of('-', it + 2);
		//cout << "find = " << finerichd << endl;
		//cout << "find2 = " << find2 << endl;
		//cout << "fierichnd3 = " << find3 << endl;
		//cout << "~" << endl;
		// if place of x is less than the place of next + and next -
			if ((find < find2 && find < find3 && find != -1) || (find2 == -1 && find3 == -1 && find != -1) || ((find < find2 && find3 == -1 || find < find3 && find2 == -1) && find != -1)) {
				coe = poly.substr(it + 1, find - it - 1);
				cout << "coe = " << coe << endl;
			} // if place of + is less than the place of next x and next -
			else if ((find2 < find && find2 < find3 && find2 != -1) || (find == -1 && find3 == -1 && find2 != -1) || ((find2 < find && find3 == -1 || find2 < find3 && find == -1) && find2 != -1)) {
				coe = poly.substr(it + 1, find2 - it - 1);
				exp = '0';
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}// if place of - less than place of next x and next +
			else if ((find3 < find2 && find3 < find && find3 != -1) || ((find2 == -1 && find == -1 && find3 != -1) || ((find3 < find && find2 == -1 || find3 < find2 && find == -1) && find3 != -1))) {
				coe = poly.substr(it + 1, find3 - it - 1);
				exp = '0';
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}// if no place for x, +, or - are found::::::::::::one variable in string exception
			else if (find == -1 && find2 == -1 && find3 == -1) {
				coe = poly.substr(it + 1, find - it - 1);
				exp = "0";
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}
		}
		// find coefficients in the middle of string
		if ( (c == '-' && b != '^' && a != 'x') || (c == '+' && a != 'x')) {
		//int	finderich = poly.find_first_of('x', it+2);
		//int finderich2 = poly.find_first_of('+', it+2);
		//int find3 = poly.find_first_of('-', it+2);

		//cout << "find = " << find << endl;
		//cout << "find2 = " << find2 << endl;
		//cout << "find3 = " << find3 << endl;
		//cout << ":P" << endl;

		if (c == '-') {//if current character is -
		 // if place of x is less than the place of next + and next -
			if ((find < find2 && find < find3 && find != -1) || (find2 == -1 && find3 == -1 && find != -1) || ((find < find2 && find3 == -1 || find < find3 && find2 == -1) && find != -1)) {
				coe = poly.substr(it+1, find-it-1);
				cout << "coe = " << coe << endl;
			}// if place of + is less than the place of next x and next -
			else if ((find2 < find && find2 < find3 && find2 != -1) || (find == -1 && find3 == -1 && find2 != -1) ||((find2 < find && find3 == -1 || find2 < find3 && find == -1) && find2 != -1)) {
				coe = poly.substr(it+1, find2-it-1 );
				exp = '0';
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}
			else if ((find3 < find2 && find3 < find && find3 != -1) || (find2 == -1 && find == -1 && find3 != -1) || ((find3 < find && find2 == -1 || find3 < find2 && find == -1) && find3 != -1)) {
				coe = poly.substr(it+1, find3-it-1);
				exp = '0';
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}// if no place for x, +, or - are found::::::::::::end of string exception
			else if (find == -1 && find2 == -1 && find3 == -1) {
				coe = poly.substr(it + 1, find - it - 1);
				exp = "0";
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}
		}
		else if (c == '+') { // if current character is +
			// if place of x is less than the place of next + and next -
			if ((find < find2 && find < find3 && find != -1) || (find2 == -1 && find3 == -1 && find != -1) || ((find < find2 && find3 == -1 || find < find3 && find2 == -1) && find != -1)) {
				coe = poly.substr(it+2, find -it -2);
				cout << "coe = " << coe << endl;
			}// if place of + is less than the place of next x and next -
			else if ((find2 < find && find2 < find3 && find2 != -1) || (find == -1 && find3 == -1 && find2 != -1) || ((find2 < find && find3 == -1 || find2 < find3 && find == -1) && find2 != -1)) {
				coe = poly.substr(it+2, find2 - it -2);
				exp = '0';
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}// if place of - less than place of next x and next +
			else if ((find3 < find2 && find3 < find && find3 != -1) || (find2 == -1 && find == -1 && find3 != -1) || ((find3 < find && find2 == -1 || find3 < find2 && find == -1) && find3 != -1)) {
				coe = poly.substr(it+2, find3-it-2);
				exp = '0';
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}// if no place for x, +, or - are found::::::::::::end of string exception
			else if (find == -1 && find2 == -1 && find3 == -1 ) {
				coe = poly.substr(it + 2, find - it - 2);
				exp = "0";
				cout << "coe = " << coe << endl;
				cout << "exp = " << exp << endl;
			}
			
		}

			
		}

	}




	system("PAUSE");
	cin.get();
	return 0;
}//erich