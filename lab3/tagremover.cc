#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "tagremover.h"

using namespace std;

TagRemover::TagRemover(istream& in): in(in) {
	specialCharacter["lt"] = '<';
	specialCharacter["gt"] = '>';
	specialCharacter["nbsp"] = ' ';
	specialCharacter["amp"] = '&';
	specialCharacter["quot"] = '"';
	specialCharacter["frasl"] = '/';
}

void TagRemover::print(ostream& out) const {
	char character;
	bool state_tag = false;
	bool state_special_character = false;
	string special_character_name;
	while(in.get(character)) {
		switch(character) {
			case '<':
				if(!state_special_character){
					state_tag = true;
				}
				break;
			case '>':
				state_tag = false;
				break;
			case '&':
				if(!state_tag){
					special_character_name = "";
					state_special_character = true;
				}
				break;
			case ';':
				if(specialCharacter.count(special_character_name)){
					out << specialCharacter.at(special_character_name);
				}
				state_special_character = false;
				break;
			default:
				if(state_special_character) {
					special_character_name += character;
				} else if(!state_tag){
					out << character;
				}
				break;
		}
	}
}

int main() {
	TagRemover tr(std::cin);
	tr.print(std::cout);
}
