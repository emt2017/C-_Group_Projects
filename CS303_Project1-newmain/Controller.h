#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Term.h"
#include "Ordered_List.h"


using namespace std;

class Controller {
public:
	friend class UserInterface;
	Controller() {}
	// Take user input string and return a polynomial
	Ordered_List<Term> Controller::createPoly(string polystring) {
		Ordered_List<Term> returnPoly;
		//Variables
		unsigned int it = 0;
		string exp;
		string coe;
		int expint;
		int coeint;
		int polylength = polystring.length();
		//Remove spaces from poly string
		//poly3.erase(remove_if(poly3.begin(), poly3.end(), isspace), poly3.end());
		//Add '~' to beginning of poly string
		string addTildeEnd = polystring.insert(0, "~");
		string poly = addTildeEnd.insert(polystring.length(), "+");
		//Start of finding coe and exp
		for (it; it < poly.length() - 1; it++) {
			int	find = poly.find_first_of('x', it + 2);
			int find2 = poly.find_first_of('+', it + 2);
			int find3 = poly.find_first_of('-', it + 2);
			char a = poly[it + 2];// after current place
			char c = poly[it + 1];// current place
			char b = poly[it];// before current place

			//special case no coefficient = 1 or -1 :::::::::::::::::: perfect
			if ((c == 'x' && b == '+') || (c == 'x' && b == '~')) {
				coe = '1';
				coeint = atoi(coe.c_str());
			}
			if (c == 'x' && b == '-') {
				coe = "-1";
				coeint = atoi(coe.c_str());
			}

			//Find coefficient with at the start of the string
			if (b == '~' && c != '-' && c != 'x') {

				// if place of x is less than the place of next + and next -
				if ((find < find2 && find < find3 && find != -1) || (find2 == -1 && find3 == -1 && find != -1) || ((find < find2 && find3 == -1 || find < find3 && find2 == -1) && find != -1)) {
					coe = poly.substr(it + 1, find - it - 1);
					coeint = atoi(coe.c_str());
					if (find != -1) {
						it = find - 2;
					}
				} // if place of + is less than the place of next x and next -
				else if ((find2 < find && find2 < find3 && find2 != -1) || (find == -1 && find3 == -1 && find2 != -1) || ((find2 < find && find3 == -1 || find2 < find3 && find == -1) && find2 != -1)) {
					coe = poly.substr(it + 1, find2 - it - 1);
					exp = '0';
					coeint = atoi(coe.c_str());
					expint = atoi(exp.c_str());
					termInsert(returnPoly, coeint, expint);
					if (find2 != -1) {
						it = find2 - 2;
					}
				}// if place of - less than place of next x and next +
				else if ((find3 < find2 && find3 < find && find3 != -1) || ((find2 == -1 && find == -1 && find3 != -1) || ((find3 < find && find2 == -1 || find3 < find2 && find == -1) && find3 != -1))) {
					coe = poly.substr(it + 1, find3 - it - 1);
					exp = '0';
					coeint = atoi(coe.c_str());
					expint = atoi(exp.c_str());
					termInsert(returnPoly, coeint, expint);
					if (find3 != -1) {
						it = find3 - 2;
					}
				}// if no place for x, +, or - are found::::::::::::one variable in string exception
				else if (find == -1 && find2 == -1 && find3 == -1) {
					coe = poly.substr(it + 1, find - it - 1);
					exp = "0";
					coeint = atoi(coe.c_str());
					expint = atoi(exp.c_str());
					termInsert(returnPoly, coeint, expint);
				}
			}
			// find coefficients in the middle of string
			if ((c == '-' && b != '^' && a != 'x') || (c == '+' && a != 'x')) {

				if (c == '-') {//if current character is -
							   // if place of x is less than the place of next + and next -
					if ((find < find2 && find < find3 && find != -1) || (find2 == -1 && find3 == -1 && find != -1) || ((find < find2 && find3 == -1 || find < find3 && find2 == -1) && find != -1)) {
						coe = poly.substr(it + 1, find - it - 1);
						coeint = atoi(coe.c_str());
						if (find != -1) {
							it = find - 2;
						}
					}// if place of + is less than the place of next x and next -
					else if ((find2 < find && find2 < find3 && find2 != -1) || (find == -1 && find3 == -1 && find2 != -1) || ((find2 < find && find3 == -1 || find2 < find3 && find == -1) && find2 != -1)) {
						coe = poly.substr(it + 1, find2 - it - 1);
						exp = '0';
						coeint = atoi(coe.c_str());
						expint = atoi(exp.c_str());
						termInsert(returnPoly, coeint, expint);
						if (find2 != -1) {
							it = find2 - 2;
						}
					}
					else if ((find3 < find2 && find3 < find && find3 != -1) || (find2 == -1 && find == -1 && find3 != -1) || ((find3 < find && find2 == -1 || find3 < find2 && find == -1) && find3 != -1)) {
						coe = poly.substr(it + 1, find3 - it - 1);
						exp = '0';
						coeint = atoi(coe.c_str());
						expint = atoi(exp.c_str());
						termInsert(returnPoly, coeint, expint);
						if (find3 != -1) {
							it = find3 - 2;
						}
					}// if no place for x, +, or - are found::::::::::::end of string exception
					else if (find == -1 && find2 == -1 && find3 == -1) {
						coe = poly.substr(it + 1, find - it - 1);
						exp = "0";
						coeint = atoi(coe.c_str());
						expint = atoi(exp.c_str());
						termInsert(returnPoly, coeint, expint);
					}
				}
				else if (c == '+') { // if current character is +
									 // if place of x is less than the place of next + and next -
					if ((find < find2 && find < find3 && find != -1) || (find2 == -1 && find3 == -1 && find != -1) || ((find < find2 && find3 == -1 || find < find3 && find2 == -1) && find != -1)) {
						coe = poly.substr(it + 2, find - it - 2);
						coeint = atoi(coe.c_str());
						if (find != -1) {
							it = find - 2;
						}
					}// if place of + is less than the place of next x and next -
					else if ((find2 < find && find2 < find3 && find2 != -1) || (find == -1 && find3 == -1 && find2 != -1) || ((find2 < find && find3 == -1 || find2 < find3 && find == -1) && find2 != -1)) {
						coe = poly.substr(it + 2, find2 - it - 2);
						exp = '0';
						coeint = atoi(coe.c_str());
						expint = atoi(exp.c_str());
						termInsert(returnPoly, coeint, expint);
						if (find2 != -1) {
							it = find2 - 2;
						}
					}// if place of - less than place of next x and next +
					else if ((find3 < find2 && find3 < find && find3 != -1) || (find2 == -1 && find == -1 && find3 != -1) || ((find3 < find && find2 == -1 || find3 < find2 && find == -1) && find3 != -1)) {
						coe = poly.substr(it + 2, find3 - it - 2);
						exp = '0';
						coeint = atoi(coe.c_str());
						expint = atoi(exp.c_str());
						termInsert(returnPoly, coeint, expint);
						if (find3 != -1) {
							it = find3 - 2;
						}
					}// if no place for x, +, or - are found::::::::::::end of string exception
					else if (find == -1 && find2 == -1 && find3 == -1) {
						coe = poly.substr(it + 2, find - it - 2);
						exp = "0";
						coeint = atoi(coe.c_str());
						expint = atoi(exp.c_str());
						termInsert(returnPoly, coeint, expint);
					}


				}
			}
			//Find exponent ::::::::::::::::::::::::::::: perfect
			if (b == '^') {

				if ((find3 < find2 && find3 != -1) || find2 == -1) { // find exp between ^ and -
					exp = poly.substr(it + 1, find3 - it - 1);
					expint = atoi(exp.c_str());
					termInsert(returnPoly, coeint, expint);
					if (find3 != -1) {
						it = find3 - 2;
					}

				}
				else if (find3 == -1 || (find2 < find3 && find2 != -1)) {  // find exp between ^ and +
					exp = poly.substr(it + 1, find2 - it - 1);
					expint = atoi(exp.c_str());
					termInsert(returnPoly, coeint, expint);
					if (find2 != -1) {
						it = find2 - 2;
					}

				}

			}
			if (c == 'x' && a != '^') { //special case no ^
				exp = '1';
				expint = atoi(exp.c_str());
				termInsert(returnPoly, coeint, expint);
			}

		}
		return returnPoly;
	}

