#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include "Binary_Tree.h"
#include "Translator.h"
using namespace std;



int main() {

	Translator t("morse.txt");
	t.buildTree();

	string encode = t.encodeLine("hello");
	cout << encode << endl;
	string decode = t.DECODE_Wrapper(encode);

	cout << decode << endl;
	cout << encode << endl;


	cin.get();
	return 0;
}
