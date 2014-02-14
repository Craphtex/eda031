#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "trigrammer.h"

using namespace std;

Trigrammer::Trigrammer(const string& in) {
	ifstream input(in);
	ofstream output("words.txt");
	vector<string> word_list;
	if(input) {
		string word;
		while(input >> word) {
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			word_list.push_back(word);
		}
		for(int i = 0; i < word_list.size(); ++i){
			vector<string> trigrams = get_trigrams(word_list[i]);
			output << word_list[i] << " " << trigrams.size() << " ";
			for(int j = 0; j < trigrams.size(); ++j) {
				output << trigrams[j] << " ";
			}
			output << endl;
		}
	} else {
		cout << "File not found.";
	}
}

vector<string> Trigrammer::get_trigrams(const string& word) const {
	vector<string> trigrams;
	if(word.length() > 2) {
		for (int i = 0; i <= word.length() - 3; ++i){
			trigrams.push_back(word.substr(i,3));
		}
		sort(trigrams.begin(), trigrams.end());
	}
	return trigrams;
}

int main(int argc, char *argv[]) {
	switch (argc) {
	case 2:
		{Trigrammer trigrammer = Trigrammer(argv[1]);}
		break;
	default:
		cout << "Wrong number of arguments.";
		break;
	}
}