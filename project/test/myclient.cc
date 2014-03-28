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

int fetch_number() {
	cout << ">>";
	int i;
	cin >> i;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n'); //Ignore up to 10 000 chars if input is illegal.
		return 0;
	}
	return i;
}

string fetch_string() {
	string value;
	cin >> value;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n'); //Ignore up to 10 000 chars if input is illegal.
		return "";
	}
	return value;
}

void list_newsgroups(connection_manager& cm){
	cout << "Listing newsgroups" << endl;
	cm.send_code(Protocol::COM_LIST_NG);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_LIST_NG) {
		throw ProtocolViolationException("In List Newsgroups: ", Protocol::ANS_LIST_NG, code);
	}
	int nbr = cm.recv_int_parameter();
	while (--nbr > -1) {
		int id = cm.recv_int_parameter();
		string name = cm.recv_string_parameter();
		cout << id << ". " << name << endl;
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In List Newsgroups: ", Protocol::ANS_END, code);
	}
}

void create_newsgroups(connection_manager& cm){
	cout << "Creating new newsgroup" << endl;
	cout << "Enter a name: ";
	string name = fetch_string();
	if (name != "") {
		cout << "No name entered. Creation aborted." << endl;
		return;
	}
	cm.send_code(Protocol::COM_CREATE_NG);
	cm.send_string_parameter(name);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_CREATE_NG) {
		throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ANS_CREATE_NG, code);
	}
	code = cm.recv_code();
	if (code == Protocol::ANS_ACK) {
		cout << "Newsgroup \"" << name << "\" successfully added.";
	}
	else if (code == Protocol::ANS_NAK) {
		code = cm.recv_code();
		if (code == Protocol::ERR_NG_ALREADY_EXISTS) {
			cout << "Newsgroup with name \"" << name << "\" already exists.";
		}
		else {
			throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ERR_NG_ALREADY_EXISTS, code);
		}
	}
	else {
		// Or ANS_NAK
		throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ANS_ACK, code);
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ANS_END, code);
	}
}

void delete_newsgroups(connection_manager& cm){
	cout << "Removing a newsgroup" << endl;
	cout << "Enter id: ";
	int id = fetch_number();
	if (id < 1) {
		cout << "No valid number was entered. Removal aborted." << endl;
		return;
	}
	cm.send_code(Protocol::COM_DELETE_NG);
	cm.send_int_parameter(id);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_DELETE_NG) {
		throw ProtocolViolationException("In Delete Newsgroups: ", Protocol::ANS_DELETE_NG, code);
	}
	code = cm.recv_code();
	if (code == Protocol::ANS_ACK) {
		cout << "Newsgroup with id \"" << id << "\" successfully removed.";
	}
	else if (code == Protocol::ANS_NAK) {
		code = cm.recv_code();
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			cout << "No newsgroup with id \"" << id << "\" exists.";
		}
		else {
			throw ProtocolViolationException("In Delete Newsgroups: ", Protocol::ERR_NG_DOES_NOT_EXIST, code);
		}
	}
	else {
		// Or ANS_NAK
		throw ProtocolViolationException("In Delete Newsgroups: ", Protocol::ANS_ACK, code);
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In Delete Newsgroups: ", Protocol::ANS_END, code);
	}
}

void list_articles(connection_manager& cm){
	cout << "List articles in newsgroup" << endl;
	cout << "Enter newsgroup id: ";
	int id = fetch_number();
	if (id < 1) {
		cout << "No valid number was entered. Listing aborted." << endl;
		return;
	}
	cm.send_code(Protocol::COM_LIST_ART);
	cm.send_int_parameter(id);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_LIST_ART) {
		throw ProtocolViolationException("In List Articles: ", Protocol::ANS_LIST_ART, code);
	}
	code = cm.recv_code();
	if (code == Protocol::ANS_ACK) {
		cout << "Newsgroup with id \"" << id << "\" successfully removed.";
		int nbr = cm.recv_int_parameter();
		while (--nbr > -1) {
			int id = cm.recv_int_parameter();
			string name = cm.recv_string_parameter();
			cout << id << ". " << name << endl;
		}
	}
	else if (code == Protocol::ANS_NAK) {
		code = cm.recv_code();
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			cout << "No newsgroup with id \"" << id << "\" exists.";
		}
		else {
			throw ProtocolViolationException("In List Articles: ", Protocol::ERR_NG_DOES_NOT_EXIST, code);
		}
	}
	else {
		// Or ANS_NAK
		throw ProtocolViolationException("In List Articles: ", Protocol::ANS_ACK, code);
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In List Articles: ", Protocol::ANS_END, code);
	}
}

void create_article(connection_manager& cm){
	cout << "Create article in newsgroup" << endl;
	cout << "Enter newsgroup id: ";
	int id = fetch_number();
	if (id < 1) {
		cout << "No valid number was entered. Creation aborted." << endl;
		return;
	}
	cout << "Enter a title: ";
	string title = fetch_string();
	if (title != "") {
		cout << "No title entered. Creation aborted." << endl;
		return;
	}
	cout << "Enter your name: ";
	string name = fetch_string();
	if (name != "") {
		cout << "No name entered. Creation aborted." << endl;
		return;
	}
	cout << "Enter article text: ";
	string text = fetch_string();
	if (text != "") {
		cout << "No text entered. Creation aborted." << endl;
		return;
	}
	cm.send_code(Protocol::COM_CREATE_ART);
	cm.send_int_parameter(id);
	cm.send_string_parameter(title);
	cm.send_string_parameter(name);
	cm.send_string_parameter(text);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_CREATE_ART) {
		throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ANS_CREATE_ART, code);
	}
	code = cm.recv_code();
	if (code == Protocol::ANS_ACK) {
		cout << "Article successfully uploaded.";
	}
	else if (code == Protocol::ANS_NAK) {
		code = cm.recv_code();
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			cout << "No newsgroup with id \"" << name << "\" exists.";
		}
		else {
			throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ERR_NG_DOES_NOT_EXIST, code);
		}
	}
	else {
		// Or ANS_NAK
		throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ANS_ACK, code);
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In Create Newsgroups: ", Protocol::ANS_END, code);
	}
}

