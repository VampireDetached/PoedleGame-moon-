#ifndef MYTRIE_H_INCLUDED
#define MYTRIE_H_INCLUDED

#include <vector>
#include <string>
#include <cstdlib> 
#include "BaseTrie.h" 
using namespace std;

class MyTrie : public BaseTrie
{
public:
	TrieNode* mRoot_;
	void mtraverse(TrieNode *p,string str);
	MyTrie():mRoot_(NULL) {};
	void minsert(const char* s, int value);
	int msearch(const char* s);
	void searchLastString(const char* s);
	void getmString(string &str,int &value);
	void reverseString(string str);
	~MyTrie(){
		delete mRoot_;
		delete pRoot_;
	}
};


#endif // MYTRIE_H_INCLUDED
