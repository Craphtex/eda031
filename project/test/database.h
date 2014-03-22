#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "article.h"
using namespace std;
class Database{
	public:
		Database();
		bool createNewsgroup(const string name);
		bool createArticle(const int ng, const string artname,const string auth,const string art);
		bool removeNewsgroup(const int id);
		bool removeArticle(const int ng, const int id);
		vector<pair<int, string>> showNewsGroups();
		vector<pair<int, string>> showArticles(const int ng);
		Article showArticle(const int ng,const int id);
		bool hasNewsGroup(const int ng);
	
	private:
		unordered_map<int, vector<Article>> data;
		map<int,string> maps;
		int count;
		string name;
		int artid;

};

#endif