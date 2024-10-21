#include <bits/stdc++.h>
using namespace std;
int n, m, x,  pre[55][55], dp[55][55][55][55];
 
int getsum(int a, int b, int c, int d){
    a++,b++,c++,d++;
    return pre[c][d]-pre[c][b-1]-pre[a-1][d]+pre[a-1][b-1];
}
 
int recur(int x1, int y1, int x2, int y2)
{
    if(x1==x2 and y1==y2) return dp[x1][y1][x2][y2]=0;
    if(dp[x1][y1][x2][y2]!=-1) return dp[x1][y1][x2][y2];
    int ans = (int)1e9;
    for(int x = x1; x < x2; x++)
        ans = min(ans, recur(x1, y1, x, y2)+recur(x+1,y1,x2,y2)+getsum(x1,y1,x2,y2));
    for(int y = y1; y < y2; y++)
        ans = min(ans, recur(x1, y1, x2, y)+recur(x1,y+1,x2,y2)+getsum(x1,y1,x2,y2));
    return dp[x1][y1][x2][y2]=ans;
}
 
int32_t main()
{
    cin >> n >> m; memset(dp, -1, sizeof(dp));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> x; pre[i+1][j+1]+=pre[i+1][j]+pre[i][j+1]-pre[i][j]+x;
        }
    }
    cout << recur(0,0,n-1,m-1);
}
