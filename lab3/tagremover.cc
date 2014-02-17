#include <iostream>
#include "tagremover.h"

using namespace std;

TagRemover::TagRemover(istream& in) {

}

void TagRemover::print(const ostream& out) const {

}

int main() {
	TagRemover tr(std::cin);
	tr.print(std::cout);
}