	// Add the two polys stored in control variables
	// returns false if operation fails
	bool Controller::addPoly() {
		sum.emptyList(); // make sure poly is empty before adding anything
		Ordered_List<Term>::iterator itr1 = poly1.begin();
		Ordered_List<Term>::iterator itr2 = poly2.begin();

		if (poly1.size() == 0 || poly2.size() == 0) {
			return false;
		}

		while ((itr1 != poly1.end()) && (itr2 != poly2.end())) {
			// If matching exponents add terms and insert into sum
			if (itr1->getExponent() == itr2->getExponent()) {
				int add = itr1->getCoefficient() + itr2->getCoefficient();
				termInsert(sum, add, itr1->getExponent());
				itr1++;
				itr2++;
			}
			// if not equal insert the bigger term
			else if (itr1->getExponent() < itr2->getExponent()) {
				termInsert(sum, itr2->getCoefficient(), itr2->getExponent());
				itr2++;

			}
			else {
				termInsert(sum, itr1->getCoefficient(), itr1->getExponent());
				itr1++;
			}

		}
		// if end of one of the polys reach input the rest of the terms from other poly
		while (itr1 != poly1.end()) {
			termInsert(sum, itr1->getCoefficient(), itr1->getExponent());
			itr1++;
		}
		while (itr2 != poly2.end()) {
			termInsert(sum, itr2->getCoefficient(), itr2->getExponent());
			itr2++;
		}

		return true;
	}

