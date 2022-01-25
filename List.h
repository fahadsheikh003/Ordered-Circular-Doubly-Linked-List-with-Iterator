#pragma once
//Fahad Waheed

template <typename T>
class List
{
	struct Node
	{
		T data;
		Node* next, * previous;

		Node() : data(T()), next(NULL), previous(NULL) {};

		Node(T data) : data(data), next(NULL), previous(NULL) {};
	};

	Node* head, * tail;

	void firstNodeCreation(T data)
	{
		Node* newNode = new Node(data);
		newNode->next = newNode->previous = newNode;
		head = tail = newNode;
	}

	Node* Search(T data)
	{
		if (!isEmpty())
		{
			Node* currnode = head;
			do 
			{
				if (currnode->data == data)
					return currnode;
				currnode = currnode->next;
			} while (currnode != head);
		}
		return NULL;
	}

public:
	List() : head(NULL), tail(NULL) {};

	List(const List<T>& obj) : head(NULL), tail(NULL)
	{
		if (!obj.isEmpty())
		{
			Node* currnode = obj.head;
			do
			{
				this->Insert(currnode->data);
				currnode = currnode->next;
			} while (currnode != obj.head);
		}
	}

	List& operator=(const List<T>& obj)
	{
		this->clear();
		if (!obj.isEmpty())
		{
			Node* currnode = obj.head;
			do
			{
				this->Insert(currnode->data);
				currnode = currnode->next;
			} while (currnode != obj.head);
		}
		return *this;
	}

	bool isEmpty()
	{
		return head == NULL && tail == NULL;
	}

	void Insert(T data)
	{
		if (isEmpty())
			firstNodeCreation(data);
		else if (data < head->data)
		{
			Node* newNode = new Node(data);
			newNode->previous = tail;
			newNode->next = head;
			head->previous = newNode;
			tail->next = newNode;
			head = newNode;
		}
		else
		{
			Node* currnode = head->next;
			Node* newNode = new Node(data);

			while (currnode != head && data > currnode->data)
				currnode = currnode->next;
				
			newNode->next = currnode;
			newNode->previous = currnode->previous;
			currnode->previous->next = newNode;
			currnode->previous = newNode;

			if (currnode == head)
			{
				tail = newNode;
			}
		}
	}

	void Remove(T data)
	{
		Node* dNode = Search(data);
		if (dNode)
		{
			if (dNode == head && dNode == tail)
			{
				head = tail = NULL;
			}
			else if (dNode == head)
			{
				head = head->next;
				head->previous = tail;
				tail->next = head;
			}
			else if (dNode == tail)
			{
				tail = tail->previous;
				tail->next = head;
				head->previous = tail;
			}
			else
			{
				dNode->previous->next = dNode->next;
				dNode->next->previous = dNode->previous;
			}

			delete dNode;
		}
	}

	void Update(T oldData, T newData)
	{
		Node* currnode = Search(oldData);

		if (currnode)
			currnode->data = newData;
	}

	int Find(T data)
	{
		int count = 0;

		Node* currnode = head;
		do
		{
			if (currnode->data == data)
				return count;
			currnode = currnode->next;
			count++;
		} while (currnode != head);
		
		return -1;
	}

	class Interator
	{
		Node* it;

	public:
		Interator() : it(NULL) {};

		void operator=(Node* node)
		{
			it = node;
		}

		T operator*()
		{
			return it->data;
		}

		void operator++()
		{
			it = it->next;
		}

		void operator++(int)
		{
			it = it->next;
		}

		bool operator==(Node* node)
		{
			return this->it == node;
		}

		bool operator!=(Node* node)
		{
			return this->it != node;
		}
	};

	Node* begin()
	{
		return head;
	}

	Node* end()
	{
		if (tail)
			return tail->next;
		return NULL;
	}

	void clear()
	{
		if (!isEmpty())
		{
			Node* currnode = head;
			do
			{
				head = head->next;
				delete currnode;
				currnode = head;
			} while (head != tail);
			if (tail)
				delete tail;
			tail = head = NULL;
		}
	}

	T operator[](int index)
	{
		int i = 0;
		Node* currnode = head;
		while (currnode && i != index)
		{
			currnode = currnode->next;
			i++;
		}
		if (currnode)
			return currnode->data;
		return T();
	}

	~List()
	{
		clear();
	}
};
