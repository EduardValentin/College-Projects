#include < iostream >
#include < fstream > 
#include < vector > 
#include < list >

    using namespace std;

int main() {
    int n;
    ifstream fin("date.in");
    ofstream fout("date.out");

    fin >> n;

    vector < vector < int >> L(n + 1);
    vector < bool > viz(n + 1, 0);
    vector < int > g(n + 1, 0);
    vector < int > Sol;
    list < int > Add;

    int x, y;

    while (fin >> x >> y) {
        L[x].push_back(y);
        L[y].push_back(x);
        g[y]++;
        g[x]++;
    }

    // Pentru inceput se adauga frunzele la lista Add

    for (int i = 1; i <= n; i++) {
        if (L[i].size() == 1) {
            Add.push_back(i);
            viz[i] = true;
        }
    }

    while (!Add.empty()) {
        list < int > Parinti;

        while (!Add.empty()) {
            int frunzaCurenta = Add.back();
            Add.pop_back();
            Sol.push_back(frunzaCurenta); // se adauga frunza la solutie
            g[frunzaCurenta] = 0; // se elimina elementul

            /*
                Se elimina parintii frunzelor in felul urmator:
                    -> La adaugarea unei frunze la solutie gradul ei devine 0, adica se elimina din calcul
                    -> gradul parintelui frunzei curent eliminate scade cu o unitate
                    -> daca gradul parintelui dupa actualizare devine 1(adica nu mai are fii) se adauga in lista Parinti pentru a fi ulterior eliminat
            */

            for (int i = 0; i < L[frunzaCurenta].size(); i++) {
                int parinte = L[frunzaCurenta][i];
                g[parinte]--;
                if (g[parinte] == 1) {
                    // eliminam parintele doar atunci cand gradul sau devine 1
                    Parinti.push_back(parinte);
                }
            }
        }

        /*
            Se adauga noile frunze in felul urmator:
                -> gradul parintelui curent devine 0, adica se elimina din calcul
                -> se cauta toti descendentii lui si se scade gradul lor cu 1 pentru ca parintele curent este eliminat din calcul
                -> daca gradul unui descendent dupa actualizare devine 1, se adauga la lista Add pentru a fi adaugat ulterior la solutie
		*/
        while (!Parinti.empty()) {
            int parinteCurent = Parinti.back();
            Parinti.pop_back();
            g[parinteCurent] = 0;
            for (int i = 0; i < L[parinteCurent].size(); i++) {
                int descendent = L[parinteCurent][i];
                g[descendent]--;
                if (g[descendent] == 1)
                    Add.push_back(L[parinteCurent][i]);
            }
        }
    }

    for (int i = 0; i < Sol.size(); i++) {
        cout << Sol[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
