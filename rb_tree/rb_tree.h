#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>

#define COLOR_RED  0x0
#define COLOR_BLACK 0x1

using namespace std;

template<typename K, typename V>
struct RBNode {

    K key;
    V value;
    unsigned char color: 1;
    RBNode *lson, *rson, *parent;

    RBNode(K key, V value) : key(key), value(value) {
        color = COLOR_RED;
        lson = NULL;
        rson = NULL;
        parent = NULL;
    }
};

template<typename K, typename V>
class TreeMap {
public:

    TreeMap();

    ~TreeMap();

    bool IsEmpty() {
        return !root_;
    }

    int Size() {
        return size_;
    }

    int Height();

    void ClearAll();

    RBNode<K, V> *Find(K key);

    RBNode<K, V> *FindMin();

    RBNode<K, V> *FindMax();

    // 刚好小于
    RBNode<K, V> *FindNextMin(K key);

    // 刚好大于
    RBNode<K, V> *FindNextMax(K key);

    void Insert(K key, V value);

    void Remove(K key);

    void PrintTree();

private:
    RBNode<K, V> *root_;
    int size_;

    void Clear(RBNode<K, V> *p);

    bool IsRed(RBNode<K, V> *p) {
        if (p && p->color == COLOR_RED) {
            return true;
        }
        return false;
    }

    bool IsBlack(RBNode<K, V> *p) {
        return !IsRed(p);
    }

    RBNode<K, V> *ParentOf(RBNode<K, V> *p) {
        if (p) {
            return p->parent;
        }
        return NULL;
    }

    RBNode<K, V> *LeftOf(RBNode<K, V> *p) {
        if (p) {
            return p->lson;
        }
        return NULL;
    }

    RBNode<K, V> *RightOf(RBNode<K, V> *p) {
        if (p) {
            return p->rson;
        }
        return NULL;
    }

    RBNode<K, V> *FindMin(RBNode<K, V> *p);

    RBNode<K, V> *FindMax(RBNode<K, V> *p);

    RBNode<K, V> *LeftRotate(RBNode<K, V> *x);

    RBNode<K, V> *RightRotate(RBNode<K, V> *y);

    void InsertFixup(RBNode<K, V> *p);

    void RemoveFixup(RBNode<K, V> *p);

    void Transplant(RBNode<K, V> *u, RBNode<K, V> *v);

    void PrintTree(RBNode<K, V> *p);
};

template<typename K, typename V>
TreeMap<K, V>::TreeMap() {
    root_ = NULL;
    size_ = 0;
}

template<typename K, typename V>
TreeMap<K, V>::~TreeMap() {
    ClearAll();
}

int max(int a, int b) {
    return a > b ? a : b;
}

template<typename K, typename V>
int GetHeight(RBNode<K, V> *p) {
    if (p == NULL) {
        return 0;
    }
    return max(GetHeight(p->lson) + 1, GetHeight(p->rson) + 1);
}

template<typename K, typename V>
int TreeMap<K, V>::Height() {
    return GetHeight(root_);
}

template<typename K, typename V>
void TreeMap<K, V>::ClearAll() {
    Clear(root_);
    root_ = NULL;
    size_ = 0;
}

template<typename K, typename V>
void TreeMap<K, V>::Clear(RBNode<K, V> *p) {

    if (!p) {
        return;
    }

    Clear(p->lson);
    Clear(p->rson);
    delete p;
}

template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::Find(K key) {

    RBNode<K, V> *p = root_;

    while (p) {
        if (p->key == key) {
            break;
        }
        if (p->key < key) {
            p = p->rson;
        } else {
            p = p->lson;
        }
    }

    return p;
}

template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::FindMin() {
    return FindMin(root_);
}


template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::FindMax() {
    return FindMax(root_);
}


template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::FindMin(RBNode<K, V> *p) {
    if (!p) {
        return NULL;
    }
    while (p->lson != NULL) {
        p = p->lson;
    }
    return p;
}


template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::FindMax(RBNode<K, V> *p) {
    if (!p) {
        return NULL;
    }
    while (p->rson != NULL) {
        p = p->rson;
    }
    return p;
}

