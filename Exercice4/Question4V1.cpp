#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void lireGraphe(const string& nomFichier, vector<vector<int>>& adj, int& n, int& m) {
    ifstream fin(nomFichier);
    if (!fin) {
        cerr << "Erreur : impossible d’ouvrir le fichier " << nomFichier << endl;
        exit(1);
    }

    fin >> n >> m;
    adj.assign(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u - 1][v - 1] = 1;
        adj[v - 1][u - 1] = 1;
    }
    fin.close();
}

void DFS(int sommet, const vector<vector<int>>& adj, vector<bool>& visite, vector<int>& composante) {
    visite[sommet] = true;
    composante.push_back(sommet);

    for (int i = 0; i < adj.size(); ++i) {
        if (adj[sommet][i] == 1 && !visite[i]) {
            DFS(i, adj, visite, composante);
        }
    }
}

vector<vector<int>> trouverComposantes(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visite(n, false);
    vector<vector<int>> composantes;

    for (int i = 0; i < n; ++i) {
        if (!visite[i]) {
            vector<int> composante;
            DFS(i, adj, visite, composante);
            composantes.push_back(composante);
        }
    }
    return composantes;
}

void ecrireResultat(const string& nomFichier, const vector<vector<int>>& composantes) {
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

    lireGraphe("../Exercice4/INPCONGRAPH.txt", adj, n, m);

    vector<vector<int>> composantes = trouverComposantes(adj);

    ecrireResultat("../Exercice4/OUTCONGRAPH.TXT", composantes);

    if (composantes.size() == 1)
        cout << "Le graphe est connexe." << endl;
    else
        cout << "Le graphe n’est pas connexe. Il a " << composantes.size() << " composantes." << endl;

    return 0;
}
