#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct TasMin {
    vector<int> heap, pos;
    vector<int>* dist;
    int size;
    TasMin(int n, vector<int>& d) : heap(n), pos(n), dist(&d), size(n) {
        for (int i = 0; i < n; ++i) {
            heap[i] = i;
            pos[i] = i;
        }
        buildTas();
    }
    void buildTas() {
        for (int i = size / 2 - 1; i >= 0; --i)
            Tasify(i);
    }
    void Tasify(int i) {
        int l = 2*i+1, r = 2*i+2, smallest = i;
        if (l < size && (*dist)[heap[l]] < (*dist)[heap[smallest]]) smallest = l;
        if (r < size && (*dist)[heap[r]] < (*dist)[heap[smallest]]) smallest = r;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            pos[heap[i]] = i; pos[heap[smallest]] = smallest;
            Tasify(smallest);
        }
    }
    int extractMin() {
        int u = heap[0];
        heap[0] = heap[--size];
        pos[heap[0]] = 0;
        Tasify(0);
        return u;
    }
    void decreaseKey(int u) {
        int i = pos[u];
        while (i > 0 && (*dist)[heap[i]] < (*dist)[heap[(i-1)/2]]) {
            swap(heap[i], heap[(i-1)/2]);
            pos[heap[i]] = i; pos[heap[(i-1)/2]] = (i-1)/2;
            i = (i-1)/2;
        }
    }
    bool empty() const {
        return size == 0;
    }
};

void dijkstraTasMatriceAdjacence(ifstream &fin, ofstream &fout) {
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
    dist[start] = 0;
    TasMin heap(n + 1, dist);

    while (!heap.empty()) {
        int u = heap.extractMin();
        if (dist[u] == numeric_limits<int>::max()) break;
        for (int v = 1; v <= n; ++v) {
            if (adj[u][v] > 0 && dist[v] > dist[u] + adj[u][v]) {
                dist[v] = dist[u] + adj[u][v];
                prev[v] = u;
                heap.decreaseKey(v);
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
    ofstream fout3("../Exercice5/OUTDIJGRAPH_TAS_MATRICE.txt");
    dijkstraMatriceAdjacence(fin, fout);
    fin.clear();
    fin.seekg(0, ios::beg);
    dijkstraListeAdjacence(fin,fout2);
    fin.clear();
    fin.seekg(0, ios::beg);
    dijkstraTasMatriceAdjacence(fin,fout3);
    return 0;
}