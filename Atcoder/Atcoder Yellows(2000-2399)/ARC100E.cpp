/*
Solved with help (https://cp-algorithms.com/algebra/all-submasks.html#enumerating-all-submasks-of-a-given-mask)
The crux of the problem is finding out how to enumerate all submasks quickly. (New technique learnt)
Turns out it's standard and can be done in O(3^n)
Also this is different from editorial but way slower in comparison.
My editorial solution in O(N*2^N) is commented below
*/

#include <bits/stdc++.h>
using namespace std;
int n, a[1<<18];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; int ans = 0;
    for(int i = 0; i < (1<<n); i++) cin >> a[i];
    for (int m=1; m<(1<<n); m++){
        int x=-1, y=-1;
        for (int s=m; ; s=(s-1)&m){ //The two loops run in amortized complexity: O(3^n)
            if(x<y) swap(x,y);
            if(x==-1) x=a[s];
            else if(y==-1) y=a[s];
            else if(x>=a[s] and a[s]>=y) y=a[s];
            else if(x<=a[s]) y=x, x=a[s];
            if(s==0) break;
        }
        ans = max(ans,x+y); cout << ans << "\n"; 
    }
}

/*
#include <bits/stdc++.h>
using namespace std;
int n, a[1<<18];
multiset<int> S[1<<18];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; int ans = 0;
    for(int i = 0; i < (1<<n); i++) cin >> a[i], S[i].insert(a[i]);
    
    for(int i = 0; i < n; i++){
        for(int m = 0; m < (1<<n); m++){

            if((m>>i)&1) continue;
            int x = m|(1<<i);
            for(auto u : S[m]) S[x].insert(u);
            while((int)S[x].size()>2) S[x].erase(S[x].begin());


            //Alternatively You can do this instead
            if((m>>i)&1){
                int x = m^(1<<i);
                for(auto u : S[x]) S[m].insert(u);
                while((int)S[m].size()>2) S[m].erase(S[m].begin());
            }
        }
    }
    
    for(int m = 1; m < (1<<n); m++)
        ans = max(ans, *prev(S[m].end())+*prev(prev(S[m].end()))),
        cout << ans << "\n";
}
*/