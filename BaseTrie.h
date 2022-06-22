#ifndef BASETRIE_H_INCLUDED
#define BASETRIE_H_INCLUDED

#include <vector>
#include <QString>
#include <QChar>
#include <QByteArray>
#include <cstdlib>

struct TrieNode
{
    const static int CHILDNUM = 26;
    TrieNode():value_(-1){
        for (int i = 0; i < CHILDNUM; ++i)
        {
        	end[i]=0;
            next_[i] = NULL;
        }
    }
    int value_;
    int end[CHILDNUM];
    TrieNode *next_[CHILDNUM];
};

class BaseTrie {
public:
    TrieNode* pRoot_;
    BaseTrie():pRoot_(NULL) {}
    void insert(QString s, int value);
    int search(QString s);
};

#endif // BASETRIE_H_INCLUDED
