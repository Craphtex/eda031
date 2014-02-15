#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "word.h"

using namespace std;

class Dictionary {
public:
	Dictionary();
	bool contains(const string& word) const;
	vector<string> get_suggestions(const string& word) const;
private:
	static const unsigned int max_word_size = 25;
	vector<Word> words[max_word_size];
	vector<string> get_trigrams(const string& word) const;
	void load_file(const string& input);
	void add_trigram_suggestions(vector<Word>& suggestions, const string& word) const;
	void rank_suggestions(vector<Word>& suggestions, const string& word) const;
	void trim_suggestions(vector<Word>& suggestions) const;
};

#endif
