/*
Solved with help (editorial)
*/

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxn = (int)7e2+10;

int n, m;
vector<int> v;
int col[maxn];
set<int> adj[maxn];
vector<pair<int,int>> w;
bool dp[maxn][maxn/2][2];

bool isBipartite(int s){
    v.pb(s);
    for(auto u : adj[s]){
        if(col[u]==-1){
            col[u] = !col[s];
            if(!isBipartite(u)) 
                return false; 
        }
        else if(col[u]==col[s]) 
            return false;
    }
    return true;
}

int32_t main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i!=j) adj[i].insert(j);
  
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].erase(b), adj[b].erase(a);
    }
  
    fill(col, col+n+1, -1);
    for(int i = 1; i <= n; i++){
        if(col[i]!=-1) continue; 
        v.clear(); int cnt = 0; col[i]=0;
        if(!isBipartite(i)){ cout<<-1; return 0; }
        for(auto u : v) cnt+=col[u];
        w.pb({cnt,(int)v.size()-cnt});
    }
  
    m = (int)w.size(); dp[0][0][0] = true;
    for(int i = 1; i <= m; i++){
        for(int j = 0; j <= n/2; j++){
            int a = w[i-1].first, b = w[i-1].second;
            for(int k = 0; k < 2; k++){
                if(k and j>=a) 
                    dp[i][j][k]|=dp[i-1][j-a][k],
                    dp[i][j][k]|=dp[i-1][j-a][k^1];
                else if(!k and j>=b)
                    dp[i][j][k]|=dp[i-1][j-b][k],
                    dp[i][j][k]|=dp[i-1][j-b][k^1];
            }
        }
    }
  
    for(int i = n/2; i >= 0; i--){
        if(dp[m][i][0] or dp[m][i][1]){
            cout << i*(i-1)/2 + (n-i)*(n-i-1)/2;
            return 0;
        }
    }
}