#include <iostream>
#include <cstdlib>

using namespace std;

// 链表节点
struct Node {
    int val;
    Node *next;
};

// 创建一个链表
Node *createList() {
    Node *head = new Node;
    head->next = NULL;
    return head;
}

// 创建一个链表节点
Node *createNode(int val) {
    Node* new_node = new Node;
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

// 插入一个节点
Node* insertNode(Node* head, int val) {
    Node* new_node = createNode(val);
    // 头插法
    Node* tmp = head->next;
    head->next = new_node;
    new_node->next = tmp;
    return head;
}

// 删除一个节点
Node* deleteNode(Node* head, int val) {
    if (head==NULL) {
        return NULL;
    }
    Node* thead = head;
    Node* pre_thead = head;
    bool find_flag = false;
    while(thead->next) {
        pre_thead = thead;
        thead = thead->next;
        if (thead->val == val) {
            Node* tmp=thead->next;
            delete thead;
            pre_thead->next = tmp;
            find_flag = true;
            break;
        }
    }
    if (!find_flag) {
        cout << "cannot find cannot delete" << endl;
    }
    return head;
}

// 打印链表
void printLinkedlist(Node* head) {
    Node *tmp = head;
    while(tmp->next) {
        tmp = tmp->next;
        cout << tmp->val << " ";
    }
    cout << endl;
}

int main()
{
    Node *head = createList();
    insertNode(head, 3);  
    insertNode(head, 7);  
    insertNode(head, 33);  
    insertNode(head, 9);
    printLinkedlist(head);  

    deleteNode(head, 33);
    deleteNode(head, 333);
    deleteNode(head, 9);
    printLinkedlist(head);
    system("pause");
    return 0;
}