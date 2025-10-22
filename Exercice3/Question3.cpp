#include <fstream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

void arbreCouvrantAvecMatriceAdjacence(ifstream &fin, ofstream &fout) {
    int n, m;
    fin >> n >> m;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u][v]++;
        adj[v][u]++;
    }

    vector<bool> vis(n + 1, false);
    queue<int> q;
    vis[1] = true;
    q.push(1);

        while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; ++v) {
            if (adj[u][v] > 0 && !vis[v]) {
                fout << u << " " << v << endl;
                vis[v] = true;
                q.push(v);
            }
        }
    }
}
void arbreCouvrantAvecListeAdjacence(ifstream &fin, ofstream &fout) {
    int n, m;
    fin >> n >> m;
    vector<list<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);
    queue<int> q;
    vis[1] = true;
    q.push(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                fout << u << " " << v << endl;
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    ifstream fin("../Exercice3/INPARBGRAPH.txt");
    ofstream fout("../Exercice3/OUTARBGRAPH.txt");
    ofstream fout2("../Exercice3/OUTARBGRAPH_LISTE.txt");

    arbreCouvrantAvecMatriceAdjacence(fin,fout);
    fin.clear();
    fin.seekg(0, ios::beg);
    arbreCouvrantAvecListeAdjacence(fin,fout2);
    return 0;
}