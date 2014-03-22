#ifndef PROTOCOL_VIOLATION_EXCEPTION_H
#define PROTOCOL_VIOLATION_EXCEPTION_H

#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class ProtocolViolationException : public exception{
public:
	ProtocolViolationException(string a, string b) : s1(a+b){};
	ProtocolViolationException(string a, int b1, int b2) : s1(a+ to_string(b1)+to_string(b2)){};
	virtual const char* what() const throw(){
		return s1.c_str();
	};
private:
	string s1;
};

#endif