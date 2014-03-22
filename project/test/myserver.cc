/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "connection_manager.h"
#include "protocol.h"
#include "database.h"
#include "article.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <unordered_map>

using namespace std;
Database db;
//Get a list of newsgroups from the database and send them to the client
void send_list(connection_manager& cm){
	vector<pair<int,string>> v = db.showNewsGroups();
	cm.send_code(Protocol::ANS_LIST_NG);
	cm.send_int_parameter(v.size());
	for(auto i = v.begin(); i != v.end(); ++i){
		cm.send_int_parameter(i->first);
		cm.send_string_parameter(i->second);
	}
}

//Create a new newsgroup from the data sent by the client
void create_newsgroup(connection_manager& cm){ 
	string name = cm.recv_string_parameter();
	cm.send_code(Protocol::ANS_CREATE_NG);
	if(db.createNewsgroup(name))
		cm.send_code(Protocol::ANS_ACK);
	else{
		cm.send_code(Protocol::ANS_NAK);
		cm.send_code(Protocol::ERR_NG_ALREADY_EXISTS);
	}
}

//Delete a newsgroup based in data sent by the client
void delete_newsgroup(connection_manager& cm){ 
	int id = cm.recv_int_parameter();
	cm.send_code(Protocol::ANS_DELETE_NG);
	if(db.removeNewsgroup(id))
		cm.send_code(Protocol::ANS_ACK);
	else{
		cm.send_code(Protocol::ANS_NAK);
		cm.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void send_art_list(connection_manager& cm){
	int id = cm.recv_int_parameter();
	vector<pair<int, string>> v = db.showArticles(id);
	cm.send_code(Protocol::ANS_LIST_ART);
	if(db.hasNewsGroup(id)){
		cm.send_code(Protocol::ANS_ACK);
		cm.send_int_parameter(v.size());
		for(auto i = v.begin(); i != v.end(); ++i){
			cm.send_int_parameter(i->first);
			cout << i->first << endl;
			cout << i->second << endl;
			cm.send_string_parameter(i->second);
		}
	}else{
		cm.send_code(Protocol::ANS_NAK);
		cm.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void create_article(connection_manager& cm){ //DONE
	int id = cm.recv_int_parameter();
	string title = cm.recv_string_parameter();
	string author = cm.recv_string_parameter();
	string text = cm.recv_string_parameter();
	cm.send_code(Protocol::ANS_CREATE_ART);
	if(db.createArticle(id, title, author, text))
		cm.send_code(Protocol::ANS_ACK);
	else{
		cm.send_code(Protocol::ANS_NAK);
		cm.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void delete_article(connection_manager& cm){
	int group_id = cm.recv_int_parameter();
	int id = cm.recv_int_parameter();
	cm.send_code(Protocol::ANS_DELETE_ART);
	if(db.removeArticle(group_id, id))
		cm.send_code(Protocol::ANS_ACK);
	else{
		cm.send_code(Protocol::ANS_NAK);
		if(db.hasNewsGroup(group_id))
			cm.send_code(Protocol::ERR_ART_DOES_NOT_EXIST);
		else
			cm.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void send_article(connection_manager& cm){
	int group_id = cm.recv_int_parameter();
	int id = cm.recv_int_parameter();
	cm.send_code(Protocol::ANS_GET_ART);
	if(db.hasNewsGroup(group_id)){
		try{
			Article a = db.showArticle(group_id,id);
			cm.send_code(Protocol::ANS_ACK);
			cm.send_string_parameter(a.getArticleName());
			cm.send_string_parameter(a.getAuthor());
			cm.send_string_parameter(a.getArticle());
		}catch(out_of_range e){
			cm.send_code(Protocol::ANS_NAK);
			cm.send_code(Protocol::ERR_ART_DOES_NOT_EXIST);		
		}
	}else{
		cm.send_code(Protocol::ANS_NAK);
		cm.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);	
	}
}

int main(int argc, char* argv[]){ //DONE
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

	
	while (true) {
		auto conn = server.waitForActivity();
		connection_manager cm(conn);
		if(conn != nullptr){
			bool run = true;
			while(run){
				try{
					int action = cm.recv_code();
					switch(action){
					case Protocol::COM_LIST_NG : 
						send_list(cm);
						break;
					case Protocol::COM_CREATE_NG : 
						create_newsgroup(cm);
						break;
					case Protocol::COM_DELETE_NG : 
						delete_newsgroup(cm);
						break;
					case Protocol::COM_LIST_ART :
						send_art_list(cm);
						break;
					case Protocol::COM_CREATE_ART :
						create_article(cm);
						break;
					case Protocol::COM_DELETE_ART : 
						delete_article(cm);
						break;
					case Protocol::COM_GET_ART :
						send_article(cm);
						break;
					case Protocol::COM_END : 
						cm.send_code(Protocol::ANS_END);
						run = false;
						break;
					}
				}catch (ConnectionClosedException e){ 
					server.deregisterConnection(conn);
					cout << "Connection closed" << endl;
					run = false;
				}catch (ProtocolViolationException e){
					server.deregisterConnection(conn);
					cout << "Connection closed: " << e.what() << endl;
					run = false;
				}
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