template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::FindNextMin(K key) {

    RBNode<K, V> *tail = root_, *last;

    while (tail) {
        last = tail;
        if (key <= tail->key) {
            tail = tail->lson;
        } else {
            tail = tail->rson;
        }
    }

    while (last && last->key >= key) {
        last = last->parent;
    }

    if (last) {
        return last;
    }

    return FindMax();
}

template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::FindNextMax(K key) {

    RBNode<K, V> *tail = root_, *last;

    while (tail) {
        last = tail;
        if (key >= tail->key) {
            tail = tail->rson;
        } else {
            tail = tail->lson;
        }
    }

    while (last && last->key <= key) {
        last = last->parent;
    }

    if (last) {
        return last;
    }

    return FindMin();
}

template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::LeftRotate(RBNode<K, V> *x) {
    RBNode<K, V> *y = x->rson;

    x->rson = y->lson;
    if (y->lson) {
        y->lson->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        root_ = y;
    } else if (x == LeftOf(ParentOf(x))) {
        x->parent->lson = y;
    } else {
        x->parent->rson = y;
    }

    y->lson = x;
    x->parent = y;

    return y;
}

template<typename K, typename V>
RBNode<K, V> *TreeMap<K, V>::RightRotate(RBNode<K, V> *y) {
    RBNode<K, V> *x = y->lson;

    y->lson = x->rson;
    if (x->rson) {
        x->rson->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL) {
        root_ = x;
    } else if (y == LeftOf(ParentOf(y))) {
        y->parent->lson = x;
    } else {
        y->parent->rson = x;
    }

    x->rson = y;
    y->parent = x;

    return x;
}

template<typename K, typename V>
void TreeMap<K, V>::Insert(K key, V value) {

    RBNode<K, V> *p = new RBNode<K, V>(key, value);

    RBNode<K, V> *exist = Find(p->key);
    if (exist) {
        return;
    }

    size_++;

    RBNode<K, V> *tail = root_, *last = NULL;

    while (tail) {
        last = tail;
        if (p->key < tail->key) {
            tail = tail->lson;
        } else {
            tail = tail->rson;
        }
    }
    p->parent = last;
    if (last == NULL) {
        root_ = p;
    } else if (p->key < last->key) {
        last->lson = p;
    } else {
        last->rson = p;
    }
    InsertFixup(p);
}

template<typename K, typename V>
void TreeMap<K, V>::InsertFixup(RBNode<K, V> *p) {
    RBNode<K, V> *parent, *grand_parent, *uncle;

    while ((parent = ParentOf(p)) && IsRed(parent)) {
        grand_parent = ParentOf(parent);
        // 父亲在左
        if (parent == LeftOf(grand_parent)) {
            uncle = RightOf(grand_parent);
            // case 1 叔叔为红，向上回溯
            if (IsRed(uncle)) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                p = grand_parent;
            } else {
                // case 2 叔叔为黑，且当前为右孩子，转case 3
                if (p == RightOf(parent)) {
                    LeftRotate(parent);
                    RBNode<K, V> *temp = parent;
                    parent = p;
                    p = temp;
                }
                // case 3 叔叔为黑，且当前为左孩子
                parent->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                RightRotate(grand_parent);
            }
        } else {
            // 父亲在右
            uncle = LeftOf(grand_parent);
            // case 1 叔叔为红，向上回溯
            if (IsRed(uncle)) {
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                p = grand_parent;
            } else {
                // case 2 叔叔为黑，且当前为左孩子，转case 3
                if (p == LeftOf(parent)) {
                    RightRotate(parent);
                    RBNode<K, V> *temp = parent;
                    parent = p;
                    p = temp;
                }
                // case 3 叔叔为黑，且当前为右孩子
                parent->color = COLOR_BLACK;
                grand_parent->color = COLOR_RED;
                LeftRotate(grand_parent);
            }
        }
    }
    root_->color = COLOR_BLACK;
}

