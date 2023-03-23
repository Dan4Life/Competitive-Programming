#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back

const int maxn = (int)1e6+10;

int col[maxn];
int n, m, t, ok=1;
vector<int> stor[2];
string a[maxn], b[maxn];
vector<pair<char,int>> v; 
vector<pair<int,int>> adj[maxn];

bool chk(){
    for(int i = 0; i < n; i++) 
        if(a[i]!=b[i]) return false;
    return true;
}

void revrow(int x){
    reverse(a[x].begin(),a[x].end());
    reverse(a[n-x-1].begin(),a[n-x-1].end());
}

void revcol(int x){
    for(int i = 0; i < n/2; i++) swap(a[i][x], a[n-i-1][x]);
    for(int i = 0; i < n/2; i++) swap(a[i][m-x-1], a[n-i-1][m-x-1]);
}

void dfs(int s){
    stor[col[s]].pb(s);
    for(auto x : adj[s]){
        if(col[x.fi]==-1) col[x.fi]=col[s]^x.se, dfs(x.fi);
        else if(col[x.fi]!=col[s]^x.se) ok=0;
    }
}

void ae(int a, int b, int c){
    adj[a].pb({b,c}); adj[b].pb({a,c});    
}

int main()
{
    cin >> n >> m >> t; memset(col,-1,sizeof(col));
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < m/2; j++){
            string x = ""; 
            x+=a[i][j], x+=a[i][m-j-1];
            x+=a[n-i-1][j], x+=a[n-i-1][m-j-1];
            string y = ""; 
            y+=b[i][j], y+=b[i][m-j-1];
            y+=b[n-i-1][j], y+=b[n-i-1][m-j-1];
            
            bool A = x==y;
            swap(x[0],x[1]), swap(x[2],x[3]);
            bool B = x==y;
            swap(x[0],x[1]), swap(x[2],x[3]);
            swap(x[0],x[2]), swap(x[1],x[3]);
            bool C = x==y;
            swap(x[0],x[1]), swap(x[2],x[3]);
            bool D = x==y;
            int cnt = A+B+C+D;
            v.clear();
            
            if(cnt==0) ok=0;
            else if(cnt==1) ae(0,i+1,B|D), ae(0,n+j+1,C|D);
            else if(cnt==2){
                if(A==D) ae(i+1,n+j+1,!A);
                else{
                    if(A) ae(0,C?i+1:n+j+1,0);
                    if(D) ae(0,B?i+1:n+j+1,1);
                }
            }
        }
    }
    
    for(int i = 0; i <= n+m; i++){
        if(col[i]!=-1) continue;
        stor[0].clear(), stor[1].clear(); 
        col[i]=0; dfs(i);
        if((int)stor[0].size() < (int)stor[1].size()) 
            if(i) swap(stor[0],stor[1]);
        for(auto u : stor[1]){
            if(u<=n) v.pb({'R',u}), revrow(u-1);
            else v.pb({'C',u-n}), revcol(u-n-1);
        }
    }
    
    if(!chk() or !ok) {cout<<-1;return 0;}
    cout << (int)v.size() << "\n";
    for(auto u:v) cout << u.fi << " " << u.se << "\n";
}
