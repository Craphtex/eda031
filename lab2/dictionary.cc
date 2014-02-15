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
	if (word.size() < max_word_size) {
		for (Word word_in_list : words[word.size()]) {
			if (word_in_list.get_word() == word) {
				return true;
			}
		}
	}
	return false;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	//transform(word.begin(), word.end(), word.begin(), ::tolower);
	vector<Word> suggestions;
	add_trigram_suggestions(suggestions, word);
	//rank_suggestions(suggestions, word);
	//trim_suggestions(suggestions);


	vector<string> suggestions_to_return;
	for(Word word_in_list : suggestions) {
		suggestions_to_return.push_back(word_in_list.get_word());
	}
	return suggestions_to_return;
}

void Dictionary::add_trigram_suggestions(vector<Word>& suggestions, const string& word) {
	if(word.size < max_word_size) {
		// Adding words with same size
		vector<Word>& same_size = words[word.size()];
		suggestions.reserve(suggestions.size() + same_size.size());
		suggestions.insert(suggestions.end(), same_size.begin(), same_size.end());

		// Adding words with one fewer letter
		if(word.size() > 0) {
			vector<Word>& minus_one = words[word.size() - 1];
			suggestions.reserve(suggestions.size() + minus_one.size());
			suggestions.insert(suggestions.end(), minus_one.begin(), minus_one.end());
		}

		// Adding words with one more letter
		if(word.size() < max_word_size - 1) {
			vector<Word>& plus_one = words[word.size() + 1];
			suggestions.reserve(suggestions.size() + plus_one.size());
			suggestions.insert(suggestions.end(), plus_one.begin(), plus_one.end());
		}

		// Removing words that differs to much regarding trigrams
		vector<string> trigrams = get_trigrams(word);
		auto i = begin(suggestions);
		while(i != end(suggestions)) {
			if(suggested.get_matches(trigrams) * 2 < trigrams.size()){
				i = suggestions.erase(i);
			}
			else {
				++i;
			}
		}
	}
}

vector<string> Dictionary::get_trigrams(const string& word) const {
	vector<string> trigrams;
	if(word.length() > 2) {
		for (int i = 0; i <= word.length() - 3; ++i){
			trigrams.push_back(word.substr(i,3));
		}
		sort(trigrams.begin(), trigrams.end());
	}
	return trigrams;
}

void Dictionary::load_file(const string& in) {
	ifstream input(in);
	if(input) {
		string word;
		while(input >> word) {
			int number_of_trigrams = 0;
			input >> number_of_trigrams;
			vector<string> trigrams;
			for (int i = 0; i < number_of_trigrams; ++i) {
				string trigram;
				input >> trigram;
				trigrams.push_back(trigram);
			}
			if (word.size() < max_word_size) {
				words[word.size()].push_back(Word(word, trigrams));
			}
		}
	} else {
		cout << "No wordlist to load.";
	}
}
