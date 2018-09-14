#ifndef TRANSLATOR
#define TRANSLATOR


#include <fstream>
#include <vector>
#include "Binary_Tree.h"
#include <map>

using namespace std;

class Translator {
public:
	Translator() {}
	Translator(string input) : fin(input), decode("CENTER") {}
	
	~Translator() {
		fin.close();
	}

	// reads in file translator is initialized with and 
	// constructs a tree to be used with decoding morse code
	void buildTree() {
		string line;
		string letter;
		string code = "";
		string::iterator itr;

		BTNode<string>* current = decode.getRoot();
	
		// load map and vector
		while (fin >> line) {
			current = decode.getRoot();
			itr = line.begin();
			letter = *(itr++); // get letter
			// iterate through morse code
			for (itr; itr != line.end(); itr++) {
				code += *itr;
				if (*itr == '.') { // go left if '.'
					if (current->left == NULL) {
						BTNode<string>* tmp = new BTNode<string>("");
						current->left = tmp;
					}
					current = current->left;
				}
				else if (*itr == '_') { // go right if '_'
					if (current->right == NULL) {
						BTNode<string>* tmp = new BTNode<string>("");
						current->right = tmp;
					}
					current = current->right;
				}
			}
			current->data = letter; // assign node stopped at to current letter
			encode[letter] = code; // put letter, morse pair into map for encoding
			code = "";
		}

		//outputTree(decode.getRoot()); // output for debug, remove later
	}

	// outputs tree via infix
	void outputTree(BTNode<string>* n) {
		if (n == NULL) {
			cout << " NULL " << endl;
			return;
		}
		outputTree(n->left);
		cout << " " << n->data << endl;
		outputTree(n->right);
	}


	string DECODE(Binary_Tree<string>& tree, BTNode<string>* root, const BTNode<string>* start, string& to_decode, string& result, const int& i) {

		char morse = to_decode[i];

		if (morse == '.') { //if morse equals '.' then move the root left
			root = root->left;
		}

		if (morse == '_') { //if morse equals '.' then move the root right
			root = root->right;
		}
		if (morse == ' ' || i == to_decode.size() - 1) {// if morse equals a space or it is at the end of the string, then roots data to string, and reset the root
			result += root->data;
			root = tree.getRoot();
		}

		if (i == to_decode.size() - 1) {//if end of string return message
			return result;
		}

		return DECODE(tree, root, start, to_decode, result, i + 1);

	}

	string DECODE_Wrapper(string& to_decode) {
		BTNode<string>* root = decode.getRoot();
		const BTNode<string>* start = root;
		const int i = 0;
		string result;

		return DECODE(decode, root, start, to_decode, result, i);
	}

	//encodes a string
	string encodeLine(string line){
		string::iterator itr = line.begin();
		string result;
		char currentLetter;
		string currentLetterS;
		//get current letter and add to result
		while(itr != line.end()){
			currentLetter = *itr;
			if (isupper(currentLetter)) { currentLetter = tolower(currentLetter); }//get rid of capitals
			currentLetterS = currentLetter;
			//cout<<currentLetterS<<" "<<encode[currentLetterS]<<endl; // log output
			result+= (encode[currentLetterS]+" ");
			itr++;
		}
		// cout<<result;
		return result;
	}

	Binary_Tree<string>& getTree() {
		return decode;
	}

private:
	ifstream fin; // file to construct tree with
	map<string, string> encode;	
	Binary_Tree<string> decode;

};



#endif
