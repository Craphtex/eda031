/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "connection_manager.h"
#include "protocol.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <memory>

using namespace std;
void print_menu(){
	cout << "1. List newsgroups" << endl;
	cout << "2. List articles" << endl;
	cout << "3. Fetch article" << endl;
	cout << "4. Create newsgroups" << endl;
	cout << "5. Remove newsgroups" << endl;
	cout << "6. Create article" << endl;
	cout << "7. Remove article" << endl;
}
int fetch_number(){
		cout << ">>";
		int i;
		cin >> i;
		if(cin.fail()){
			cin.clear();
			cin.ignore(10000, '\n'); //Ignore up to 10 000 chars if input is illegal.
			return 0;
		}
		return i;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	print_menu();
	int nbr;
	shared_ptr<Connection> ptr(&conn);
	connection_manager cm(ptr);
	while (true) {
		cout << fetch_number() << endl;
	}
}

