#include "traffic.h"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
//#define int ll
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define all(a) a.begin(), a.end()
 
const int maxn = 1000010;
const ll MOD = 1e9+7;
const int INF = 1e9;
const ll LINF = 1e18;
ll n, m, a[maxn], b[maxn];
//map<int, int> M, N;
string s, ss;
//set<int> S;
ll dis = LINF, ind = -1;
vector<int> adj[maxn];
ll subtree[maxn], ppl[maxn], fans = 0;
 
void dfs(int s, int p=-1)
{
    for(auto u : adj[s])
    {
        if(u==p)continue;
        dfs(u,s);
        subtree[s]+=subtree[u];
        ppl[s] = max(ppl[s], subtree[u]);
    }
    ppl[s] = max(ppl[s], fans-subtree[s]-a[s]);
    subtree[s]+=a[s];
}
 
int LocateCentre(int N, int pp[], int S[], int D[])
{
    int i;
    for(int i = 0; i < maxn; i++)subtree[i]=0, ppl[i]=0;
    for(i = 0; i < N; i++) a[i]=pp[i], fans+=pp[i];
    for(i = 0; i < N-1; i++) adj[S[i]].pb(D[i]), adj[D[i]].pb(S[i]);
    dfs(0);
    for(i = 0; i < N; i++)
        if(dis>ppl[i])dis=ppl[i],ind=i;
    return ind;
}
