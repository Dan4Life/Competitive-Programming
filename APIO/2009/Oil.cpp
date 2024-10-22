#include <bits/stdc++.h>
using namespace std;
const int N = 1502;
int n, m, k, mx[N], sf[N], pr2[N];
int a[N][N], b[N][N], pr[N][N];

void rotate(){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			b[i][j] = a[i][j];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			a[i][j] = b[j][m-i-1];
	swap(n,m);
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k; int ans=0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];
	for(int _ : {0,1,2,3}){
		memset(pr,0,sizeof(pr)), memset(pr2,0,sizeof(pr2));
		memset(mx,0,sizeof(mx)), memset(sf,0,sizeof(sf));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				pr[i+1][j+1] = pr[i][j+1]+
					pr[i+1][j]-pr[i][j]+a[i][j];
		n-=k, m-=k;
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= m; j++)
				b[i][j] = pr[i+k][j+k]-
					pr[i][j+k]-pr[i+k][j]+pr[i][j];
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= m; j++)
				mx[i]=max(mx[i],b[i][j]);
		memset(pr,0,sizeof(pr)); int ind = 0;
		for(int i = n; i >= 0; i--) sf[i]=max(sf[i+1],mx[i]);
		for(int i = 0; i <= n; i++) pr2[i]=max(i?pr2[i-1]:0,mx[i]);
		for(int i = k; i <= n; i++){
			while(ind<=i-k){
				pr[0][0]=max(pr[0][0],b[ind][0]);
				pr[m][1]=max(pr[m][1],b[ind][m]);
				for(int j = 1; j <= m; j++)
					pr[j][0]=max({pr[j-1][0], pr[j][0], b[ind][j]});
				for(int j = m-1; j >= 0; j--)
					pr[j][1]=max({pr[j+1][1], pr[j][1], b[ind][j]});
				ind++;
			}
			for(int j = k; j <= m; j++)
				ans = max(ans, pr[j-k][0]+pr[j][1]+sf[i]);
			for(int j = i-k; j>=k; j--){
			    pr[j][3]=max(j==i-k?0:pr[j+1][3],mx[j]);
				ans = max(ans, pr2[j-k]+pr[j][3]+sf[i]);
			}
		}
		n+=k, m+=k; rotate();
	}
	cout << ans << "\n";
}
