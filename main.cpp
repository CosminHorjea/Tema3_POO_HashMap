#include <iostream>
#include <list>

using namespace std;

int main()
{
	cout << 10;
}
/*
1 Tabel de dispersie
HashMap <class K, class V, class F = KeyHash<K>>
Implementat, i o clas˘a template pentru hash map. Clasa KeyHash<K> va fi
folosita pe post de functie hash default pentru calcularea hash-urilor pe chei.
ˆIn caz de coliziune HashMap-ul va p˘astra valorile ˆıntr-o list˘a ˆınl˘ant,uit˘a. Clasa
HashMap trebuie s˘a ofere:
• constructor f˘ar˘a parameterii care init, ializeaz˘a un HashMap gol;
• constructor de copiere s, i operator de atribuire;
• metod˘a de ad˘augare, c˘autare s, i s, tergere element nou ˆın HashMap;
• metod˘a ce ˆıntoare un vector (STL) cu valorile cunoscute pentru o anumit˘a
cheie;
• metod˘a pentru obt, inerea num˘arului de chei distincte din HashMap;
• supraˆınc˘arcarea operatorului [] care ˆıntoarce prima valoare cunoscut˘a pentru o cheie;
• supraˆınc˘arcarea operatorului de afis,are;
*/