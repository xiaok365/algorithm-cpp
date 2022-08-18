#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <cstring>

#define ALPHABET_SIZE 26
#define WORD_SIZE 100
#define WORD_NUM 10000

struct Node {
    int order_;
    bool is_word_;
    Node *child_[ALPHABET_SIZE];

    Node() : order_(-1), is_word_(false) {
        memset(child_, 0, sizeof child_);
    }
};

class Trie {
public:

    Trie() {
        memset(word_, 0, sizeof word_);
        memset(cnt_, 0, sizeof cnt_);
        order_ = 0;
    }

    int Insert(const char word[], int len);

    bool Find(const char word[], int len);

    int Size() const { return order_; }

    char *GetWord(int i) { return word_[i]; }

    int WordCnt(int i) { return cnt_[i]; }

private:
    Node root_;
    char word_[WORD_NUM][WORD_SIZE];
    int cnt_[WORD_NUM], order_;
};

int Trie::Insert(const char word[], int len) {

    Node *p = &root_;
    for (int i = 0; i < len; ++i) {
        int j = word[i] - 'a';
//        if (j < 0 || j > 25) continue;
        if (!p->child_[j]) {
            p->child_[j] = new Node;
        }
        p = p->child_[j];
    }

    if (!p->is_word_) {
        p->is_word_ = true;
        p->order_ = order_;
        strcpy(word_[order_++], word);
    }
    cnt_[p->order_]++;
    return p->order_;
}

bool Trie::Find(const char word[], int len) {

    Node *p = &root_;
    for (int i = 0; i < len; ++i) {
        int j = word[i] - 'a';
//        if (j < 0 || j > 25) continue;
        if (!p->child_[j]) {
            return false;
        }
        p = p->child_[j];
    }
    return p->is_word_;
}

#endif //TRIE_TRIE_H
