#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class TagRemover {
public:
	TagRemover(istream& in);
	void print(ostream& out) const;
private:
	istream& in;
	unordered_map <string, char> specialCharacter;
};

#endif
