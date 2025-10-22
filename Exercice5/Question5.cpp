#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

void dijkstraMatriceAdjacence(ifstream &fin, ofstream &fout) {
    int n, m, start, end;
    fin >> n >> m >> start >> end;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    vector<int> dist(n + 1, numeric_limits<int>::max());
    vector<int> prev(n + 1, -1);
    vector<bool> vis(n + 1, false);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int v = 1; v <= n; ++v) {
            if (adj[u][v] > 0 && dist[v] > dist[u] + adj[u][v]) {
                dist[v] = dist[u] + adj[u][v];
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    fout << dist[end] << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        fout << path[i];
        if (i + 1 < path.size()) fout << " → ";
    }
    fout << endl;
}

void dijkstraListeAdjacence(ifstream &fin, ofstream &fout) {
    int n, m, start, end;
    fin >> n >> m >> start >> end;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> dist(n + 1, numeric_limits<int>::max());
    vector<int> prev(n + 1, -1);
    vector<bool> vis(n + 1, false);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &[v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    fout << dist[end] << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        fout << path[i];
        if (i + 1 < path.size()) fout << " → ";
    }
    fout << endl;
}

int main() {
    ifstream fin("../Exercice5/INPDIJGRAPH.txt");
    ofstream fout("../Exercice5/OUTDIJGRAPH.txt");
    ofstream fout2("../Exercice5/OUTDIJGRAPH_LISTE.txt");
    dijkstraMatriceAdjacence(fin, fout);
    fin.clear();
    fin.seekg(0, ios::beg);
    dijkstraListeAdjacence(fin,fout2);
    return 0;
}