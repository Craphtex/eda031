#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	//std::vector<std::string> get_suggestions(const std::string& word) const;
	void load_file(const std::string& input, const std::string& output);
	std::vector<std::string> get_trigrams(const std::string& word) const ;
private:
	std::vector<std::string> dictionary;
};

#endif
