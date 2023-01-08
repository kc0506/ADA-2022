#include <bits/stdc++.h>

#include "ypglpk.hpp"

using namespace std;

typedef long long int ll;

struct edge {
    int from, to, w;
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    // ypglpk::set_output(true);

    int N, M;
    cin >> N >> M;

    vector<edge> E(M);
    for (int i = 0; i < M; i++) {
        auto &e = E[i];
        cin >> e.from >> e.to >> e.w;
    }

    const int T = 1, S = N;

    // A: M -> N
    // 1. >= 0; 2. <= 1; 3. in + out <= 0; 4. in + out >= 0
    vector<vector<double>> A;
    vector<vector<double>> A1(N + 1, vector<double>(M + N + 1, 0));  // for once
    vector<vector<double>> A2(N + 1, vector<double>(M + N + 1, 0));  // for in+out <= 0
    vector<vector<double>> A3(N + 1, vector<double>(M + N + 1, 0));  // for in+out >= 0
    vector<vector<double>> A4(M, vector<double>(M + N + 1, 0));      // MTZ

    for (int i = 0; i < M; i++) {
        // 每個點經過一次*
        A1[E[i].to][i] = 1;

        // 入出度之和
        A2[E[i].to][i] = 1;
        A2[E[i].from][i] = -1;
        A3[E[i].to][i] = -1;
        A3[E[i].from][i] = 1;

        // MTZ
        A4[i][i] = N;
        A4[i][M + E[i].from] = 1;
        A4[i][M + E[i].to] = -1;
    }

    A.insert(A.end(), A1.begin(), A1.end());
    A.insert(A.end(), A2.begin(), A2.end());
    A.insert(A.end(), A3.begin(), A3.end());
    A.insert(A.end(), A4.begin(), A4.end());

    // B: 3N
    vector<double> B;
    vector<double> B1((N + 1), 1);
    vector<double> B2((N + 1), 0);
    vector<double> B3((N + 1), 0);
    vector<double> B4(M, N - 1);

    B1[1] = 0;
    
    B2[T] = -1;
    B2[S] = 1;

    B3[T] = 1;
    B3[S] = -1;

    B.insert(B.end(), B1.begin(), B1.end());
    B.insert(B.end(), B2.begin(), B2.end());
    B.insert(B.end(), B3.begin(), B3.end());
    B.insert(B.end(), B4.begin(), B4.end());

    // cout << "B:\n";
    // for (auto &x : B)
    //     cout << x << '\n';

    // return 0;

    // C: w * x
    vector<double> C(M + 1 + N, 0);
    for (int i = 0; i < M; i++)
        C[i] = E[i].w;

    vector<int> varType(M + 1 + N, GLP_IV);
    for (int i = 0; i < M; i++)
        varType[i] = GLP_BV;

    pair<double, std::vector<double>> SOLUTION = ypglpk::mixed_integer_linear_programming(
        A, B, C, varType);
    if (SOLUTION.second.empty()) {
        cout << -1;
    } else {
        cout << (long long int)SOLUTION.first << '\n';
        for (int i = 0; i < M; i++) {
            cout << !!(SOLUTION.second[i]);
        }
    }
}
