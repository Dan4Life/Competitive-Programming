/*
Solved by myself
Instead of the long dp solution from editorial, we can root at the node with the smallest p value
Then using priority queue, for current node with p value = x, 
it can be proven that it's always better to update the neighbours of that node(that aren't yet updated) to x+1
I tried doing it just by increasing node p value order but I keep getting RTE for some reason...
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define se second
const int maxn = (int)2e5+10;
int n, k;
int a[maxn];
vector<int> adj[maxn];

int32_t main(){
    cin >> n; memset(a,-1,sizeof(a));
    for(int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }
    cin >> k;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    for(int i = 0; i < k; i++){
        int x, y; cin >> x >> y; a[x]=y;
        pq.push({a[x],x});
    }
    while(!pq.empty()){
        int curx = pq.top().se; pq.pop();
        for(auto u : adj[curx]){
            if(a[u]==-1){
                a[u]=a[curx]+1;
                pq.push({a[u],u});
            } 
            else if(abs(a[curx]-a[u])!=1){
                cout << "No\n"; return 0;
            }
        }
    }
    cout << "Yes\n";
    for(int i = 1; i <= n; i++) cout << a[i] << "\n";
}
