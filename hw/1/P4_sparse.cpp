#include <bits/stdc++.h>

using namespace std;

#define MAX_L 20
#define MAX_N 500000
int sparse_table[MAX_M][MAX_L];

void build(int N, int A[], int sparse_table[][MAX_L], int l, int myLog[], int myPow[])
{
    // T[i][j] stores min(st: T[i], size: 2^j)
    // 2^l >= N, so j = 0~l
    for (int i = 0; i < N; i++)
        sparse_table[i][0] = A[i];
    for (int j = 1; j <= l; j++)
    {
        int size = myPow[j];

        for (int i = 0; i + size - 1 < N; i++)
        {
            // ends if i + myPow[j] - 1 >= N

            // Cur = A[i, i + myPow[j] - 1]
            // size = myPow[j]
            // L = A[i, i + myPow[j - 1] - 1] (left half)
            // R = A[st, i + myPow[j] - 1] (right half)
            // i + myPow[j] - 1 - st = myPow[j - 1] - 1  =>  st = i + myPow[j] - myPow[j - 1]
            int lmin = sparse_table[i][j - 1], rmin = sparse_table[i + size - myPow[j - 1]][j - 1];

            // Then min(Cur) = min(min(L), min(R))
            sparse_table[i][j] = min(lmin, rmin);
        }
    }
}

void build(int N, int A[], int sparse_table[][MAX_L], int l, int myLog[], int myPow[])
{
    // T[i][j] stores min(st: T[i], size: 2^j)
    // 2^l >= N, so j = 0~l
    for (int i = 0; i < N; i++)
        sparse_table[i][0] = A[i];
    for (int j = 1; j <= l; j++)
    {
        int size = myPow[j];

        for (int i = 0; i + size - 1 < N; i++)
        {
            // ends if i + myPow[j] - 1 >= N

            // Cur = A[i, i + myPow[j] - 1]
            // size = myPow[j]
            // L = A[i, i + myPow[j - 1] - 1] (left half)
            // R = A[st, i + myPow[j] - 1] (right half)
            // i + myPow[j] - 1 - st = myPow[j - 1] - 1  =>  st = i + myPow[j] - myPow[j - 1]
            int lmin = sparse_table[i][j - 1], rmin = sparse_table[i + size - myPow[j - 1]][j - 1];

            // Then min(Cur) = min(min(L), min(R))
            sparse_table[i][j] = min(lmin, rmin);
        }
    }
}

int solve(int n, int A[], int l, int r)
{
    if (l >= r)
        return 0;

    // O(n)
    int *min_index = min_element(A + l, A + r + 1);

    int res = 0, mid = min_index - A, mi = *min_index;

    // T(n - m) + T(m)
    // Not necessarily 2T(n/2)
    res += solve(n, A, l, mid - 1) + solve(n, A, mid + 1, r);

    // O(n)
    map<int, int> Hash;
    for (int i = l; i <= r; i++)
    {
        if (i == mid)
            continue;
        res += A[mid] == A[i] - A[mid];
    }

    // O(n)
    for (int i = l; i < mid; i++)
        Hash[A[i] - mi]++, Hash[A[i] + mi]++;
    for (int i = mid + 1; i <= r; i++)
        res += Hash[A[i]];
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N;
    cin >> N;
    int A[N];
    for (auto &i : A)
        cin >> i;

    int myLog[N + 1]; // stores ceil(log_2(N))
    for (int b = 1, i = 1, l = 0; i <= N; l += b == i, b *= (b == i) ? 2 : 1, i++)
        myLog[i] = l;

    int myPow[myLog[N] + 1];
    for (int b = 1, i = 0; b < 2 * N; b *= 2, i++)
        myPow[i] = b;

    int l = myLog[N];
    build(N, A, sparse_table, l, myLog, myPow);

    int res = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
        {
            // find the max size s.t. size <= r - l + 1
            // i.e. find j s.t. myPow[j] <= r - l + 1  =>  j <= floor(log(r - l + 1))
            // but myLog is ceil, hence need to take floor

            int size = j - i + 1, curBase, curMin = 0;
            curBase = myLog[size];
            curBase -= myPow[curBase] > size;

            // // L = [l, l + myPow[j] - 1], R = [st, r];
            // // r - st = myPow[j] - 1  =>  st = r - myPow[j] + 1
            if (myPow[curBase] == size)
                curMin = sparse_table[i][curBase];
            else
            {
                int lmin = sparse_table[i][curBase], rmin = sparse_table[j - myPow[curBase] + 1][curBase];
                curMin = min(lmin, rmin);
            }

            res += abs(A[i] - A[j]) == curMin;
        }
    cout << res << '\n';
}

/*
g++ P4_sparse.cpp -o P4_sparse
Get-Content text | .\P4_sparse > out
*/