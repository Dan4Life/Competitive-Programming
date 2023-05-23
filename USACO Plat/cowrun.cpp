#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)1e3+10;
int n, lf, a[mxN], dp[mxN][mxN][2];

int recur(int i, int j, int k){
	int *ans = &dp[i][j][k];
	if(*ans!=-1) return *ans;
	*ans = mxN*mxN*mxN;
	if(i==0 and j==1) return *ans=n*abs(a[lf]);
	if(i==1 and j==0) return *ans=n*abs(a[lf-1]);
	int cPos = (k?a[lf+j-1]:a[lf-i]);
	if(i and !k){
		*ans = min(*ans, recur(i-1,j,0)+(n-i-j+1)*abs(a[lf-i+1]-cPos));
		*ans = min(*ans, recur(i-1,j,1)+(n-i-j+1)*abs(a[lf+j-1]-cPos));
	}
	if(j and k){
		*ans = min(*ans, recur(i,j-1,0)+(n-i-j+1)*abs(a[lf-i]-cPos));
		*ans = min(*ans, recur(i,j-1,1)+(n-i-j+1)*abs(a[lf+j-2]-cPos));
	}
	return *ans;
}

int32_t main() {
	ifstream cin("cowrun.in");
	ofstream cout("cowrun.out");
	cin >> n; memset(dp,-1,sizeof(dp));
	for(int i = 0; i < n; i++) cin >> a[i], lf+=(a[i]<0);
	sort(a,a+n); cout << min(recur(lf,n-lf,0),recur(lf,n-lf,1));
}
