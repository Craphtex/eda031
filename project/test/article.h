#ifndef ARTICLE_H
#define ARTICLE_H
#include <string>

using namespace std;

class Article{
public:
	Article(const int ng, const int id, const string artname, const string auth, const string art):newsgroup(ng), idnbr(id), articlename(artname), author(auth), article(art){}
	int getNewsGroup() const {return newsgroup;}
	int getIdNbr() const {return idnbr;}
	string getArticleName() const {return articlename;}
	string getAuthor() const {return author;}
	string getArticle() const {return article;}
private:	
	int newsgroup;
	int idnbr;
	string articlename;
	string author;
	string article;
};

#endif


