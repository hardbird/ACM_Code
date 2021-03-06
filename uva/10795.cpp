#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn=60+10;

int n, start[maxn], finish[maxn];

LL f(int * P, int i, int final)
{
    if(i==0)return 0;
    if(P[i]==final)return f(P, i-1, final);
    return f(P, i-1, 6-P[i]-final)+(1LL<<(i-1));
}

int main()
{
    int kase=0;
    while(~scanf("%d", &n) && n)
    {
        for(int i=1; i<=n; i++)
            scanf("%d", start+i);
        for(int i=1; i<=n; i++)
            scanf("%d", finish+i);
        int k=n;
        while(k>=1 && start[k]==finish[k])k--;
        LL ans=0;
        if(k>=1)
        {
            int other=6-start[k]-finish[k];
            ans=f(start, k-1, other)+f(finish, k-1, other)+1;
        }
        printf("Case %d: %lld\n", ++kase, ans);
    }
    return 0;
}
