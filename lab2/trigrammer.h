#ifndef TRIGRAMMER_H
#define TRIGRAMMER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Trigrammer {
public:
	Trigrammer();
	Trigrammer(const string& in);
	vector<string> get_trigrams(const string& word) const;
private:
};

#endif