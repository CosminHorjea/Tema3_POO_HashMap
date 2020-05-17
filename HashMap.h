#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <exception>
#include "KeyHash.h"
using namespace std;

template <class K, class V, class F = KeyHash<K>>
class HashMap
{
	struct Node
	{
		K key;
		vector<V> values;
		Node *next;
	};
	const int SIZE = 100;
	vector<Node *> table;
	F hashFunction;
	unsigned distinctKeys = 0;

public:
	HashMap();
	HashMap(const HashMap &);
	~HashMap();
	HashMap &operator=(const HashMap &hm);
	void put(K key, V value);
	vector<V> getValues(K key);
	bool searchKey(K key);
	void deleteKey(K key);
	unsigned getNumberOfDistinctKeys();
	V &operator[](K key);
	template <class K1, class V1, class F1>
	friend ostream &operator<<(ostream &out, HashMap<K1, V1, F1> &hm)
	{
		for (Node *i : hm.table)
		{
			if (i != NULL)
			{
				Node *aux = i;
				while (aux)
				{
					cout << aux->key << ": ";
					for (V val : aux->values)
					{
						cout << val << " ";
					}
					cout << endl;
					aux = aux->next;
				}
			}
		}
		return out;
	};
};
template <class K, class V, class F>
HashMap<K, V, F>::HashMap()
{
	table.resize(SIZE, NULL);
}

template <class K, class V, class F>
HashMap<K, V, F>::HashMap(const HashMap<K, V, F> &hm) : SIZE(hm.SIZE)
{
	table.resize(SIZE, NULL);
	this->distinctKeys = 0;
	this->hashFunction = hm.hashFunction;
	for (Node *i : hm.table)
	{
		if (i != NULL)
		{
			Node *aux = i;
			while (aux != NULL)
			{
				for (V val : aux->values)
				{
					this->put(aux->key, val);
				}
				aux = aux->next;
			}
		}
	}
};

template <class K, class V, class F>
HashMap<K, V, F>::~HashMap()
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

template <class K, class V, class F>
HashMap<K, V, F> &HashMap<K, V, F>::operator=(const HashMap &hm)
{
	if (this == &hm)
	{
		return *this;
	}
	this->distinctKeys = 0;
	this->hashFunction = hm.hashFunction;
	for (Node *i : table) //sterg vechiul obiect
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
		if (i != NULL)
		{
			Node *aux = i;
			while (aux != NULL)
			{

				for (V val : aux->values)
				{
					put(aux->key, val);
				}
				aux = aux->next;
			}
		}
	}
	return *this;
}

template <class K, class V, class F>
void HashMap<K, V, F>::put(K key, V value)
{
	unsigned long hashKey = hashFunction(key);
	Node *new_n = new Node;
	new_n->key = key;
	new_n->values.push_back(value);
	new_n->next = NULL;
	Node *aux = table[hashKey];
	if (!aux)
	{
		table[hashKey] = new_n;
		distinctKeys++;
		return;
	}
	while (aux != NULL)
	{
		if (aux->key == key)
		{
			aux->values.push_back(value);
			break;
		}
		if (!aux->next)
		{
			aux->next = new_n;
			distinctKeys++;
			break;
		}
		aux = aux->next;
	}
}

template <class K, class V, class F>
vector<V> HashMap<K, V, F>::getValues(K key)
{
	unsigned long hashKey = hashFunction(key);
	Node *aux = table[hashKey];
	while (aux)
	{
		if (aux->key == key)
		{
			return aux->values;
		}
		aux = aux->next;
	}
}

template <class K, class V, class F>
bool HashMap<K, V, F>::searchKey(K key)
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

template <class K, class V, class F>
void HashMap<K, V, F>::deleteKey(K key)
{
	if (!this->searchKey(key))
	{
		throw out_of_range("Cheia " + key + " nu exista in HashMap");
	}
	unsigned long hashKey = hashFunction(key);
	Node *prev = NULL;
	Node *aux = table[hashKey];
	while (aux != NULL)
	{
		if (aux->key == key)
		{
			break;
		}
		prev = aux;
		aux = aux->next;
	}
	if (!prev)
	{
		table[hashKey] = aux->next;
		delete aux;
	}
	else
	{
		prev->next = aux->next;
		delete aux;
	}
	distinctKeys--;
}

template <class K, class V, class F>
unsigned HashMap<K, V, F>::getNumberOfDistinctKeys()
{
	return this->distinctKeys;
}

template <class K, class V, class F>
V &HashMap<K, V, F>::operator[](K key)
{
	unsigned long hashKey = hashFunction(key);
	Node *aux = table[hashKey];
	while (aux)
	{
		if (aux->key == key)
		{
			return aux->values[0];
		}
	}
	throw out_of_range("Cheia " + key + " nu exista in HashMap");
}