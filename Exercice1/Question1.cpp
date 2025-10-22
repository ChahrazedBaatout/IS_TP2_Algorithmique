#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void searchSousSequence(ifstream &fin, ofstream &fout) {
    int n;
    fin >> n;
    if (n > 5000 || n < 1) {
        cout << "Error: (n="<<n<<") <= 5000." << endl;
        exit(-1);
    }
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
        if (a[i] > 10000 || a[i] < -1000) {
            cout << "Error:  -10000 ≤ a[i] ≤ 10000" << endl;
            exit(-1);
        }
    }

    vector<int> dp(n, 1);
    vector<int> prev(n, -1);

    int max_len = 1, last = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            last = i;
        }
    }

    vector<int> indices;
    for (int i = last; i != -1; i = prev[i])
        indices.push_back(i);
    reverse(indices.begin(), indices.end());

    fout << max_len << "\n";
    for (int idx: indices)
        fout << "a[" << (idx + 1) << "] = " << a[idx] << "\n";

}

int main() {
    ifstream fin("../Exercice1/INPMONOSEQ.txt");
    ofstream fout("../Exercice1/OUTMONOSEQ.txt");
    if (!fin.is_open()) {
        cout << "Erreur : impossible d'ouvrir INPMONOSEQ.txt" << endl;
        return 1;
    }
    searchSousSequence(fin,fout);
    return 0;
}
