#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

void suicide() {
    system("PAUSE");
}

vector<int> dangos;
vector<ll> preSum;
int top, cur_size;
unordered_map<int, bool> eaten;

vector<pair<int, int>> Arr;

void init(int M) {
    top = cur_size = 0;

    dangos.resize(M);
    preSum.resize(M);
    dangos[0] = preSum[0] = 0;
};
void put(int w) {
    dangos[++top] = w;
    preSum[top] = preSum[top - 1] + w;
    ++cur_size;
}
ll take() {
    if (cur_size == 0) {
        cout << "Take error!\n";
        suicide();
        return -1;
    }

    --cur_size;
    return dangos[top--];
}

ll CC(int x, int k) {
    if (cur_size < x) {
        cout << "CC error!\n";
        suicide();
        return 0;
    }

    int b = ceil((double)x / k);

    // Eat and compute sum of largest b number;

    // copy last x element
    vector<pair<int, int>> Arr;

    for (int i = top - x + 1; i <= top; i++) {
        Arr.push_back(pair<int, int>(i, dangos[i]));
    }

    sort(Arr.begin(), Arr.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    ll res = 0;
    for (int i = 0; i < b; i++) {
        res += Arr.back().second;
        Arr.pop_back();
    }

    sort(Arr.begin(), Arr.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.first < b.first;
    });

    for (int i = 0, pos = top - x + 1; i < x - b; i++, pos++) {
        dangos[pos] = Arr[i].second;
        preSum[pos] = preSum[pos - 1] + dangos[pos];
    }

    cur_size -= b;
    top -= b;

    // print();

    Arr.clear();

    return res;
}

ll DD(int x) {
    if (cur_size < x) {
        cout << "DD error!\n";
        suicide();
        return -1;
    }

    // top - x + 1 ~ top
    // preSum[i] = sum of 1~i
    // => preSum[top] - preSum[top - x]
    return preSum[top] - preSum[top - x];
}

void print() {
    assert(top == cur_size);

    cout << "Current tower:\n";
    for (int i = 1; i <= top; i++) {
        cout << dangos[i] << ' ';
    }
    cout << '\n';
}

#include <cctype>
int hasEOF = 0;
int readchar() {
    static int N = 1 << 20;
    static char buf[1 << 20];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;
        }
        p = buf;
    }
    return *p++;
}

int ReadInt(int *x) {
    char c, neg;
    while ((c = readchar()) != '-' && !isdigit(c)) {
        if (c == EOF) return 0;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c - '0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c - '0';
    *x *= neg;
    return 1;
}

void WriteInt(int x) {
    if (!x)
        putchar('0');
    else {
        char s[100];
        int i, j = 0;
        if (x < 0) putchar('-'), x = -x;
        for (; x > 0; x /= 10) s[j++] = x % 10;
        for (i = j - 1; i >= 0; i--) putchar(s[i] + 48);
    }
}

void WriteLL(long long int x) {
    if (!x)
        putchar('0');
    else {
        char s[100];
        int i, j = 0;
        if (x < 0) putchar('-'), x = -x;
        for (; x > 0; x /= 10) s[j++] = x % 10;
        for (i = j - 1; i >= 0; i--) putchar(s[i] + 48);
    }
}

int main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int M;
    ReadInt(&M);

    char oper;

    init(M);
    while (oper != EOF) {
        oper = readchar();
        switch (oper) {
            case 'P': {
                // putchar(oper);
                int w;
                ReadInt(&w);
                // WriteInt(w);
                // continue;
                put(w);
                break;
            }
            case 'T': {
                // putchar(oper);
                WriteLL(take());
                putchar('\n');
                break;
            }
            case 'C': {
                int x, k;
                // putchar(oper);
                ReadInt(&x), ReadInt(&k);
                WriteLL(CC(x, k));
                putchar('\n');
                break;
            }
            case 'D': {
                int x;
                // putchar(oper);
                ReadInt(&x);
                WriteLL(DD(x));
                putchar('\n');
                break;
            }
            default:
                continue;
        }
    }
}
