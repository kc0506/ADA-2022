#include <bits/stdc++.h>
#include <cctype>
int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;   
        }
        p = buf;
    }
    return *p++;
}

int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

void WriteInt(int x){
    if (!x) putchar('0');
    else{
        char s[100];
        int i,j=0;
        if(x<0) putchar('-'), x = -x;
        for (;x>0;x/=10) s[j++]=x%10;
        for (i=j-1;i>=0;i--) putchar(s[i]+48);
    }
}

using namespace std;

map<int, int> myLog;

int store[100100];
int compute(int n){
    if(n == 1)
        return 1;
    if(myLog.count(n))
        return n + 2 * n * myLog[n];
    if(store[n])
        return store[n];

    int res = 0;
    res += compute(n / 2);
    res += 2 * n;
    res += compute(n - n / 2);
    return store[n] = res;
}

int recur(int n, stack<int> &tower, stack<int> &top_half, stack<int> &bot_half){
    // 將最頂端 n 個元素以題目要求方式倒放
    // 例：recur(4): (1, 2, 3, 4) -> (2, 1, 3, 4) -> (3, 4, 2, 1) -> (4, 3, 2, 1)
    if(n == 1){
        cout << "PHOTO\n";    
        return 0;
    }

    int half = n / 2, res = 0;
    res += recur(half, tower, top_half, bot_half);

    res += 2 * n;
    for(int i=0; i < half; i++){
        cout << "POP\n";
        top_half.push(tower.top());
        tower.pop();
    }
    for(int i=0; i < n - half; i++){
        cout << "POP\n";
        bot_half.push(tower.top());
        tower.pop();
    }

    for(int i=0; i < half; i++){
        cout << "PLACE " << top_half.top() << "\n";
        tower.push(top_half.top());
        top_half.pop();
    }
    for(int i=0; i < n - half; i++){
        cout << "PLACE " << bot_half.top() << "\n";
        tower.push(bot_half.top());
        bot_half.pop(); 
    }
    assert(top_half.empty());
    assert(bot_half.empty());

    res += recur(n - half, tower, top_half, bot_half);

    return res;
}


void recur_optimal(int n, vector<int> &tower){
    // 將最頂端 n 個元素以題目要求方式倒放
    // 例：recur(4): (1, 2, 3, 4) -> (2, 1, 3, 4) -> (3, 4, 2, 1) -> (4, 3, 2, 1)
    if(n == 1){
        puts("PHOTO");
        return;
    }

    int half = n / 2;
    recur_optimal(half, tower);

    for(int i=0; i<n; i++)
        puts("POP");

    // 先印上面，再印下面，最後交換
    vector<int> top(half), bot(n - half);
    copy(tower.begin(), tower.begin() + half, top.begin());
    copy(tower.begin() + half, tower.begin() + n, bot.begin());
    // reverse(bot.begin(), bot.end());

    // printf("tower:\n");
    // for(auto i: tower)
    //     printf("%d ", i);
    // printf("\n");
    // printf("top:\n");
    // for(auto i: top)
    //     printf("%d ", i);
    // printf("\n");
    // printf("bot:\n");
    // for(auto i: bot)
    //     printf("%d ", i);
    // printf("\n");

    copy(bot.begin(), bot.end(), tower.begin());
    copy(top.begin(), top.end(), tower.begin() + n - half);
    for(auto i: top){
        fputs("PLACE ", stdout);
        WriteInt(i);
        putchar('\n');
    }
    for(auto i = bot.rbegin(); i != bot.rend(); i++){
        fputs("PLACE ", stdout);
        WriteInt(*i);
        putchar('\n');
    }

    recur_optimal(n - half, tower);
}


int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    for(int i=0, d=1; i<18; i++){
        myLog[d] = i;
        d *= 2;
    }

    // Normal ver.
    // int N;
    // stack<int> tower, top_half, bot_half;
    // cin >> N;
    // cout << compute(N) + N << '\n';

    // for(int i = N; i >= 1; i--){
    //     tower.push(i);
    //     cout << "PLACE " << i << '\n';
    // }
    // recur(N, tower, top_half, bot_half);

    // Optimal ver.
    int N;
    ReadInt(&N);
    vector<int> tower(N, 0);
    WriteInt(compute(N) + N);
    putchar('\n');

    for(int i = N; i >= 1; i--){
        tower[i - 1] = i;
        fputs("PLACE ", stdout);
        WriteInt(i);
        putchar('\n');
    }
    // return 0;

    recur_optimal(N, tower);
}
