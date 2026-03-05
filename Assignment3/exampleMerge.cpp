#include <iostream>
using namespace std;

long long comparisonCount = 0;
class LL {
private:
    struct Node {
        int data;
        Node* next;
        Node(int x) : data(x), next(nullptr) {}
    };

    Node* head;

    // Split list into two halves
    Node* split(Node* source) {
        Node* slow = source;
        Node* fast = source->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* second = slow->next;
        slow->next = nullptr;
        return second;
    }

    // Merge two sorted lists
    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        comparisonCount++;
        if (a->data <= b->data) {
            a->next = merge(a->next, b);
            return a;
        } else {
            b->next = merge(a, b->next);
            return b;
        }
    }

    // Recursive merge sort
    Node* mergeSort(Node* node) {
        if (!node || !node->next)
            return node;

        Node* second = split(node);

        node = mergeSort(node);
        second = mergeSort(second);

        return merge(node, second);
    }

public:
    LL() : head(nullptr) {}

    void push_back(int x) {
        Node* newNode = new Node(x);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }

    void sort() {
        head = mergeSort(head);
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LL list;
	int x;

	while (cin >> x)
		list.push_back(x);

    list.sort();
}