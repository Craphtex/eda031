#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <iostream>

using namespace std;

class TagRemover {
public:
	TagRemover(istream& in);
	void print(const ostream& out) const;
private:
};

#endif
