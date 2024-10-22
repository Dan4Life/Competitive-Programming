#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define int long long
#define pb push_back
#define sz(a) (int)a.size()
using pii = pair<int,int>;
const int mxN = (int)1e6+10;
const int LINF = (int)1e18;

int n, A, B, C;
int pre[mxN], a[mxN], dp[mxN];

double g(int i, int j){
    int y1 = pre[i]*(A*pre[i]-B)+dp[i]; swap(i,j);
    int y2 = pre[i]*(A*pre[i]-B)+dp[i]; swap(i,j);
    int x1 = 2*A*pre[i]; swap(i,j);
    int x2 = 2*A*pre[i]; swap(i,j);
    y1-=y2,x1-=x2;
    return (double)(y1*1.0/x1*1.0);
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> A >> B >> C; int ans = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], pre[i]=pre[i-1]+a[i];
    for(int i = 1; i <= n; i++) dp[i] = -LINF;
    deque<int> dq; dq.clear(); dq.push_back(0);
    for(int i = 1; i <= n; i++){
        while(sz(dq)>1 and g(dq[0],dq[1])<=pre[i]) dq.pop_front(); int x = dq[0];
        dp[i] = max(dp[i],dp[x]+A*(pre[i]-pre[x])*(pre[i]-pre[x])+B*(pre[i]-pre[x])+C);
        while(sz(dq)>1 and g(end(dq)[-2],end(dq)[-1])>=g(end(dq)[-2],i)) dq.pop_back(); 
        dq.push_back(i);
    }
    cout << dp[n] << "\n";
}
