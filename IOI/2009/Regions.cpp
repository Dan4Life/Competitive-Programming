#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
bool vis[25001];
int n,r,q,cnt=1, a[maxn], st[maxn], en[maxn], B[maxn];
unordered_map<int,int> calc[25001];
vector<int> adj[maxn], v[25001];
void dfs(int s, int p = -1)
{
    st[s] = cnt++;
    for(auto u : adj[s])
        if(u!=p) dfs(u,s);
    en[s] = cnt-1;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> r >> q >> a[1];
    for(int i = 2; i <= n; i++)
    {
        int x; cin >> x >> a[i];
        adj[x].push_back(i);
    }
    int K = sqrt(n);
    dfs(1); for(int i = 1; i <= n; i++) B[st[i]]=i;
    for(int i = 1; i <= n; i++) v[a[B[i]]].push_back(st[B[i]]);
    for(int i = 1; i <= n; i++)
    {
        if(vis[a[B[i]]]) continue;
        if(v[a[B[i]]].size()<=K) continue;
        vis[a[B[i]]]=true;
        int pref[n+2]{0};
        for(auto u : v[a[B[i]]])
        {
            int l = st[B[u]], r = en[B[u]];
            pref[l]++, pref[r+1]--;
        }
        for(int j = 1; j <= n; j++)
            pref[j]+=pref[j-1], calc[a[B[j]]][a[B[i]]]+=pref[j];
    }
    while(q--)
    {
        int a, b, ans = 0; cin >> a >> b;
        if(v[a].size()<=K){
            for(auto u : v[a]){
                int l = st[B[u]], r = en[B[u]];
                auto itr = upper_bound(v[b].begin(), v[b].end(), r)-v[b].begin();
                auto itr2 = upper_bound(v[b].begin(), v[b].end(), l)-v[b].begin();
                if(itr) itr--, ans+=max((int)(itr-itr2)+1, 0);
            }
        }
        else ans = calc[b][a];
        cout << ans << endl;
    }
}
