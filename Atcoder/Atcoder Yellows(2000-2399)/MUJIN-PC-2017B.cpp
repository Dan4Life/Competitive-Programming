/*
Solved by myself (just 1 tiny bug)
Same as editorial
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)5e2+10; 

int n;
string a[maxn];
int cnt[maxn], cnt2[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; 
    int ans = 2*n+2, x = 0; bool ok = 0;
    for(int i = 0; i < n; i++) cin >> a[i];
 
    for(int i = 0; i < n; i++){
        int cnt = 0;
        for(int j = 0; j < n; j++)
            cnt+=(a[j][i]=='#');
        x+=(cnt!=n); ok|=!!cnt;
    }
    if(!ok){cout<<-1;return 0;}

    for(int i = 0; i < n; i++){
        int sum = 0, xx=0;
        for(int j = 0; j < n; j++){
            if(a[i][j]=='#') continue;
            int cnt = 0;
            for(int k = 0; k < n; k++)
                if(a[k][i]=='#') cnt=1;
            sum++; if(!cnt) xx=1;
        }
        ans = min(ans, sum+xx);
    }
    cout << ans+x;
}