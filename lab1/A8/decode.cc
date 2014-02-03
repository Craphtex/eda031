#include <iostream>
#include <fstream>
#include "coding.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc > 1) {
		string file = argv[1];
		ifstream input(file);
		ofstream output(file + ".dec");
		if(input) {
			unsigned char c;
			while(input >> c) {
				output << Coding::decode(c);
			}
			cout << "Successfully decoded.";
		} else {
			cout << "File not found.";
		}
	} else {
		cout << "Too few arguments.";
	}
}
