#include <stdio.h>
#include <ctype.h>
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

void WriteLL(long long int x){
    if (!x) putchar('0');
    else{
        char s[100];
        int i,j=0;
        if(x<0) putchar('-'), x = -x;
        for (;x>0;x/=10) s[j++]=x%10;
        for (i=j-1;i>=0;i--) putchar(s[i]+48);
    }
}

void ReadStr(char *str){
    char c;
    while(!isgraph(c = readchar()));
    
    // printf("c = %c\n", c);
    int cur = 0;
    str[cur++] = c;
    while(isgraph(c = readchar())){
        str[cur++] = c;
    }
}

void print_bin(int n)
{
    int l = sizeof(n)*8;//總位數。
    int i;
    if(n == 0)
    {
        putchar('0');
        return;
     }
    for(i = l-1; i >= 0; i --)//略去高位0.
    {
        if(n&(1<<i)) break;
    }
 
    for(;i>=0; i --)
        putchar(((n&(1<<i)) != 0 ) + '0');
}