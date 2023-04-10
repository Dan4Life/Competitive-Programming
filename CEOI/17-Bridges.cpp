#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mxN = (int)1e5+10;
const int mxC = (int)1e6+10;
const int LINF = (int)1e12+10;
int n, m, x, h[mxN], w[mxN], dp[mxN];

struct Line{
	int m, c;
	Line(){ m=c=LINF; }
	Line(int _m, int _c){ m = _m, c = _c;}
	int operator()(int x){ return m*x+c; }
} seg[2*mxC+10];

void addLine(Line a, int p=0, int l=1, int r=mxC){
	if(l==r){
		if(seg[p](l)>a(l)) seg[p]=a;
		return;
	}
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	if(a.m > seg[p].m) swap(a,seg[p]);
	if(a(mid) < seg[p](mid))
		swap(a,seg[p]), addLine(a,p+1,l,mid);
	else addLine(a,rp,mid+1,r);
}

int query(int x, int p=0, int l=1, int r=mxC){
	if(l==r) return seg[p](x);
	int mid = (l+r)>>1; int rp = p+2*(mid-l+1);
	if(x<=mid) return min(query(x,p+1,l,mid),seg[p](x));
	return min(query(x,rp,mid+1,r),seg[p](x));
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; 
    for(int i = 1; i <= n; i++) cin >> h[i];
    for(int i = 1; i <= n; i++) cin >> w[i];
	dp[1] = -w[1];
	for(int i = 1; i <= n; i++){
		if(i>1)dp[i] = query(h[i])+h[i]*h[i]-w[i];
		addLine({-2*h[i],dp[i]+h[i]*h[i]});
	}
	cout << accumulate(w+1,w+n+1,0ll)+dp[n];
}