	// output poly to standard output
	void printPoly(Ordered_List<Term>& f) {
		Ordered_List<Term>::iterator iter = f.begin();
		cout << endl;
		if (f.size() == 0) { // if no terms output 0
			cout << "0";
		}
		while (iter != f.end()) {
			if ((!iter.isHead()) && (iter->getCoefficient() > 0))
				cout << "+";
			if (iter->getCoefficient() == 0) {
				iter = f.erase(iter); // erase any zero coeff terms
			}
			if (iter->getExponent() == 0) { // constants
				cout << iter->getCoefficient();
				++iter;
			}
			else {
				if (iter->getCoefficient() != 1 && iter->getCoefficient() != -1) {
					cout << iter->getCoefficient();
				}
				if (iter->getCoefficient() == -1) {
					cout << "-";
				}
				cout << "x";
				if ((iter->getExponent() != 1)) {
					cout << "^" << iter->getExponent();
				}
				++iter;
			}
		}
		cout << endl << endl;
	}

	// function for UI to call to create first poly
	// and store it in poly1 variable
	void setpoly1(string source) {
		poly1.emptyList(); // empty any previous poly 
		Ordered_List<Term> temp = createPoly(source);
		poly1 = temp;
	}
	void setpoly2(string source) {
		poly2.emptyList();
		Ordered_List<Term> temp = createPoly(source);
		poly2 = temp;
	}

	// wrapper function so no terms with a 0 coeff are inserted into a list
	void termInsert(Ordered_List<Term>& poly, int coeff, int exp) {
		if (coeff == 0) {
			return;
		}
		else {
			poly.insert(Term(coeff, exp));
		}
	}

private:
	Ordered_List<Term> poly1;
	Ordered_List<Term> poly2;
	Ordered_List<Term> sum;
};

#endif