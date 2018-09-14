#ifndef USERINTERFACE
#define USERINTERFACE

#include "Controller.h"
#include <iostream>
#include <string>
using namespace std;

class UserInterface {
public:
	UserInterface(Controller c) : cntrl(c) {}
	UserInterface() {}
	void outputMenu();
	bool getMenuInput();
	string getPolynomial();
private:
	Controller cntrl;
};

#endif