void delete_article(connection_manager& cm){
	cout << "Delete article in newsgroup" << endl;
	cout << "Enter newsgroup id: ";
	int ng_id = fetch_number();
	if (ng_id < 1) {
		cout << "No valid number was entered. Removal aborted." << endl;
		return;
	}
	cout << "Enter article id: ";
	int art_id = fetch_number();
	if (art_id < 1) {
		cout << "No valid number was entered. Removal aborted." << endl;
		return;
	}
	cm.send_code(Protocol::COM_DELETE_ART);
	cm.send_int_parameter(ng_id);
	cm.send_int_parameter(art_id);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_DELETE_ART) {
		throw ProtocolViolationException("In Delete Article: ", Protocol::ANS_DELETE_ART, code);
	}
	code = cm.recv_code();
	if (code == Protocol::ANS_ACK) {
		cout << "Article with id \"" << art_id << "\" in newsgroup with id \"" << ng_id << "\" successfully deleted.";
	}
	else if (code == Protocol::ANS_NAK) {
		code = cm.recv_code();
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			cout << "No newsgroup with id \"" << ng_id << "\" exists.";
		}
		else if (code == Protocol::ERR_ART_DOES_NOT_EXIST) {
			cout << "No article with id \"" << art_id << "\" exists in newsgroup with id \"" << ng_id << "\".";
		}
		else {
			throw ProtocolViolationException("In Delete Article: ", Protocol::ERR_NG_DOES_NOT_EXIST, code);
		}
	}
	else {
		// Or ANS_NAK
		throw ProtocolViolationException("In Delete Article: ", Protocol::ANS_ACK, code);
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In Delete Article: ", Protocol::ANS_END, code);
	}
}

void get_article(connection_manager& cm){
	cout << "Fetch article in newsgroup" << endl;
	cout << "Enter newsgroup id: ";
	int ng_id = fetch_number();
	if (ng_id < 1) {
		cout << "No valid number was entered. Fetching aborted." << endl;
		return;
	}
	cout << "Enter article id: ";
	int art_id = fetch_number();
	if (art_id < 1) {
		cout << "No valid number was entered. Fetching aborted." << endl;
		return;
	}
	cm.send_code(Protocol::COM_GET_ART);
	cm.send_int_parameter(ng_id);
	cm.send_int_parameter(art_id);
	cm.send_code(Protocol::COM_END);

	int code = cm.recv_code();
	if (code != Protocol::ANS_DELETE_ART) {
		throw ProtocolViolationException("In Get Article: ", Protocol::ANS_DELETE_ART, code);
	}
	code = cm.recv_code();
	if (code == Protocol::ANS_ACK) {
		cout << "Article with id \"" << art_id << "\" in newsgroup with id \"" << ng_id << "\" successfully deleted.";
		string title = cm.recv_string_parameter();
		string author = cm.recv_string_parameter();
		string text = cm.recv_string_parameter();
		cout << title << " (by " << author << ")" << endl;
		cout << text << endl;
	}
	else if (code == Protocol::ANS_NAK) {
		code = cm.recv_code();
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			cout << "No newsgroup with id \"" << ng_id << "\" exists.";
		}
		else if (code == Protocol::ERR_ART_DOES_NOT_EXIST) {
			cout << "No article with id \"" << art_id << "\" exists in newsgroup with id \"" << ng_id << "\".";
		}
		else {
			throw ProtocolViolationException("In Get Article: ", Protocol::ERR_NG_DOES_NOT_EXIST, code);
		}
	}
	else {
		// Or ANS_NAK
		throw ProtocolViolationException("In Get Article: ", Protocol::ANS_ACK, code);
	}
	code = cm.recv_code();
	if (code != Protocol::ANS_END) {
		throw ProtocolViolationException("In Get Article: ", Protocol::ANS_END, code);
	}
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
	shared_ptr<Connection> ptr(&conn);
	connection_manager cm(ptr);

	bool run = true;
	while(run){
		print_menu();
		int action = fetch_number();
		while (!action || action < 7) {
			cout << "Not a valid option." << endl;
			action = fetch_number();
		}
		try{
			switch(action){
			case 1 : 
				list_newsgroups(cm);
				break;
			case 2 : 
				list_articles(cm);
				break;
			case 3 : 
				get_article(cm);
				break;
			case 4 :
				create_newsgroups(cm);
				break;
			case 5 :
				delete_newsgroups(cm);
				break;
			case 6 : 
				create_article(cm);
				break;
			case 7 :
				delete_article(cm);
				break;
			default:
				cout << "Congratz, you managed to break the system..." << endl;
				throw ConnectionClosedException();
				break;
			}
		}catch (ConnectionClosedException e){
			cout << "Connection closed" << endl;
			run = false;
		}catch (ProtocolViolationException e){
			cout << "Connection closed: " << e.what() << endl;
			run = false;
		}
	}
}

