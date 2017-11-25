
/* 
Subproblema		 ==> l[i] = lungimea maxima a unui subsir ce contine cuvantul i
					 poz[c1 c2] = pozitia la care se gaseste cuvantul ce contine ca prime doua litere c1 si c2 si formeaza un subsir maximal cu elementele deja procesate
					 p[i] = parintele cuvantului i

Recurenta		 ==> l[i] = 1 + l[poz[c1c2]] unde c1 si c2 sunt primele doua litere din cuvantul i

Solutie			 ==> max{l[i] | i = 1,n}
Regula de calcul ==> i = n,1
*/


#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void afisDrum(vector<string> &v, vector<int> &p, int idx)
{
	if (idx != -1)
	{
		cout << v[idx] << "\n";
		afisDrum(v, p, p[idx]);
	}
}

int main()
{
	size_t n;
	cin >> n;
	vector<string> v(n);
	vector<int> p(n, -1);
	vector<int> l(n, 1);

	map<string, int> poz;

	for (size_t i = 0; i < n; i++)
	{
		cin >> v[i];
	}

	for (int i = n-1; i >= 0; i--)
	{
		string firstTwo;
		firstTwo += v[i][0];
		firstTwo += v[i][1];

		string lastTwo;
		lastTwo += v[i][v[i].length() - 2];
		lastTwo += v[i][v[i].length() - 1];

		map<string, int>::iterator it_ftwo = poz.find(firstTwo);
		map<string, int>::iterator it_ltwo = poz.find(lastTwo);	

		if (it_ltwo != poz.end())
		{
			// Am calculat inainte
			l[i] = l[it_ltwo->second] + 1;
			p[i] = it_ltwo->second;	// Legam cu parintele
		}

		if (it_ftwo != poz.end())
		{
			if (l[it_ftwo->second] < l[i])	// Actualizam poz daca e cazul
				it_ftwo->second = i;
		}
		else
		{
			poz[firstTwo] = i;
		}
	}

	// Se calculeaza maximul lungimilor
	int lmax = -1, k;
	for (size_t i = 0; i < n; i++)
	{
		if (l[i] > lmax)
			lmax = l[i], k = i;
	}

	afisDrum(v, p, k);
	return 0;
}

