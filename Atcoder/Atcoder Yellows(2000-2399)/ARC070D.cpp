/*
Solved by myself
We can apply complementary counting here :D
For every element 'A_i', the element is NECESSARY if there is a subset without that element such that 
the subset sum 'x' satisfies this condition: k-A_i <= x < k.
Doing this naively is O(N^3), how to speedup?
We can apply dp for every prefix and suffix(dp1 and dp2) and use two pointers to speed it up as N,K<=5000
Now we can just find x using bruteforce for dp1 and dp2. We can also use binary search or bitmask speedup like in editorial
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn = (int)5e3+1;
int n, k;
int a[maxn];
bool dp[maxn][maxn], dp2[maxn][maxn];
vector<int> v[maxn];

void calc(bool dp[][maxn], bool ok){
    dp[0][0] = 1; if(ok) v[0].pb(0);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= k; j++){
            dp[i][j]|=dp[i-1][j];
            if(j-a[i]>=0 and dp[i-1][j-a[i]]) dp[i][j]=1; 
            if(dp[i][j] and ok) v[i].pb(j);
        }
    }
}

int32_t main(){
    cin >> n >> k; int ans = n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    calc(dp, 0); reverse(a+1, a+n+1);
    calc(dp2, 1); reverse(a+1, a+n+1);
    for(int i = 1; i <= n; i++){
        int sum = k, ptr = (int)v[n-i].size()-1;
        for(int j = 0; j < k; j++){
            if(!dp[i-1][j]) continue;
            if(sum<j or sum==k-a[i]) break;
            if(j>=k-a[i]) sum = min(sum,j);
            else{
                while(ptr>0 and v[n-i][ptr-1]>=k-a[i]-j) ptr--;
                if(ptr!=(int)v[n-i].size() 
                    and v[n-i][ptr]>=k-a[i]-j)
                        sum = min(sum, v[n-i][ptr]+j);
            }
        }
        ans-=(sum<k); //idk why i made sum to be as small as possible lol
    }
    cout << ans;
}
