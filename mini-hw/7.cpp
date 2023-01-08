#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> C;

int n;
int m;
bool P[10000] = {0};

int compute() {
    int res = 0;
    for (int i = 0; i < m; i++) {
        int flag = 0;
        for (int j = 0; j < 3; j++) {
            int sign = C[i][j] > 0;
            flag = flag || (sign ? P[C[i][j]] : !P[C[i][j]]);
        }
        // cout << i << ": " << flag << '\n';
        res += flag;
    }
    return res;
}

int sumup() {
    int res = 0;
    for (int i = 0; i < n; i++)
        res += P[i];
    cout << res << '\n';
}

bool solve(int cur) {
    // 到 i 為止已經處理好了

    // cout << "cur = " << cur << ": \n";
    // for (int i = 0; i < n; i++)
    //     cout << P[i] << ' ';
    // cout << '\n';

    int res = compute();
    if (res * 8 >= m * 7) {
        // cout << "solved!\n";
        // cout << "cur = " << cur << ": \n";
        // for (int i = 0; i < n; i++)
        //     cout << P[i] << ' ';
        // cout << '\n';
        return true;
    }
    if (cur == 0)
        return false;

    cur--;
    if (solve(cur)) {
        return true;
    };

    P[cur] = true;
    if (solve(cur))
        return true;
    // cout << "oh no!: " << cur << '\n';
    P[cur] = false;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    cin >> n;

    srand(rand());
    srand(rand());
    srand(37128973);

    cin >> m;
    C.resize(m, vector<int>(3));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < 3; j++)
            cin >> C[i][j];

    if (1) {
        for (int i = 0; i < n; i++)
            cout << ((rand() % 2) ? 1 : -1) << ' ';
    } else {
        solve(n);
        for (int i = 0; i < n; i++)
            cout << (P[i] ? 1 : -1) << ' ';
    }
}
