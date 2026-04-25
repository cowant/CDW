#include <iostream>

class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    
    void add(int val) {
        Node* newNode = new Node(val); // 内部直接使用 Node
        newNode->next = head;
        head = newNode;
    }

private:
    // 嵌套类：Node 只在 LinkedList 内部有意义，所以设为 private
    class Node {
    public:
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head; // 外围类使用嵌套类定义的类型

};

int main() {
    LinkedList list;
    list.add(10);
    // LinkedList::Node node; // 报错！因为 Node 在 private 区块
    return 0;
}
