#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(a) a.begin(),a.end()

const int mxN = (int)5e2+10;
const int LINF = (int)1e9;

char z[mxN];
int n, V, W, mx, area=LINF;
int g[mxN][mxN], h[mxN][mxN];
unordered_map<int,int> indv, indw;
int x[mxN], y[mxN], origv[mxN], origw[mxN];

int32_t main() {
	ifstream cin("cowrect.in"); ofstream cout("cowrect.out");
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; vector<int> v, w;
	for(int i = 0; i < n; i++){
		cin >> x[i] >> y[i] >> z[i];
		v.pb(x[i]), w.pb(y[i]);
	}
	sort(all(v)), sort(all(w));
	v.erase(unique(all(v)),end(v));
	w.erase(unique(all(w)),end(w));
	for(auto u : v) indv[u]=V++,origv[V-1]=u;
	for(auto u : w) indw[u]=W++,origw[W-1]=u;
	for(int i = 0; i < n; i++){
		x[i]=indv[x[i]],y[i]=indw[y[i]];
		if(z[i]=='H') h[y[i]][x[i]]++;
		else g[y[i]][x[i]]++;
	}
	for(int i = 0; i < W; i++)
		for(int j = 1; j < V; j++)
			g[i][j]+=g[i][j-1], h[i][j]+=h[i][j-1];
	for(int i = 0; i < V; i++){
		for(int j = i; j < V; j++){
			int y = 0, sum = 0, mxsum = 0;
			int firstY=-1, lastY=-1, mnarea = LINF;
			for(int y = 0; y <= W; y++){
				if(g[y][j]-(i?g[y][i-1]:0)>=1 or y==W){
					int curArea = (origw[lastY]-origw[firstY])*(origv[j]-origv[i]);
					if(mxsum<sum) mxsum=sum,mnarea=curArea;
					else if(mxsum==sum) mnarea = min(mnarea, curArea);
					sum = 0; firstY=lastY=-1;
				}
				else{
					sum += h[y][j]-(i?h[y][i-1]:0);
					if(h[y][j]-(i?h[y][i-1]:0)){
						lastY = y;
						if(firstY==-1)firstY=y;
					}
				}
			}
			if(mxsum>mx)mx=mxsum,area=mnarea;
			else if(mxsum==mx)area=min(area,mnarea);
		}
	}
	cout << mx << "\n" << area << "\n";
}
