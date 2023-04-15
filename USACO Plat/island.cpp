#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
const int mxN = (int)5e1+3;

int n, m, CC;
string a[mxN];
int X[] = {1,-1,0,0};
int Y[] = {0,0,1,-1};
deque<pair<int,int>> Q;
int dp[1<<17][17], mv[17][17];
int dis[mxN][mxN], comp[mxN][mxN];

void bfs(){
    while(!Q.empty()){
        int i = Q[0].fi, j = Q[0].se; Q.pop_front();
        for(int k = 0; k < 4; k++){
            int ni = i+X[k], nj = j+Y[k];
            if(ni<0 or nj<0 or ni>=n or nj>=m) continue;
            if(a[ni][nj]!='X' and a[ni][nj]!='S') continue;
            if(dis[i][j]+(a[i][j]=='S')<dis[ni][nj]){
                dis[ni][nj]=dis[i][j]+(a[i][j]=='S');
                if(a[i][j]=='S') Q.push_back({ni,nj});
                else Q.push_front({ni,nj});
            }
        }
    }
}

void recur(int i, int j){
    if(i<0 or j<0 or i>=n or j>=m) return;
    if(comp[i][j] or a[i][j]!='X') return;
    comp[i][j]=CC;
    for(int k = 0; k < 4; k++) 
        recur(i+X[k],j+Y[k]);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("island.in");
    ofstream cout("island.out");
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(a[i][j]=='X' and !comp[i][j]) 
                CC++, recur(i,j);
    memset(mv,0x3f,sizeof(mv));
    for(int x = 1; x <= CC; x++){
        for(int y = 1; y <= CC; y++){
            memset(dis,0x3f,sizeof(dis));
            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                    if(a[i][j]=='X' and comp[i][j]==x)
                        dis[i][j] = 0, Q.push_back({i,j});
            int ans = 0x3f3f3f3f; bfs();
            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                    if(a[i][j]=='X' and comp[i][j]==y)
                        ans = min(ans, dis[i][j]);
            mv[x-1][y-1] = ans;
        }
    }
    memset(dp,0x3f,sizeof(dp));
    for(int i = 0; i < CC; i++) dp[(1<<i)][i]=0;
    for(int mask = 0; mask < (1<<CC); mask++){
        for(int i = 0; i < CC; i++){
            if(mask>>i&1){ int nmask = mask^(1<<i);
                for(int j = 0; j < CC; j++) if((nmask>>j)&1)  
                    dp[mask][i] = min(dp[mask][i], dp[nmask][j]+mv[j][i]);
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 0; i < CC; i++) ans = min(ans, dp[(1<<CC)-1][i]);
    cout << ans;
}
