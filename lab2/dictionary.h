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
	void load_file(const string& input);
private:
	unordered_set<Word> words;
	vector<Word> words[25]; // words[i] = the words with i letters,
	                        // ignore words longer than 25 letters
};

#endif
