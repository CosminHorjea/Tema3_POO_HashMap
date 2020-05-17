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
	struct Node //structura unui nod din lista inalntuita
	{
		K key;
		vector<V> values;
		Node *next;
	};
	const int SIZE;
	vector<Node *> table;	   // tabelul cu pointeri catre liste simplu inlantuite
	F hashFunction;			   //functia de dispersie
	unsigned distinctKeys = 0; // numarul de chei distincte

public:
	HashMap();
	HashMap(const HashMap &);
	~HashMap();
	HashMap &operator=(const HashMap &hm);
	void put(K key, V value);
	vector<V> getValues(K key) const;
	bool searchKey(K key) const;
	void deleteKey(K key);
	unsigned getNumberOfDistinctKeys() const;
	V &operator[](K key) const;
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
HashMap<K, V, F>::HashMap() : SIZE(100)
{
	/*
		Constructor pentru clasas HashMap
	@desc
		setez marimea tabelului si toate valorile sunt NULL
	*/
	table.resize(SIZE, NULL);
}

template <class K, class V, class F>
HashMap<K, V, F>::HashMap(const HashMap<K, V, F> &hm) : SIZE(hm.SIZE)
{
	/*
		Copy Constructor pentru clasa HashMap
	@param
		hm- obiectul pe care il copiez
	@desc
		Copiez proprietatile din hm si dupa ceea introduc pe rand fiecare element
	*/
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
	/*
		Descturctor pentru clasa HashMap
	@desc
		Iau fiecare pointer din tabel catre listele inalntuire
		iar daca acestea nu sunt goale sterg elementele
		La final tabelul este contine pointeri NULL
	*/
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
	/*
		Operator= pentru clasa HashMap
	@param
		hm - valoare din partea dreapta a egalului
	@desc
		Mai intai sterg elementele din obiectul curent,
		iar dupa aceea introcud elementele din hm
	*/

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

	for (Node *i : hm.table) // copiez elementele din hm
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
	return *this; // returnez obiectul
}

template <class K, class V, class F>
void HashMap<K, V, F>::put(K key, V value)
{
	/*
		Introducerea unei perechi Key|Value in HashMap
	@param
		K key - cheia care trebuie inserata
		V value - valoarea asociata cheii
	@desc
		Merg prin lista inlantuita de la F(key), daca gasesc acea cheie
		o inserez in vectorul acelui nod,
		altfel nodul se insereaza la sfarsitul listei
	
	*/
	unsigned long hashKey = hashFunction(key); // calculez indexul din table
	Node *new_n = new Node;					   // fac un nod nou
	new_n->key = key;
	new_n->values.push_back(value);
	new_n->next = NULL;
	Node *aux = table[hashKey]; //merg in capul listei de la acel index
	if (!aux)					// daca lista e vida
	{
		table[hashKey] = new_n;
		distinctKeys++;
		return;
	}
	while (aux != NULL) // cat timp merg prin lista
	{
		if (aux->key == key) // daca cheia deja exista
		{
			aux->values.push_back(value); // pun valoarea in vectorul nodului
			break;
		}
		if (!aux->next) // daca sunt la capat de lista
		{
			aux->next = new_n; // adaug ultimul nod
			distinctKeys++;
			break;
		}
		aux = aux->next;
	}
}

template <class K, class V, class F>
vector<V> HashMap<K, V, F>::getValues(K key) const
{
	/*
		Gasirea tuturor valorilor pentru un anumit Key
	@param
		K key - cheia pentru care vreau valorile din HashMap
	@return
		vector<V> - un vector cu taote valorile pentru o anumita cheie
	*/
	unsigned long hashKey = hashFunction(key); // iau indexul din tabel
	Node *aux = table[hashKey];
	while (aux)
	{
		if (aux->key == key) // daca gasesc cheia din paramentru
		{
			return aux->values; // returnez valorile
		}
		aux = aux->next;
	}
}

template <class K, class V, class F>
bool HashMap<K, V, F>::searchKey(K key) const
{
	/*
		Cautarea unei chei in HahMap
	@param
		K key- cheia pe care o caut in HashMap
	@return
		bool - true daca am gasit cheia acautata, false altfel
	*/
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
	/*
		Stergerea unei valori din HashMap
	@param
		K key - cheia pe care vreau sa o sterg
	@desc
		Merg prin nodurule din lista asociata cheii si elimin nodul
	@throws
		out_of_rande - in cazul in care cheia din paramentru nu exista
	
	*/
	if (!this->searchKey(key))
	{
		throw out_of_range("Cheia " + key + " nu exista in HashMap");
	}
	unsigned long hashKey = hashFunction(key);
	Node *prev = NULL;			// iau un pointer care e in spatele celui cu care parcurg lista
	Node *aux = table[hashKey]; // pointerul cu care parcurg lsita
	while (aux != NULL)			// cat timp merg prin lista
	{
		if (aux->key == key) // daca am gasit cheia ma opresc
		{
			break;
		}
		prev = aux;		 //pointerul din spate avanseaza
		aux = aux->next; // pointerul de parcurgere avanseaza
	}
	if (!prev) // daca nu am pointer in spatem, inseamana ca ne aflam pe prima pozitie din lista
	{
		table[hashKey] = aux->next; // mut capul listei la urmatorul nod
		delete aux;
	}
	else
	{
		prev->next = aux->next; // altfel leg nodul din spate de cel care urmeaza
		delete aux;
	}
	distinctKeys--; // scad numarul de chei distincte din HashMap
}

template <class K, class V, class F>
unsigned HashMap<K, V, F>::getNumberOfDistinctKeys() const
{
	/*
		Aflarea numarului de chei distincte din HashMap
	@return
		unsigned int - o valoarea pozitiva care semnifica numarul de chei distincte
	*/
	return this->distinctKeys;
}

template <class K, class V, class F>
V &HashMap<K, V, F>::operator[](K key) const
{
	/*
		operator[] care intoarce prima valaore pentru o cheie data
	@param
		K key - cheia pe care vreau sa o accesez
	@return
		V - valoarea de pe prima pozitie din vectorul asociat cu cheia "key"
	@throws
		out_of_bounds - in cazul in care cheia solicitat nu exista
	*/
	if (!this->searchKey(key))
		throw out_of_range("Cheia " + key + " nu exista in HashMap");
	unsigned long hashKey = hashFunction(key);
	Node *aux = table[hashKey];
	while (aux)
	{
		if (aux->key == key)
		{
			return aux->values[0];
		}
	}
}