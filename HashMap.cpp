#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <string>
#include <set>
using namespace std;

template <class K>
class KeyHash
{
public:
	unsigned long operator()(K key)
	{
		return std::hash<K>{}(key) % 100;
	}
};
template <class K, class V, class F = KeyHash<K>>
class HashMap
{
	struct Node
	{
		K key;
		V value;
		Node *next;
	};
	const int SIZE = 100;
	vector<Node *> table;
	F hashFunction;

public:
	HashMap()
	{
		table.resize(100, NULL);
	}
	HashMap(const HashMap &hm)
	{
		this->SIZE = hm.size;
		this->hashFunction = hm.hashFunction;
		for (Node *i : hm.table)
		{
			if (i)
			{
				Node *aux = i;
				while (aux)
				{
					this->put(aux->key, aux->value);
					aux = aux->next;
				}
			}
		}
	};
	~HashMap()
	{
		for (Node *i : table)
		{
			if (i)
			{
				Node *aux = i;
				while (aux)
				{
					Node *d = aux;
					aux = aux->next;
					delete d;
				}
				i = NULL;
			}
		}
	}
	HashMap &operator=(const HashMap &hm)
	{
		if (this == &hm)
		{
			return *this;
		}
		this->size() = hm.SIZE;
		this->hashFunction = hm.hashFunction;
		for (Node *i : table) //sterg vechil obiect
		{
			Node *aux = i;
			while (aux)
			{
				Node *d = aux;
				aux = aux->next;
				delete d;
			}
			i = NULL;
		}

		for (Node *i : hm.table)
		{
			if (i)
			{
				Node *aux = i;
				while (aux)
				{
					this->put(aux->key, aux->value);
					aux = aux->next;
				}
			}
		}
	};
	void put(K key, V value)
	{
		unsigned long hashKey = hashFunction(key);
		Node *new_n = new Node;
		new_n->key = key;
		new_n->value = value;
		new_n->next = table[hashKey];
		table[hashKey] = new_n;
	}
	vector<V> getValues(K key)
	{
		unsigned long hashKey = hashFunction(key);
		vector<V> result;
		Node *aux = table[hashKey];
		while (aux)
		{
			if (aux->key == key)
			{
				result.push_back(aux->value);
			}
			aux = aux->next;
		}
		return result;
	}
	bool searchKey(K key)
	{
		unsigned long hashKey = hashFunction(key);
		Node *aux = table[hashKey];
		while (aux)
		{
			if (aux->key == key)
			{
				return true;
			}
			aux = aux->next;
		}
		return false;
	}
	void deleteKey(K key)
	{
		unsigned long hashKey = hashFunction(key);
		Node *aux = table[hashKey];
		Node *prev = NULL;
		while (aux && (aux->key == key))
		{
			Node *a = aux;
			table[hashKey] = aux->next;
			aux = aux->next;
			delete a;
		}
		while (aux)
		{
			if (aux->key == key)
			{
				prev->next = aux->next;
				Node *d;
				d = aux;
				aux = aux->next;
				delete d;
			}
			else
			{
				prev = aux;
				aux = aux->next;
			}
		}
	}
	unsigned getNumberOfDistinctKeys()
	{
		set<K> keys; //TODO change into a vector or something
		for (Node *i : table)
		{
			if (i)
			{
				Node *aux = i;
				while (aux)
				{
					keys.insert(aux->key);
					aux = aux->next;
				}
			}
		}
		return keys.size();
	}
	V &operator[](K key)
	{
		unsigned long hashKey = hashFunction(key);
		Node *aux = table[hashKey];
		while (aux)
		{
			if (aux->key == key)
			{
				return aux->value;
			}
		}
		throw - 1; //TODO eroare key
	}
	// template <class U, class W>
	friend ostream &operator<<(ostream &out, HashMap &hm)
	{
		for (Node *i : hm.table)
		{
			if (i != NULL)
			{
				Node *aux = i;
				while (aux)
				{
					cout << aux->key << ": " << aux->value << " " << endl;
					aux = aux->next;
				}
			}
		}
		return out;
	};
};

int main()
{
	HashMap<string, int> h;
	h.put("Alyca", 12);
	h.put("Robyca", 10);
	h.deleteKey("Alyca");
	h.put("Alyca", 13);
	h.put("Moise", 22);
	h.put("Alyca", 14);
	cout << h.searchKey("Alyca") << endl;
	cout << h;
	cout << h.getNumberOfDistinctKeys();
	// for (int i : h.getValues("Alyca"))
	// {
	// cout << i << " ";
	// }
	// cout << endl
	// 	 << h["Alyca"];
	// cout << endl
	// 	 << h;
}