#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()
using ll = long long;
const int mxN = (int)5e2+2;
bool used[mxN*mxN*2];
int n, m, k, x; ll ans = 0;
int a[mxN][mxN], p[mxN*mxN];
int sz[mxN*mxN], nodeSz[mxN*mxN];
int X[] = {1,-1,0,0}, Y[] = {0,0,1,-1};

vector<pair<int,int>> stv;
vector<tuple<int,int,int>> edges;

inline int node(int i, int j){return i*m+j;}

int findSet(int i){return i==p[i]?i:p[i]=findSet(p[i]);}

bool isSameSet(int i, int j){return findSet(i)==findSet(j);}

bool unionSet(int i, int j){
	int x = findSet(i), y = findSet(j);
	if(x==y) return false;
	if(sz[x]<sz[y]) swap(x,y);
	p[y]=x; sz[x]+=sz[y]; 
	nodeSz[x]+=nodeSz[y]; 
	return true;
}

int findSize(int i, int sz[]) {return sz[findSet(i)];}

inline bool isValid(int i, int j){
	return i>=0 and i<n and j>=0 and j<m;
}

int32_t main() {
	ifstream cin("skilevel.in");
	ofstream cout("skilevel.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 0; i < mxN*mxN; i++) p[i]=i, sz[i]=1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> x; nodeSz[node(i,j)]=x; 
			if(x) stv.pb({i,j});
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < 4; k++){
				int x = i+X[k], y = j+Y[k];
				int A = node(i,j), B = node(x,y);
				if(!isValid(x,y)) continue;
				edges.pb(make_tuple(abs(a[i][j]-a[x][y]),A,B));
			}
		}
	}
	sort(all(edges), [&](tuple<int,int,int> a, tuple<int,int,int> b){
		return get<0>(a)<get<0>(b);
	});
	if(k==1){cout<<0;return 0;}
	for(auto u : edges){
		int a = get<1>(u), b = get<2>(u), w = get<0>(u);
		unionSet(a, b); if(findSize(a,sz)<k) continue;
		ans+=(ll)findSize(a,nodeSz)*w, nodeSz[findSet(a)]=0;
	}
	cout << ans;
}
