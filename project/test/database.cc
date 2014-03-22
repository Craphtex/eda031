#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "database.h"
#include "article.h"
#include <stdexcept>



using namespace std;
Database::Database(){
	count = 0;
	artid = 0;
}
// skapar newsgroup
bool Database::createNewsgroup(const string name){
	if(find_if(maps.begin(), maps.end(),[name](pair<int, string> temp){return temp.second == name;}) == maps.end()){
		maps.insert(pair<int,string>(count,name));
		++count;
		return true;
	}
	return false;
}
//skapar ny artikel med int som parameter som visar vilken newsgroup som den tillhör
bool Database::createArticle(const int ng, const string artname,const string auth,const string art){
	if(maps.find(ng)!=maps.end()){
		Article a(ng, artid,artname,auth,art);
		auto temp = find_if(data.begin(), data.end(), [ng](pair<int, vector<Article>> p1){return p1.first ==ng;});
		if(temp!=data.end()){
			temp->second.push_back(a);
			
		} else{
			vector<Article> temp2;
			temp2.push_back(a);
			data.insert(make_pair(ng,temp2));
			
		}
		//cout << "Newsgroup: " <<  a.getNewsGroup() << endl <<"Art id: " << a.getIdNbr() << endl <<"Article name: " << a.getArticleName() << endl << "Author: " << a.getAuthor() << endl << "Artikel: " << a.getArticle() << endl;
		++artid;
		return true;
	}
		//cout << "Newsgroup not found, try again" << endl;
		return false;
}

bool Database::removeNewsgroup(const int ng){
	auto it = maps.find(ng);
	if(it != maps.end()){
		maps.erase(it);
		return true;
	}
	return false;
}

bool Database::removeArticle(const int ng, const int id){
	auto i = maps.find(ng);
	if(i != maps.end()){
		auto index = data.find(ng);
		for(auto j = index->second.begin();j != index->second.end(); ++j){
			if(id == j->getIdNbr()){
				index->second.erase(j);
				return true;
				}
		}	
	}
	return false;
}

vector<pair<int, string>> Database::showNewsGroups(){
	vector<pair<int, string>> temp;
	for (auto pos = maps.begin(); pos != maps.end(); ++pos) {
		temp.push_back(make_pair(pos->first, pos->second));
    }
    return temp;
}

vector<pair<int, string>> Database::showArticles(const int ng){
	vector<pair<int, string>> temp;
	auto i = data.find(ng);
	if(i != data.end()){
		auto index = data.find(ng);

		for(auto j = index->second.begin();j !=index->second.end(); ++j){
			temp.push_back(make_pair(j->getIdNbr(), j->getArticleName()));
		}
	}
	return temp;
}
Article Database::showArticle(const int ng,const int id){
	auto i = maps.find(ng);
	if(i != maps.end()){
		auto index = data.find(ng);
		for(auto j = index->second.begin();j != index->second.end();++j){
			if(id == j->getIdNbr()){
				return *j;
			}
		}
	}
	throw out_of_range("No article found with that Newsgroup id and/or that article id");
}
bool Database::hasNewsGroup(const int ng){
	return maps.find(ng) != maps.end();
}


