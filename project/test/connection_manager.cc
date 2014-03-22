#include "connection_manager.h"
#include "connectionclosedexception.h"
#include "connection.h"
#include "protocol.h"

#include <string>
#include <memory>

using namespace std;

connection_manager::connection_manager(const shared_ptr<Connection>& ptr) : conn(ptr) {}

void connection_manager::send_byte(int code){
	try{
		conn->write(static_cast<char> (code));
	} catch(exception e){
		throw ConnectionClosedException();
	}
}

void connection_manager::send_int(int value) {
	send_byte((value >> 24) & 0xFF);
	send_byte((value >> 16) & 0xFF);
	send_byte((value >> 8) & 0xFF);
	send_byte(value & 0xFF);
}

void connection_manager::send_code(int code){
	send_byte(code);
}

void connection_manager::send_int_parameter(int param){
	send_code(Protocol::PAR_NUM);
	send_int(param);
}

void connection_manager::send_string_parameter(string param){
	send_code(Protocol::PAR_STRING);
	send_int(param.length());
	for(auto c: param)
		send_byte(c);
}

int connection_manager::recv_byte(){
	int code = conn->read();
	if(code == 12345)
		throw ConnectionClosedException();
	return code;
}

int connection_manager::recv_code(){
	int code = recv_byte();
	return code;
}

int connection_manager::recv_int(){
	int b1 = recv_byte();
	int b2 = recv_byte();
	int b3 = recv_byte();
	int b4 = recv_byte();
	return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}

int connection_manager::recv_int_parameter(){
	int code = recv_code();
	if(code != Protocol::PAR_NUM)
		throw ProtocolViolationException("In RecvInte: ",Protocol::PAR_NUM, code);
	return recv_int();
}

string connection_manager::recv_string_parameter(){
	int code = recv_code();
	if(code != Protocol::PAR_STRING)
		throw ProtocolViolationException("In RecvString: ",Protocol::PAR_STRING, code);
	int n = recv_int();
	if(n<0)
		throw ProtocolViolationException("In RecvString: ", "n < 0");
	string s;
	for(int i = 0; i < n; i++)
		s.push_back(static_cast<char> (recv_code()));
	return s;
}