#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
using pii = pair<int,int>;
const int mxN = (int)5e2+2;
const int LINF = (int)1e8;
int n, w, h;
string a[mxN];
pii mov[5][mxN][mxN];
int X[] = {-1,0,1,0};
int Y[] = {0,1,0,-1};
bool vis[10][10][mxN][mxN];
int dp[10][10][mxN][mxN];
 
inline bool isValid(int x, int y){ return (x>=0 and x<h and y>=0 and y<w and a[x][y]!='x'); }
 
pii mv(int dir, int x,int y){
    while(isValid(x,y)){
        if(a[x][y]=='A') dir=(dir+3)%4;
        else if(a[x][y]=='C') dir=(dir+1)%4;
        if(!isValid(x+X[dir], y+Y[dir])) break;
        x+=X[dir], y+=Y[dir];
    }
    return mp(x,y);
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> w >> h; int ans = LINF;
    for(int i = 0; i < h; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 0; k <= h; k++)
                for(int l = 0; l <= w; l++)
                    dp[i][j][k][l]=LINF;   
    for(int k = 0; k < 4; k++)
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                mov[k][i][j] = mv(k,i,j);
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            if(a[i][j]>='0' and a[i][j]<='9')
                dp[a[i][j]-'0'][a[i][j]-'0'][i][j]=0;
    vector<pair<int,int>> q[mxN*mxN];
    for(int l = 1; l <= n; l++){
        for(int i=1,j=i+l-1;j<=n;i++,j++){
            for(int x = 0; x < h; x++){
                for(int y = 0; y < w; y++){
                    for(int k = i; k < j; k++)
                        dp[i][j][x][y] = min(dp[i][j][x][y], 
                            dp[i][k][x][y]+dp[k+1][j][x][y]);
                    if(dp[i][j][x][y]<LINF) q[dp[i][j][x][y]].pb({x,y});
                }
            }
            for(int _ = 0; _ < mxN*mxN; _++){
                for(auto [x,y] : q[_]){
                    if(vis[i][j][x][y]) continue; vis[i][j][x][y]=1;
                    for(int k = 0; k < 4; k++){
                        int nx = mov[k][x][y].fi, ny = mov[k][x][y].se;
                        if(dp[i][j][x][y]+1< dp[i][j][nx][ny]){
                            dp[i][j][nx][ny]=dp[i][j][x][y]+1;
                            q[dp[i][j][nx][ny]].pb({nx,ny});
                        }
                    }
                }
                q[_].clear();
            }
        }
    }
    for(int x = 0; x < h; x++)
        for(int y = 0; y < w; y++)
            ans = min(ans, dp[1][n][x][y]);
    cout << (ans==LINF?-1:ans);
}
