#include "MyTrie.h"
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;
void MyTrie::minsert(const char* s, int value)
{
    TrieNode *p = NULL;
    if (!(p = pRoot_))
        p = pRoot_ = new TrieNode();
    int i =0, k = 0;
    while(s[i])
    {
        i++;
    }
    i--;
    while(i>=0)
    {
    	k = s[i--]-'a';
        //cout<<p->next_[k];
		if (!p->next_[k])
        p->next_[k] = new TrieNode();
        p->end[k]=1;
		p = p->next_[k];
    }
    p->value_ = value;
}

int MyTrie::msearch(const char *s)
{
    TrieNode *p = NULL;
    if(!( p = mRoot_))
        return -1;
    int i = 0, k = 0;
    while(s[i])
    {
        i++;
    }
	i--;
	while(i>=0)
	{
		k = s[i--]-'a';
        if (p->next_[k] == NULL)
            return -1;
        p = p->next_[k];
	}
    return p->value_;
}

void MyTrie::searchLastString(const char* s1)
{
	cout<<"Seraching LastString result:"<<endl;
    TrieNode * p = NULL;
    if(!( p = pRoot_))
    p=pRoot_;
    int i = 0, k = 0;
    while(s1[i])
    {
        i++;
    }
	i--;
	while(i>=0)
	{
		if (s1[i])
		{	
			k = s1[i]-'a';
			i--;
        	if(p->end[k]==1)
			{p=p->next_[k];}
			else
			{
				cout<<"[Failed]"<<endl;
				return;
			}
    	}
	}
    //enumerate all the children
    string str = s1;
    mtraverse(p, str);
}

void MyTrie::mtraverse(TrieNode *p,string str)
{
    if (p->value_ >= 0)
    {
        getString(str, p->value_);
    }
    for (int i = 0; i < TrieNode::CHILDNUM; ++i)
    {
        if (p->end[i])
        {
            char c = 'a'+i;
            mtraverse(p->next_[i], (c+str));
        }
    }
}
void MyTrie::reverseString(string str)
{
	int m=str.size()-1;
	for (int i=0;2*i<m;i++)
	{
		char l1=str[i];
		char l2=str[m-i];
		str.replace(m-i,1,1,l1);
		str.replace(i,1,1,l2);
	}
	cout<<endl;
}
void getmString(string &str, int &value)
{
	if(value>=0)
	printf("%s\n",str.c_str());
}
