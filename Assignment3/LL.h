#ifndef LL_H
#define LL_H

#include <cstdlib>

template <class T>
class LL
{
public:
	// made node public so can access in cpp files
	class Node
	{
	public:
		Node() : data(T()), prev(nullptr), next(nullptr) {}
		Node(T item) : data(item), prev(nullptr), next(nullptr) {}

		T data;
		Node * prev;
		Node * next;
	};

	Node * head;
	Node * tail;

	
	class Iterator
	{
	private:
		Node * current;

	public:

		friend class LL;
		Iterator() : current(nullptr) {}
		Iterator(Node * n) : current(n) {}
		T operator*() { return current->data; }
		Iterator operator++()
		{
			current = current->next;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator it(*this);
			current = current->next;
			return it;
		}
		Iterator operator--()
		{
			current = current->prev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator it(*this);
			current = current->prev;
			return it;
		}
		bool operator==(Iterator rhs) const
		{
			return this->current == rhs.current;
		}
		bool operator!=(Iterator rhs) const
		{
			return this->current != rhs.current;
		}
	};

	LL();
	LL(const LL<T>&);
	const LL<T>& operator=(const LL<T>&);
	~LL();

	void push_front(const T&);
	void push_back(const T&);

	void pop_front();
	void pop_back();

	bool isEmpty() const {
    	return head == nullptr && tail == nullptr;
    }

	T front() const { 
		return head->data; 
	}

	T back() const { 
		return tail->data; 
	}

	void removeNode(Iterator&);
	void insertNode(const Iterator&, const T&);

	Iterator begin() const { return Iterator(head);}
	Iterator end() const { return Iterator(tail); }

	void swap(Iterator&, Iterator&);

	// merge sort functions
    Node* split(Node* head);
	Node* merge(Node* first, Node* second);
	Node* mergeSort(Node* head);

	Node* getHead() {
		return head;
	}

	// bubble sort functions
	void bubbleSort();

	// print function
	void printList();
};


#endif
