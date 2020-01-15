# ���������ܽ�

## ���ݽṹ

### ����

* �����󽻵�
* ������
* ������
* ����������
* k����������鲢

    ```c++
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <set>
    #include <map>
    #include <cassert>
    #include <algorithm>

    using namespace std;

    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    void printList(ListNode* head) {
        ListNode *tmp= head;
        while(tmp) {
            cout << tmp->val << " ";
            tmp = tmp->next;    
        }
        cout << endl;
    }

    ListNode* createList(vector<int>& data) {
        auto it = data.begin();
        ListNode* head = new ListNode(*it);
        ListNode* new_head = head;
        it++;
        for(; it != data.end(); it++) {
            ListNode* new_node = new ListNode(*it);
            head->next = new_node;
            head = head->next;
        }
        return new_head;
    }

    /* 
    leetcode-206  ������ת 
    ʾ��:
    ����: 1->2->3->4->5->NULL
    ���: 5->4->3->2->1->NULL
    */
    class Solution206 {
    public:
        ListNode* reverseList(ListNode* head) {
            if (head == NULL || head->next == NULL) {
                return head;
            }
            // ��������ָ�����η�ת
            // new_head����ת���µ�ͷ�ڵ�
            // cur����ǰ����ת�Ľڵ�
            ListNode* new_head = head;
            ListNode* cur = head->next;
            new_head->next = NULL;

            while(cur) {
                ListNode* tmp = cur->next;   // ������һ������ת�Ľڵ�

                cur->next = new_head;
                new_head = cur;

                cur = tmp;
            }

            return new_head;
        }
    };

    /*
    leetcode-92
    ��ת��λ�� m �� n ��������ʹ��һ��ɨ����ɷ�ת��
    ˵��:
    1 �� m �� n �� �����ȡ�

    ʾ��:
    ����: 1->2->3->4->5->NULL, m = 2, n = 4
    ���: 1->4->3->2->5->NULL
    */
    class Solution92 {
    public:
        ListNode* reverseBetween(ListNode* head, int m, int n) {
            if (head == NULL || head->next == NULL || m == n) {
                return head;
            }
            // һ��ɨ���¼�ĸ��ؼ��ڵ� 1 �� m �� n �� ������
            // m�������׽ڵ㣬fixed_begin == NULL����ת���ͷ�ڵ㼴Ϊ�µ�ͷ�ڵ㡣
            // n������β�ڵ㣬fixed_end == NULL�������������Ҫ���⴦��
            ListNode *fixed_begin = NULL;
            ListNode *fixed_end = NULL;
            ListNode *new_head = NULL;
            ListNode *new_end = NULL;
            ListNode* tmp = head;

            // ���ҵ�fixed_begin �� new_end��
            // new_head = fixed_begin->next
            // fixed_end = new_end->next
            for(int i = 1; i <=n; i++) {
                if (i == m-1) {          // m==1ʱ��fixed_begin==NULL
                    fixed_begin = tmp;
                }
                if (i == m) {
                    new_head = tmp;
                }
                if (i == n) {
                    new_end = tmp;
                }
                tmp = tmp->next;     
            }
            if (new_end != NULL) {
                fixed_end = new_end->next; // fixed_end����ΪNULL
            }

            // ��ת
            ListNode* cur = new_head->next;
            new_head->next = fixed_end;        // ���� β��

            while(cur != fixed_end && cur != NULL) {
                ListNode *tmp = cur->next;
                cur->next = new_head;
                new_head = cur;

                cur = tmp;
            }
            if (fixed_begin) {
                fixed_begin->next = new_head;      // ���� ͷ��
            } else {
                head = new_head;
            }

            return head;
        }
    };

    /*
    leetcode-160
    ��дһ�������ҵ������������ཻ����ʼ�ڵ㡣

    ����˼·1��
    ����һ��set����listA���нڵ��ַ���룻
    Ȼ�����α���listB��ÿһ���ڵ㣬�����set�У��򷵻ؽ��㡣

    ����˼·2��
    (1) ����listA�ĳ��Ⱥ�listB�ĳ��ȣ��ϳ����������ĳ���Ϊn��
    (2) �ϳ�����������ƶ�n��λ�ã����룩��
    (3) Ȼ��ͬʱ�ƶ�listA��listB��������ָ����ͬʱ����Ϊ���㡣
    */

    class Solution160 {
    public:
        ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
            set<ListNode *> setA;
            ListNode* intersectionNode = NULL;
            ListNode* tmp = headA;
            while (tmp != nullptr) {
                setA.insert(tmp);
                tmp = tmp->next;
            }
            tmp = headB;
            while (tmp != nullptr) {
                if (setA.find(tmp) != setA.end()) {
                    intersectionNode = tmp;
                    break;
                }
                tmp = tmp->next;
            }
            return intersectionNode;
        }

        ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB) {
            ListNode* intersectionNode = nullptr;

            if (headA == nullptr || headB == nullptr) {
                return nullptr;
            }

            ListNode* tmp = headA;
            int lenA=0, lenB=0;
            while (tmp->next != nullptr) {
                lenA++;
                tmp = tmp->next;
            }
            tmp = headB;
            while (tmp->next != nullptr) {
                lenB++;
                tmp = tmp->next;
            }

            if (lenA > lenB) {
                tmp = headA;
                while(lenA > lenB) {
                    tmp = tmp->next;
                    lenA--;
                }
                headA = tmp;
            } 
            if (lenB > lenA) {
                tmp = headB;
                while(lenB > lenA) {
                    tmp = tmp->next;
                    lenB--;
                }
                headB = tmp;
            }
            ListNode *tmpA = headA, *tmpB = headB;
            while (tmpA != nullptr && tmpB != nullptr)
            {
                if (tmpA == tmpB) {
                    intersectionNode = tmpA;
                    break;
                }
                tmpA = tmpA->next;
                tmpB = tmpB->next;
            }

            return intersectionNode;
        }
    };

    /*
    leetcode-142
    ��������
    ����һ��������������ʼ�뻷�ĵ�һ���ڵ㡣 ��������޻����򷵻� null��
    ˼·1��
    ����ͬʱ�Ѽ����ַ����set�����ٴ���set���ҵ�����ڵ�ʱ˵���л���

    ˼·2��
    ����ָ�����ܣ�
    ��ָ��ÿ����2������ָ��ÿ����1��������ָ����ڻ���ĳһ�㴦������
    ��ָ���ߵĲ�������ָ���ߵ��������� 2* (x + y) = x + y + z + y => x = z
    ���ۣ���ָ��ӿ�ʼ�ߣ���ָ��������㿪ʼ�ߣ������ĵ㼴Ϊ���㡣
    */

    class Solution142 {
    public:
        ListNode *detectCycle1(ListNode *head) {
            ListNode* crossNode = nullptr;
            set<ListNode*> mset;
            ListNode* tmp = head;
            while (tmp != nullptr) {
                if (mset.find(tmp) != mset.end()) {
                    crossNode = tmp;
                    break;
                }
                mset.insert(tmp);
                tmp = tmp->next;
            }
            return crossNode;
        }

        ListNode *detectCycle2(ListNode *head) {

            ListNode* crossNode = nullptr;
            ListNode* fastNode = head;
            ListNode* slowNode = head;
            ListNode* meetNode = nullptr;
            bool flag = false;
            while(fastNode && fastNode->next) {
                slowNode = slowNode->next;
                fastNode = fastNode->next;
                if (fastNode->next == nullptr) {
                    break;
                }
                fastNode = fastNode->next;
                if (fastNode == slowNode) {
                    meetNode = slowNode;       // ������
                    break;
                }
            }
            if (meetNode) {
                slowNode = head;
                fastNode = meetNode;
                while (slowNode != fastNode) {
                    slowNode = slowNode->next;
                    fastNode = fastNode->next;
                }
                crossNode = slowNode;
            }
            return crossNode;
        }
    };

    /*
    leetcode-86
    �ָ�����
    ����һ�������һ���ض�ֵ x����������зָ���ʹ������С�� x �Ľڵ㶼�ڴ��ڻ���� x �Ľڵ�֮ǰ��
    ��Ӧ����������������ÿ���ڵ�ĳ�ʼ���λ�á�
    ʾ��:

    ����: head = 1->4->3->2->5->2, x = 3
    ���: 1->2->2->4->3->5

    ˼·��
    ����������ʱͷ�ڵ㣨������ͷ������������Ҫ��Ԫ�ء�
    */

    class Solution86 {
    public:
        ListNode* partition(ListNode* head, int x) {

            if (head == nullptr || head->next == nullptr) {
                return head;
            }

            ListNode* littleNode = new ListNode(0);  // ��ʱ�ڵ㣬����С��x��Ԫ��
            ListNode* bigNode = new ListNode(0);     // ��ʱ�ڵ㣬�������ڵ���x��Ԫ��
            ListNode* littleHead = littleNode;
            ListNode* bigHead = bigNode;

            ListNode* tmp = head;
            while(tmp) {
                if (tmp->val < x) {
                    littleNode->next = tmp;
                    littleNode = littleNode->next;
                } else {
                    bigNode->next = tmp;
                    bigNode = bigNode->next;
                }
                tmp = tmp->next;
            }
            littleNode->next = bigHead->next;
            if (bigNode) {
                bigNode->next = nullptr;
            }

            return littleHead->next;
        }
    };

    /*
    leetcode-138
    ��������������
    ����һ������ÿ���ڵ����һ���������ӵ����ָ�룬��ָ�����ָ�������е��κνڵ��սڵ㡣
    Ҫ�󷵻�������������� 
    */

    class Node {
    public:
        int val;
        Node* next;
        Node* random;

        Node(int _val) {
            val = _val;
            next = NULL;
            random = NULL;
        }
    };

    /*
    3-->5-->7-->10->NULL
    3------>7
        5------>10
            7->7
    */
    Node* creatRandomList() {
        Node* head = new Node(3);
        Node* tmp = head;
        Node* node1 = new Node(5);
        Node* node2 = new Node(7);
        Node* node3 = new Node(10);
        head->next = node1;      // 3
        head->random = node2;
        node1->next = node2;     // 5
        node1->random = node3;
        node2->next = node3;     // 7
        node2->random = node2;
        return head;
    }

    void printRandomNode(Node* head) {

        Node* tmp = head;
        while(tmp) {
            int next = -1;
            int random = -1;
            if (tmp->next != nullptr) {
                next = tmp->next->val;
            }
            if (tmp->random != nullptr) {
                random = tmp->random->val;
            }
            cout << tmp->val << "-> ( " << next << ", " << random << " )" << endl;
            tmp = tmp->next; 
        }
    }

    class Solution138 {
    public:
        Node* copyRandomList(Node* head) {
            if (head == nullptr) {
                return nullptr;
            }

            Node* tmp = head;
            vector<Node *> nodes;    // index -- node
            vector<Node *> random_index; // index -- node��randomָ��ָ���node��ַ
            map<Node*, int> random_reverse_index; // node��randomָ��ָ���node��ַ -- index

            int index = 0;
            // �ռ�����ڵ㡢randomָ����Ϣ
            while(tmp) {
                nodes.push_back(new Node(tmp->val));
                random_reverse_index.insert(std::pair<Node*, int>(tmp, index));
                random_index.push_back(tmp->random);
                index++;
                tmp = tmp->next;
            }

            // ����ָ�루next��random��
            for(int i=0; i<nodes.size();i++) {
                // ����nextָ�루���һ��node��NULL,���ô���
                if ( i+1 < nodes.size()) {
                    nodes[i]->next = nodes[i+1];
                }
                // ����randomָ��
                assert(nodes.size() == random_index.size());
                auto it = random_reverse_index.find(random_index[i]);
                if (it != random_reverse_index.end()) {
                    nodes[i]->random = nodes[it->second];
                }
            }
            return nodes[0];
        }
    };

    /*
    leetcode-21
    �ϲ�������������
    ��������������ϲ�Ϊһ���µ������������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ� 
    */

    class Solution21 {
    public:
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
            // ����һ����ʱͷ�ڵ㣨��ͷ�ڵ㣩,�����������Ľ��������
            ListNode* head = new ListNode(0);     
            ListNode* t1 = l1;
            ListNode* t2 = l2;
            ListNode* tmp = head; 
            while(t1 && t2) {
                if (t1->val <= t2->val) {
                    tmp->next = t1;
                    t1 = t1->next;
                } else {
                    tmp->next = t2;
                    t2 = t2->next;
                }
                tmp = tmp->next;
            }
            while(t1) {
                tmp->next = t1;
                t1 = t1->next;
                tmp = tmp->next;
            }
            while(t2) {
                tmp->next = t2;
                t2 = t2->next;
                tmp = tmp->next;
            }
            return head->next;
        }
    };

    /*
    leetcode-23
    �ϲ�k����������
    ˼·��
    ��k���ڵ��ַ�ŵ�vector�У��ٽ�vector�����ٽ��ڵ�˳��������

    */

    class Solution23 {
    public:
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            vector<ListNode* > listSet;
            for(auto it=lists.begin(); it!=lists.end();it++) {
                ListNode* tmp = *it;
                while(tmp) {
                    listSet.push_back(tmp);
                    tmp = tmp->next;
                }
            }
            if (listSet.size() == 0) {
                return nullptr;
            }
            // �Զ���ȽϺ��������򣬴���
            std::sort(listSet.begin(), listSet.end(), sortList());
            for(size_t i=0; i<listSet.size();i++) {
                if (i < listSet.size() - 1) {
                    listSet[i]->next = listSet[i+1];
                } else {
                    listSet[i]->next = nullptr;
                }   
            }
            return listSet[0];
        }
    private:
        struct sortList{
            bool operator() (ListNode* a, ListNode* b) {
                return a->val < b->val; 
            }
        };
    };

    int main() {

        vector<int> data = {1, 22, 7};
        ListNode* head1 = createList(data);
        vector<int> data2 = {2, 35, 3};
        ListNode* head2 = createList(data2);
        vector<ListNode*> v = {head1, head2};
        Solution23 st23;
        ListNode* newhead = st23.mergeKLists(v);
        printList(newhead); 

        system("pause");
    }
    ```

### ��������ͼ

### ��������������������

### ��ϣ�����ַ���

### ջ�����С���

### �߼����ݽṹ

## �㷨

### ̰���㷨

### �ݹ顢���ݡ�����

### ��̬�滮
