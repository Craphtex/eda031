#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t): word(w), triples(t) {}

string Word::get_word() const {
	return word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	int triplets_ctr = 0;
	int t_ctr = 0;
	int matches_ctr = 0;
	while(triplets.size() < triplets_ctr || t.size() < t_ctr) {
		if (triplets[triplets_ctr] == t[t_ctr]) {
			++matches_ctr;
			++triplets_ctr;
			++t_ctr;
		}
		else if(triplets[triplets_ctr] < t[t_ctr]) {
			++triplets_ctr;
		}
		else {
			++t_ctr;
		}
	}
	return matches_ctr;
}
