#include <iostream>
#include "coding.h"

using namespace std;

int main() {
	unsigned char c = 0;
	for (int i = 0; i < 256; ++i){
		unsigned char encoded = Coding::encode(c);
		unsigned char decoded = Coding::decode(encoded);
		cout << "Different: " << (c != encoded) << endl;
		cout << "Decoded: " << (c == decoded) << endl;
		++c;
	}
}
