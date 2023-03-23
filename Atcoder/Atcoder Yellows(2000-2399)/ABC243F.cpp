/*
Solved by myself
Same as editorial
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, ans=0;
int a[2010];
int dp[100010][8];

int sqrtt(int x){
    int y = sqrt(x); y++;
    if(y*y<=x) return y; y--;
    if(y*y<=x) return y; return y-1;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; cin >> t;
    while(t--){
        cin >> n; ans = 0;
        int y = sqrtt(n);
        int yy = sqrtt(y);
        
        for(int i = 1; i <= 100000; i++)
            for(int j = 0; j < 8; j++) 
                dp[i][j] = 0;
        
        for(int i = yy; i >= 1; i--){
            dp[i][1] += dp[i+1][1];
            if(i==1) dp[i][1] += y-1;
            else dp[i][1] += y-i*i+1;
        }
        ans = 1+dp[1][1]-dp[2][1];
        for(int i = yy; i>=1; i--){
            for(int j = 2; j <= 6; j++){
                dp[i][j] += dp[i+1][j];
                int k = max(i*i,2ll);
                if(k<=yy) dp[i][j]+=dp[k][j-1]; 
                if(i==1) ans+=dp[i][j]-dp[i+1][j];
            }
        }
        cout << ans << "\n";
    }
}