template<typename K, typename V>
void TreeMap<K, V>::Remove(K key) {
    if (IsEmpty()) {
        return;
    }

    RBNode<K, V> *p = Find(key);
    if (p == NULL) {
        cout << "remove failed, key=" << key << endl;
        return;
    }

    size_--;

    // 有2个孩子
    if (p->lson != NULL && p->rson != NULL) {
        // 用后继结点代替待删除结点
        RBNode<K, V> *replacement = FindMin(p->rson);
        p->value = replacement->value;
        p->key = replacement->key;
        p = replacement;
    }

    RBNode<K, V> *successor;

    if (p->lson != NULL) {
        successor = p->lson;
    } else {
        successor = p->rson;
    }

    if (successor != NULL) {
        Transplant(p, successor);
        if (p->color == COLOR_BLACK) {
            RemoveFixup(successor);
        }
    } else {
        if (p->color == COLOR_BLACK) {
            RemoveFixup(p);
        }
        Transplant(p, NULL);
    }

    delete p;
}

template<typename K, typename V>
void TreeMap<K, V>::RemoveFixup(RBNode<K, V> *p) {
    RBNode<K, V> *brother, *parent;

    while (p != root_ && IsBlack(p)) {

        parent = ParentOf(p);

        if (p == LeftOf(parent)) {
            brother = parent->rson;
            // 兄弟为红 转为case 2,3,4
            if (IsRed(brother)) {
                brother->color = COLOR_BLACK;
                parent->color = COLOR_RED;
                LeftRotate(parent);
                brother = RightOf(parent);
            }
            // 兄弟为黑
            // 兄弟2孩子都黑 case 2，向上回溯
            if (IsBlack(brother->lson) && IsBlack(brother->rson)) {
                brother->color = COLOR_RED;
                p = parent;
            } else {
                // case 3 左红右黑，转case 4
                if (IsBlack(brother->rson)) {
                    brother->color = COLOR_RED;
                    brother->lson->color = COLOR_BLACK;
                    RightRotate(brother);
                    brother = RightOf(parent);
                }
                // case 4 右红
                brother->rson->color = COLOR_BLACK;
                brother->color = parent->color;
                parent->color = COLOR_BLACK;
                LeftRotate(parent);
                break;
            }
        } else {
            brother = parent->lson;
            // 兄弟为红 转为case 2,3,4
            if (IsRed(brother)) {
                brother->color = COLOR_BLACK;
                parent->color = COLOR_RED;
                RightRotate(parent);
                brother = LeftOf(parent);
            }
            // 兄弟为黑
            // 兄弟2孩子都黑 case 2，向上回溯
            if (IsBlack(brother->lson) && IsBlack(brother->rson)) {
                brother->color = COLOR_RED;
                p = parent;
            } else {
                // case 3 左黑右红，转case 4
                if (IsBlack(brother->lson)) {
                    brother->color = COLOR_RED;
                    brother->rson->color = COLOR_BLACK;
                    LeftRotate(brother);
                    brother = LeftOf(parent);
                }
                // case 4 左红
                brother->lson->color = COLOR_BLACK;
                brother->color = parent->color;
                parent->color = COLOR_BLACK;
                RightRotate(parent);
                break;
            }
        }
    }

    p->color = COLOR_BLACK;
}

template<typename K, typename V>
void TreeMap<K, V>::Transplant(RBNode<K, V> *u, RBNode<K, V> *v) {
    if (!u->parent) {
        root_ = v;
    } else if (u == LeftOf(ParentOf(u))) {
        u->parent->lson = v;
    } else {
        u->parent->rson = v;
    }

    if (v) {
        v->parent = u->parent;
    }
}

template<typename K, typename V>
void TreeMap<K, V>::PrintTree() {
    PrintTree(root_);
}


template<typename K, typename V>
void TreeMap<K, V>::PrintTree(RBNode<K, V> *p) {

    if (p == NULL) {
        return;
    }
    printf("key=%d, color=%d\n", p->key, p->color);
    PrintTree(p->lson);
    PrintTree(p->rson);
}

#endif //RB_TREE_H
