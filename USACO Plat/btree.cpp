#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()

const int mxN = 40010;

bool vis[mxN];
int n, x, ans, sz;
vector<int> adj[mxN];
int a[mxN], sub[mxN];
int _mxpr[mxN*2], _mnpr[mxN*2];
int *mxpr = _mxpr+mxN, *mnpr = _mnpr+mxN;
struct Data{ int mx, mn, sm; } segTree[mxN*2], Init{0,0,0};

Data combine(Data &a, Data &b){
	Data c; c.sm = a.sm+b.sm;
	c.mx = max(a.mx,a.sm+b.mx);
	c.mn = min(a.mn,a.sm+b.mn);
	return c;
}

void upd(int i, int v, int p=0, int l=0, int r=n+5){
	if(l==r){ segTree[p]={max(0,v),min(0,v),v}; return; }
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	if(i<=mid) upd(i,v,p+1,l,mid);
	else upd(i,v,rp,mid+1,r);
	segTree[p] = combine(segTree[p+1],segTree[rp]);
}

Data query(int i, int j, int p=0, int l=0, int r=n+5){
	if(i>j or i>r or j<l) return Init;
	if(i<=l and r<=j) return segTree[p];
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	auto le = query(i,j,p+1,l,mid);
	auto ri = query(i,j,rp,mid+1,r);
	return combine(le,ri);
}

int fcentroid(int s, int p, int n){
	for(auto u : adj[s])
		if(!vis[u] and u!=p and sub[u]>n/2)
			return fcentroid(u,s,n);
	return s;
}

int calcSize(int s, int p){
	sub[s]=1;
	for(auto u : adj[s]){
		if(vis[u] or u==p) continue;
		sub[s]+=calcSize(u,s);
	}
	return sub[s];
}

void dfs1(int s, int p, int lev){
	upd(lev,a[s]);
	auto cur = query(0,sz);
	if(!cur.mn){
		int mx = cur.mx, sm = cur.sm;
		if(mxpr[-sm]!=-1 and sm+mxpr[-sm]>=0)
			ans = max({ans, mx, sm+mxpr[-sm]});
	}
	for(auto u : adj[s])
		if(!vis[u] and u!=p) 
			dfs1(u,s,lev-1);
	upd(lev,0);
}

void dfs2(int s, int p, int mx=0, int mn=0, int sum=0){ 
	mxpr[sum]=max(mxpr[sum],mx); 
	mnpr[sum]=min(mnpr[sum],mn);
	for(auto u : adj[s]){
		if(vis[u] or u==p) continue; 
		int nsm = sum+a[u]; 
		dfs2(u,s,max(mx,nsm),min(mn,nsm),nsm);
	}
}

void ctroid_dec(int s, int p){
	sz = calcSize(s,p);
	int ctroid = fcentroid(s,p,sz); vis[ctroid]=1;
	for(int _ = 0; _ < 2; _++){
		for(int i = 0; i <= sz; i++) upd(i,0);
		for(int i = -sz; i <= sz; i++) mxpr[i]=-1,mnpr[i]=0;
		upd(sz,a[ctroid]); mxpr[0]=mnpr[0]=0;
		for(auto u : adj[ctroid]){
			if(vis[u] or u==p) continue;
			dfs1(u,ctroid,sz-1);
			dfs2(u,ctroid,max(0,a[u]),min(0,a[u]),a[u]);
		}
		reverse(all(adj[ctroid]));
	}
	for(auto u : adj[ctroid])
		if(!vis[u] and u!=p) 
			ctroid_dec(u,ctroid);
}

int32_t main() {
	ifstream cin("btree.in"); ofstream cout("btree.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for(int i = 2; i <= n; i++)
		cin >> x, adj[x].pb(i), adj[i].pb(x);
	for(int i = 1; i <= n; i++){
		char c; cin >> c; a[i]=(c=='('?1:-1);
	}
	ctroid_dec(1,-1); cout << ans;
}
