#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 510;
const int INF = 0x3f3f3f3f;
int nx,ny; //两边的点数
int g[N][N]; //二分图描述
int linker[N],lx[N],ly[N]; //y中各点匹配状态， x,y中的点标号
int slack[N];
bool visx[N],visy[N];
bool DFS(int x)
{
    visx[x] = true;
    for(int y = 0; y < ny; y++)
    {
        if(visy[y]) continue;
        int tmp = lx[x] + ly[y] - g[x][y];
        if(tmp == 0)
        {
            visy[y] = true;
            if(linker[y] == -1 || DFS(linker[y]))
            {
                linker[y] = x;
                return true;
            }
        }
        else if(slack[y] > tmp)
            slack[y] = tmp;
    }
    return false;
}
int KM()
{
    memset(linker, -1, sizeof(linker));
    memset(ly,0, sizeof(ly));
    for(int i = 0; i < nx; i++)
    {
        lx[i] = -INF;
        for(int j = 0; j < ny; j++)
            if(g[i][j] > lx[i])
                lx[i] = g[i][j];
    }
    for(int x = 0; x < nx; x++)
    {
        for(int i = 0; i < ny; i++)
            slack[i] = INF;
        while(true)
        {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(DFS(x)) break;
            int d = INF;
            for(int i = 0; i < ny; i++)
                if(!visy[i] && d > slack[i])
                    d = slack[i];
            for(int i = 0; i < nx; i++)
                if(visx[i])
                    lx[i] -= d;
            for(int i = 0; i < ny; i++)
            {
                if(visy[i])ly[i] += d;
                else slack[i] -= d;
            }
        }
    }
    int res = 0;
    for(int i = 0; i < ny; i++)
        if(linker[i] != -1)
            res += g[linker[i]][i];
    return res;
}

int main()
{
    int n;
    while(scanf("%d",&n) == 1)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d",&g[i][j]);
        nx = ny = n;
        KM();
        int ans=0;
        for(int i=0; i<n; i++)
        {
            ans+=lx[i];
            printf("%d%c", lx[i], i<n-1?' ':'\n');
        }
        for(int i=0; i<n; i++)
        {
            ans+=ly[i];
            printf("%d%c", ly[i], i<n-1?' ':'\n');
        }
        printf("%d\n", ans);
    }
    return 0;
}
