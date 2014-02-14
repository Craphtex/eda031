#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "word.h"
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary() {
	load_file("words.txt");
}

bool Dictionary::contains(const string& word) const {
	for (string word_in_list : words) {
		if (word_in_list == word) {
			return true;
		}
	}
	return false;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}

void Dictionary::load_file(const string& in) {
	ifstream input(in);
	if(input) {
		string word;
		while(input >> word) {
			words.insert(word);
			int number_of_trigrams = 0;
			input >> number_of_trigrams;
			for (int i = 0; i < number_of_trigrams; ++i) {
				string trigram;
				input >> trigram;
			}
		}
	} else {
		cout << "No wordlist to load.";
	}
}
