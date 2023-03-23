#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define fi first
#define se second
 
using pii = pair<int,int>;
using ll = long long;
 
const int maxn = (int)1e6+10;
const int LINF = (int)1e18;
int n, s, t, ans;
ll a[maxn], dis[maxn];
bool vis[maxn];
vector<pair<int,int>> adj[maxn];
 
void ae(int a, int b, int c){
    adj[a].pb({b,c});
}
 
void dijkstra(){
    for(int i = 1; i <= n; i++) dis[i] = LINF;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,s}); dis[s] = 0;
    while(!pq.empty()){
        int a = pq.top().se; pq.pop();
        if(vis[a]) continue; vis[a]=1;
        for(auto u : adj[a]){
            int b = u.fi, w = u.se;
            if(dis[b]>dis[a]+w){
                dis[b]=dis[a]+w;
                pq.push({dis[b], b});
            }
        }
    }
    cout << dis[t];
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> s >> t; int sum = 0;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) if(i!=t) ae(i,t,abs(t-i)*a[i]); 
    
    stack<pair<int,int>> st;
    for(int i = 1; i <= n; i++){
        while(!st.empty() and st.top().fi > a[i]) st.pop();
        if(!st.empty()) ae(i,st.top().se,abs(i-st.top().se)*a[i]);
        st.push({a[i],i});
    }
    while(!st.empty()) st.pop();
    for(int i = n; i >= 1; i--){
        while(!st.empty() and st.top().fi > a[i]) st.pop();
        if(!st.empty()) ae(i,st.top().se,abs(i-st.top().se)*a[i]);
        st.push({a[i],i});
    }
    dijkstra();
}
