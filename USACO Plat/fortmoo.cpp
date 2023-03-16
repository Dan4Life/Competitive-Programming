#include <bits/stdc++.h>
using namespace std;

string a[210];
set<int> S[210];
set<pair<int,int>> SS[210];
int n, m, ans, pref[210][210], dp[210][210][210];

int main() {
    ifstream cin("fortmoo.in");
    ofstream cout("fortmoo.out");
	cin >> n >> m; memset(dp, -1, sizeof(dp));
	for(int i = 0; i < n; i++){
        cin >> a[i];
        for(int j = 0; j < m; j++) {
            if(a[i][j]=='X') { S[j].insert(i); continue; }
            S[j].insert(n), pref[i][j+1] = pref[i][j]+1;
            SS[j].insert({pref[i][j+1], i});
        }
    }
    for(int i = n-1; i >= 0; i--){
        for(int j = m-1; j >= 0; j--){
            if(a[i][j]=='X') continue;
            for(int k = 1; j+k<=m; k++){
                int l = j, r = j+k-1;
                if(a[i][r]=='X') continue;
                if(pref[i][r+1]<k) break;
                int mx_down = min(*S[l].lower_bound(i),*S[r].lower_bound(i))-1;
                if((mx_down-i+1)*k<=ans) continue;
                int cur = i-1, sum = 0, K = k;
                auto itr = SS[r].lower_bound({k,i});
                while(itr!=SS[r].end()){
                    int next = itr->second;
                    if(next>mx_down){
                        itr = SS[r].lower_bound({K+1, i});
                        if(itr!=SS[r].end())
                        {
                            K = itr->first;
                            itr = SS[r].lower_bound({K, i});
                            if(itr!=SS[r].end()) K = itr->first;
                        }
                        continue;
                    }
                    if(dp[next][r][k]!=-1){ sum = dp[next][r][k], cur=next-1; break; }
                    cur = next; itr++;
                }
                mx_down = min(mx_down, cur);
                dp[i][r][k]=(mx_down-i+1)*k+sum;
                ans = max(ans, dp[i][r][k]);
            }
        }
    }
    cout << ans;
}
