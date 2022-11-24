#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

class Tower {
    // indexed from 1.
    vector<int> dangos;
    vector<ll> preSum;
    int top, size;
    unordered_map<int, bool> eaten;

   public:
    Tower(int M) : top(0), size(0) {
        dangos.resize(M);
        preSum.resize(M);
        dangos[0] = preSum[0] = 0;
    };

    void put(int w);
    ll take();
    ll CC(int x, int k);
    ll DD(int x);

    void print();
};

void suicide() {
    system("PAUSE");
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int M;
    cin >> M;

    string oper;
    Tower T(M);
    while (M--) {
        cin >> oper;
        switch (oper[0]) {
            case 'P': {
                int w;
                cin >> w;
                T.put(w);
                break;
            }
            case 'T': {
                cout << T.take() << '\n';
                break;
            }
            case 'C': {
                int x, k;
                cin >> x >> k;
                cout << T.CC(x, k) << '\n';
                break;
            }
            case 'D': {
                int x;
                cin >> x;
                cout << T.DD(x) << '\n';
                break;
            }
            default:
                cout << "operation error!\n";
                suicide();
        }
    }
}

void Tower::put(int w) {
    dangos[++top] = w;
    preSum[top] = preSum[top - 1] + w;
    ++size;
}

ll Tower::take() {
    if (size == 0) {
        cout << "Take error!\n";
        suicide();
        return -1;
    }

    --size;
    return dangos[top--];
}

ll Tower::CC(int x, int k) {
    if (size < x) {
        cout << "CC error!\n";
        suicide();
        return 0;
    }

    int b = ceil((double)x / k);

    // Eat and compute sum of largest b number;

    // copy last x element
    int Arr[x], sorted_Arr[x];

    copy(
        dangos.begin() + top - x + 1,
        dangos.begin() + top + 1,
        Arr);

    for (auto &x : Arr) {
        eaten[x] = false;
    }

    copy(Arr, Arr + x, sorted_Arr);
    sort(sorted_Arr, sorted_Arr + x, greater<int>());

    ll res = 0;
    for (auto it = sorted_Arr; it != sorted_Arr + b; it++) {
        res += *it;
        eaten[*it] = true;
    }

    for (int i = 0, pos = top - x + 1; i < x; i++) {
        if (!eaten[Arr[i]]) {
            // cout << "Arr[i] = " << Arr[i] << '\n';
            dangos[pos] = Arr[i];
            preSum[pos] = preSum[pos - 1] + dangos[pos];
            pos++;
        }
    }

    size -= b;
    top -= b;

    // print();

    return res;
}

ll Tower::DD(int x) {
    if (size < x) {
        cout << "DD error!\n";
        suicide();
        return -1;
    }

    // top - x + 1 ~ top
    // preSum[i] = sum of 1~i
    // => preSum[top] - preSum[top - x]
    return preSum[top] - preSum[top - x];
}

void Tower::print() {
    assert(top == size);

    cout << "Current tower:\n";
    for (int i = 1; i <= top; i++) {
        cout << dangos[i] << ' ';
    }
    cout << '\n';
}