#include <iostream>
#include <algorithm>
#include <iterator>

#include <string>
#include <vector>
#include <fstream>

#include "tagremover.h"

using namespace std;

TagRemover::TagRemover(istream& in): in(in) {}

void TagRemover::print(const ostream& out) const {
	bool in_tag = false;
	istream_iterator<string> input(in);
	string s;
	while(input >> s) {
		//out << s;
	}
}

int main() {
	TagRemover tr(std::cin);
	tr.print(std::cout);
}
