#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;

    Node(int data) : data(data), next(nullptr) {}

};

Node *head, *tail;

void push_front(int x) {
    Node *node = new Node(x);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head = node;
    }
}

void push_back(int x) {
    Node *node = new Node(x);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

void erase(Node **head, int x) {
    Node *pre;
    // 如果头结点是要删除的结点
    pre = *head;
    if ((*head)->data == x) {
        (*head) = (*head)->next;
        delete pre;
        return;
    }
    // 寻找要删除的结点
    while (pre->next != nullptr && pre->next->data != x) {
        pre = pre->next;
    }

    // 如果找到，则删除结点
    Node *current;
    if (pre->next != nullptr) {
        current = pre->next;
        pre->next = pre->next->next;
        delete current;
    }
}

void display(Node *head) {
    while (head != nullptr) {
        cout << head->data << endl;
        head = head->next;
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    int a[100];
    cout << a << endl;

    push_front(1);
    push_front(2);
    push_front(3);

    push_back(4);
    push_back(5);
    push_back(6);

    erase(&head, 4);
    erase(&head, 2);
    display(head);

    return 0;
}
