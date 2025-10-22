#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

struct State {
    int len, sum, prev_i, prev_j, take;

    State(int len = -1, int sum = 0, int prev_i = -1, int prev_j = -1, int take = 0)
        : len(len), sum(sum), prev_i(prev_i), prev_j(prev_j), take(take) {
    }
};

void process(ifstream &fin, ofstream &fout) {
    int n, k;
    fin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        fin >> a[i];

    vector<vector<State> > dp(n + 1, vector<State>(k));
    dp[0][0] = State(0, 0, -1, -1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < k; ++j) {
            State s1 = dp[i - 1][j];
            if (s1.len != -1) {
                if (dp[i][j].len < s1.len || (dp[i][j].len == s1.len && dp[i][j].sum < s1.sum)) {
                    dp[i][j] = State(s1.len, s1.sum, i - 1, j, 0);
                }
            }
            int j2 = (j - a[i] % k + k) % k;
            State s2 = dp[i - 1][j2];
            if (s2.len != -1) {
                int new_len = s2.len + 1;
                int new_sum = s2.sum + a[i];
                if (dp[i][j].len < new_len || (dp[i][j].len == new_len && dp[i][j].sum < new_sum)) {
                    dp[i][j] = State(new_len, new_sum, i - 1, j2, 1);
                }
            }
        }
    }

    vector<int> indices;
    int i = n, r = 0;
    while (i > 0) {
        State &s = dp[i][r];
        if (s.take) indices.push_back(i);
        int ni = s.prev_i, nr = s.prev_j;
        i = ni;
        r = nr;
        if (i == -1) break;
    }
    fout << dp[n][0].len << endl;
    int sum = 0;
    for (int idx: indices) {
        fout << "a[" << idx << "] = " << a[idx] << endl;
        sum += a[idx];
    }
    fout << "Sum = " << sum << endl;
}

int main() {
    ifstream fin("../Exercice2/INPDIVSEQ.txt");
    ofstream fout("../Exercice2/OUTDIVSEQ.txt");
    if (!fin.is_open()) {
        cout << "Erreur : impossible d'ouvrir INPDIVSEQ.txt" << endl;
        return 1;
    }
    process(fin, fout);
    return 0;
}
