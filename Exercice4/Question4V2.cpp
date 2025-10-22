// en utilisant une liste d'adjacence
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void lireGrapheListe(const string& nomFichier, vector<vector<int>>& adj, int& n, int& m) {
    ifstream fin(nomFichier);
    if (!fin) {
        cerr << "Erreur : impossible d’ouvrir le fichier " << nomFichier << endl;
        exit(1);
    }

    fin >> n >> m;
    adj.assign(n, {});

    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    fin.close();
}

void DFSListe(int sommet, const vector<vector<int>>& adj, vector<bool>& visite, vector<int>& composante) {
    visite[sommet] = true;
    composante.push_back(sommet);

    for (int voisin : adj[sommet]) {
        if (!visite[voisin]) {
            DFSListe(voisin, adj, visite, composante);
        }
    }
}

vector<vector<int>> trouverComposantesListe(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visite(n, false);
    vector<vector<int>> composantes;

    for (int i = 0; i < n; ++i) {
        if (!visite[i]) {
            vector<int> composante;
            DFSListe(i, adj, visite, composante);
            composantes.push_back(composante);
        }
    }

    return composantes;
}

void ecrireResultatListe(const string& nomFichier, const vector<vector<int>>& composantes) {
    ofstream fout(nomFichier);
    if (!fout) {
        cerr << "Erreur : impossible d’écrire dans " << nomFichier << endl;
        exit(1);
    }

    fout << composantes.size() << endl;
    for (int i = 0; i < composantes.size(); ++i) {
        fout << "composante connexe " << i + 1 << endl;
        for (int s : composantes[i])
            fout << s + 1 << " ";
        fout << endl;
    }

    fout.close();
}


int main() {
    vector<vector<int>> adj;
    int n, m;

    lireGrapheListe("../Exercice4/INPCONGRAPH.txt", adj, n, m);

    vector<vector<int>> composantes = trouverComposantesListe(adj);

    ecrireResultatListe("../Exercice4/OUTCONGRAPH_LIST.TXT", composantes);

    if (composantes.size() == 1)
        cout << "Le graphe est connexe." << endl;
    else
        cout << "Le graphe n’est pas connexe. Il a " << composantes.size() << " composantes." << endl;

    return 0;
}
