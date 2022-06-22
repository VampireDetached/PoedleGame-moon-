#include "BaseTrie.h"
#include <stack>
#include <QString>
#include <cassert>
#include <iostream>
#include <QChar>
#include <QDebug>
#include <QByteArray>
using namespace std;

void BaseTrie::insert(QString s, int value)
{
    TrieNode *p = NULL;
    if (!(p = pRoot_))
        p = pRoot_ = new TrieNode();
    int i = 0, k=0 ;
    QByteArray ss;
    ss.append(s);
    for (int i=0;i<5;i++)
    {
        QByteArray ax("一一一一一");
        k=(int)ss.at(i)-(int)ax.at(i);
        if (!p->next_[k])
        p->next_[k] = new TrieNode();
		p->end[k]=1;
        p = p->next_[k];
    }
    p->value_ = value;
}

int BaseTrie::search(QString s)
{
    TrieNode *p = NULL;
    if(!( p = pRoot_))
        return 0;
    int i = 0,k=0;
    QByteArray ss;
    ss.append(s);
    for (int i=0;i<5;i++)
    {
        QByteArray ax("aaaaa");
        k = (int)ss.at(i)-(int)ax.at(i);
        if (p->next_[k] == NULL)
            return 0;
        p = p->next_[k];
    }
    return 1;
}



