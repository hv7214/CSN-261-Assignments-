#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMainWindow>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegExp>
#include <QPushButton>
#include <QDir>

namespace Ui {
class Dictionary;
}

struct TrieNode {
    public :
        bool isendofword;
        QHash<QChar, TrieNode*> m;
        QString meaning;

        TrieNode() {
            isendofword = false;
        }

};

class Trie{

    public:
        TrieNode *root;

        Trie() {
            root = nullptr;
        }

        void insert(QString word, QString meaning) {
            if(root == nullptr)
                root = new TrieNode();

            TrieNode *temp = root;

            for(int i = 0; i < word.length(); i++) {
                QChar c = word[i];

                if(temp->m.find(c) == temp->m.end())
                    temp->m.insert(c, new TrieNode());

                temp = temp->m[c];
            }

            temp->isendofword = true;
            temp->meaning = meaning;
        }

        QString search(QString word) {
            if(root == nullptr) {return "Dictionary is empty";}

            TrieNode *temp = root;

            for(int i = 0; i < word.length(); i++) {
                QChar c = word[i];

                if(temp->m.find(c) == temp->m.end()) {return "Not Found";}

                temp = temp->m[c];
            }

            if(!temp->isendofword) {return "Not Found";}
            return temp->meaning;
        }
};

class Dictionary : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dictionary(QWidget *parent = nullptr);
    ~Dictionary();
    void LoadData(QString filename);
    Trie trie;
public slots:
        void SearchMeaning();

private:
    Ui::Dictionary *ui;
    QPushButton *button;

};

#endif // DICTIONARY_H
