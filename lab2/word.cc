#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t): word(w), trigrams(t) {}

string Word::get_word() const {
	return word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	unsigned int trigrams_ctr = 0;
	unsigned int t_ctr = 0;
	unsigned int matches_ctr = 0;
	while(trigrams.size() < trigrams_ctr || t.size() < t_ctr) {
		if (trigrams[trigrams_ctr] == t[t_ctr]) {
			++matches_ctr;
			++trigrams_ctr;
			++t_ctr;
		}
		else if(trigrams[trigrams_ctr] < t[t_ctr]) {
			++trigrams_ctr;
		}
		else {
			++t_ctr;
		}
	}
	return matches_ctr;
}
