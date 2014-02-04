#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary() {
}

/*
bool Dictionary::contains(const string& word) const {
	string a = word;
	return true;
}
*/

/*
vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}
*/

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

void Dictionary::load_file(const string& in, const string& out) {
	ifstream input(in);
	ofstream output(out);
	if(input) {
		string word;
		while(input >> word) {
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			dictionary.push_back(word);
		}
		for(int i = 0; i < dictionary.size(); ++i){
			vector<string> trigrams = get_trigrams(dictionary[i]);
			output << dictionary[i] << " " << trigrams.size() << " ";
			for(int j = 0; j < trigrams.size(); ++j) {
				output << trigrams[j] << " ";
			}
			output << endl;
		}
	} else {
		cout << "File not found.";
	}
}

int main() {
	Dictionary dictionary = Dictionary();
	dictionary.load_file("words", "words.txt");
}

/*
int main(int argc, char *argv[]) {
	if (argc > 1) {
		ifstream input(argv[1]);
		ofstream output("words.txt");
		if(input) {
			string word;
			while(input >> word) {
				cout << word << " ";
				int cnt;
				input >> cnt;
				cout << cnt << " ";
				while(--cnt >= 0){
					string str;
					input >> str;
					cout << str << "(" << cnt << ") ";
				}
				cout << endl;
			}
		} else {
			cout << "File not found.";
		}
	} else {
		cout << "Too few arguments.";
	}
}
*/