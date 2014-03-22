#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include "connection_manager.h"
#include "connectionclosedexception.h"
#include "protocolviolationexception.h"
#include "connection.h"

#include <string>
#include <memory>
/*
class ProtocolViolationException: public exception{
private:
	string msg;
public:
	ProtocolViolationException(std::string s1, std::string s2){
		msg = s1 + s2;
	}

	ProtocolViolationException(std::string s1, int i1, int i2);{	
		msg = s1 + to_string(i1) + to_string(i2);
	}

	virtual const char* what() const throw(){
  		return msg;
  	}

};
*/
class connection_manager {
public:
	connection_manager(const std::shared_ptr<Connection>&);
	void send_code(int);
	void send_int(int);
	void send_int_parameter(int);
	void send_string_parameter(std::string);
	int recv_code();
	int recv_int();
	int recv_int_parameter();
	std::string recv_string_parameter();
private:
	void send_byte(int);
	int recv_byte();
	std::shared_ptr<Connection> conn;
};
#endif