/*
    Idee: Jucatorul 1 are o strategie de castig daca diferenta maxima pe care o poate obtine e mare decat 0
    Subproblema: d[i][j] = diferenta maxima pe care o poate obtine jucatorul care e la mutare pe o tabla v[i..j]
    Recurenta:   d[i][j] = max{v[i] - d[i+1][j],v[j] - d[i][j-1]}
    Solutia problemei: Jucatorul 1 are strategie de castig daca d[1][n] > 0, altfel nu are.
    Ordine de calcul: i=n..1

    Pt a vedea ce alege  jucatorul care e la mutare verificam: 1) v[i] = d[i][j] + d[i+1][j] --> jucatorul trebuie sa aleaga v[i]
                                                               2) v[j] = d[i][j] + d[i+1][j] --> jucatorul trebuie sa aleaga v[j]

*/

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

ifstream fin("joculet.in");
ofstream fout("joculet.out");

long long n, i, j, d[2001][2001], v[2001];

long long max(const long long a, const long long b)
{
	return ((a > b) ? a : b);
}

int main()
{
	fin >> n;
	for (i = 1; i <= n; i++)
		fin >> v[i];

	///D[i][j] = diferenta maxima pe care o poate obtine jucatorul aflat la mutare pe o tabla cu numere de la i..j

	d[n][n] = v[n];

	for (i = n - 1; i >= 1; i--)
	{
		for (j = i; j <= n; j++)
		{
			if (i == j)
				d[i][i] = v[i];
			else
				d[i][j] = max(v[i] - d[i+1][j], v[j] - d[i][j - 1]);

		}

	}
	if (d[1][n] > 0)
	{
		int st = 1, dr = n, i = 1, compSum = 0, playerSum = 0;
		int compMove = 1; // 1 = muta computerul, -1 = muta jucatorul 2

		fout << "First player can win.\n " << d[1][n] << ".\n";

		while(st <= dr)
		{
			if (compMove == 1)
			{
				fout << "Player 1 wins by " << d[st][dr] << endl;

				fout << i << " : Player 1 takes ";

				if (v[st] == d[st][dr] + d[st + 1][dr])
				{
					fout << v[st] << endl;
					i++;
					compSum += v[st++];
				}
				else
				{
					fout << v[dr] << endl;
					i++;
					compSum += v[dr--];
				}

			}
			else
			{
				fout << i << " : Player 2 takes ";

				if (v[st] == d[st][dr] + d[st + 1][dr])
				{
					fout << v[st] << endl;
					i++;
					playerSum += v[st++];
				}
				else
				{
					fout << v[dr] << endl;
					i++;
					playerSum += v[dr--];
				}

			}

			compMove *= -1;
		}

	}
	return 0;
}
