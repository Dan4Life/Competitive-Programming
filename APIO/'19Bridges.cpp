#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define int long long
#define SZ(a) (int)a.size()
#define all(a) a.begin(),a.end()
 
const int B = 1200;
const int maxn = (int)1e5+10;
 
int n, m, q;
stack<int> st; bool ch[maxn]; 
int u[maxn], v[maxn], w[maxn];
int t[maxn], s[maxn], w2[maxn];
int p[maxn], sz[maxn], ans[maxn];
vector<int> edge[B], updE, fixE;
 
void rs(){ iota(p,p+n+1,0); fill(sz,sz+n+1,1); }
int findSet(int i) { return p[i]==i?i:findSet(p[i]); }
 
void unionSet(int a, int b){
	a=findSet(a), b=findSet(b);
	if(a==b) return;
	if(sz[a] < sz[b]) swap(a,b);
	sz[a]+=sz[b]; st.push(b); p[b]=a; 
}
 
void rollback(int Size){
	while(SZ(st)>Size){
		int x = st.top(); st.pop();
		sz[p[x]]-=sz[x], p[x]=x;
	}
}
 
int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; i++) cin >> u[i] >> v[i] >> w[i];
	cin >> q;
	for(int i = 1; i <= q; i++) cin >> t[i] >> s[i] >> w2[i];
 
	for(int l = 1; l <= q; l+=B){
		int r = min(q+1, l+B), j=0;
		fill(ch,ch+m+1,false); rs();
		updE.clear(); fixE.clear();
		for(int i = 0; i < B; i++) edge[i].clear();
 
		for(int i = l; i < r; i++)
			if(t[i]==1 and !ch[s[i]]) 
				updE.pb(i), ch[s[i]]=1;
		for(int i = 1; i <= m; i++) if(!ch[i]) fixE.pb(i);
 
		for(int i = l; i < r; i++){
			if(t[i]==1) w[s[i]]=w2[i];
			else for(auto j : updE) 
				if(w[s[j]]>=w2[i]) edge[i-l].pb(s[j]);
		}
		
		vector<int> ord(r-l,0); iota(all(ord),l);
		sort(all(fixE), [&](int i, int j){ return w[i]>w[j]; });
		sort(all(ord), [&](int i, int j){ return w2[i]>w2[j]; });
		
		for(auto i : ord){
			if(t[i]==1) continue;
			while(j<SZ(fixE) and w[fixE[j]]>=w2[i])
				unionSet(u[fixE[j]],v[fixE[j]]), j++;
			int pr = SZ(st);
			for(auto j : edge[i-l]) unionSet(u[j],v[j]); 
			ans[i] = sz[findSet(s[i])]; rollback(pr);
		}
	}
	for(int i = 1; i <= q; i++) if(t[i]==2) cout << ans[i] << "\n";
}
