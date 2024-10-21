#include <bits/stdc++.h>
using namespace std;
#define int long long
 
int32_t main()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n+5, 0);
    int a[1000];
    for(int i = 0; i < n; i++) cin >> a[i];
    map<int,int> M;
    for(int i = 0; i < m; i++) cin >> M[i+1];
    queue<int> Q;
    int cnt = 0, ans = 0;
    for(int i = 0; i < 2*m; i++)
    {
        int x; cin >> x;
        if(x>0)
        {
            if(cnt==n) Q.push(x);
            else{
                cnt++;
                for(int j = 0; j < n; j++)
                {
                    if(v[j]) continue;
                    v[j]=x, ans+=a[j]*M[x];
                    break;
                }
            }
        }
        else{
            x*=-1;
            for(int j = 0; j < n; j++)
            {
                if(v[j]!=x) continue;
                v[j]=0, cnt--;
                if(!Q.empty()){
                    int z = Q.front(); Q.pop();
                    v[j]=z, ans+=a[j]*M[z], cnt++;
                }
            }
        }
    }
    cout << ans;
}
