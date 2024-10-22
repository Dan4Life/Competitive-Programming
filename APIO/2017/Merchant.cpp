#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 105, K=1005;
int n, m, kk, u, v, w;
int b[N][K], s[N][K], p[N][N], d[2][N][N];
 
void floydWarshall(int d[][N]){
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
}
 
int32_t main(){
    cin >> n >> m >> kk;
    memset(d,63,sizeof(d));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= kk; j++) 
            cin >> b[i][j] >> s[i][j];
    for(int i = 0; i < m; i++)
        cin>>u>>v>>w,d[0][u][v]=w;
    floydWarshall(d[0]);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= kk; k++)
                if(min(b[i][k],s[j][k])>=0) 
                    p[i][j]=max(p[i][j],s[j][k]-b[i][k]);
    int l = 0, r = 1e9;
    while(l<r){
        int mid = (l+r+1)/2, ok=0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[1][i][j]=-p[i][j]+mid*
                    min((int)1e18/mid,d[0][i][j]);
        floydWarshall(d[1]);
        for(int i = 1; i <= n;i++) 
            if(d[1][i][i]<=0) ok=1;
        if(ok) l=mid;
        else r=mid-1;
    }
    cout << l;
}
