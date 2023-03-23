/* 
Solved by myself
Say we pick a random X, then that X contributes as thus for each adjacent pair of numbers:
if(a[i]<a[i+1])
    if(a[i]<X and X<=a[i+1]) 
        add a[i+1] - X + 1;  // Better to use fav button, then forward button till a[i+1]
    else 
        add a[i+1] - a[i];   // Better to use only forward button till a[i+1]
else
    if(X<=a[i+1]) 
        add a[i+1] - X + 1;  // Better to use fav button, then forward button till a[i+1]
    else if(X>a[i]) 
        add m - X + a[i+1] + 1; // Better to use fav button, then forward button till a[i+1]
    else 
        add a[i+1] - a[i] + m; // Better to use only forward button till a[i+1]
}
We can calculate for all Xs quickly like this:
Line 8 and 15 conditions can be done with prefix sums logic at first
The remaining conditions can be done with range query data structures quickly
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = (int)1e5+10;
const int LINF = (int)1e18;
int n, m;
int a[maxn], ans[maxn];
int fenwick[2][maxn];
vector<int> v[maxn], w[maxn], W[maxn];

void update(int x, int v, int i){
    for(; x<maxn; x+=(x&-x)) fenwick[i][x]+=v;
}

int sum(int x, int i){
    int tot = 0;
    for(; x>0; x-=(x&-x)) 
        tot+=fenwick[i][x];
    return tot;
}

int query(int l, int r, int i){
    return sum(r,i)-sum(l-1,i);
}

void init(){
    for(int i = 1; i < maxn; i++)
        fenwick[0][i]=fenwick[1][i]=0;
}

int32_t main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> a[i];

    for(int i = 0; i < n-1; i++){
        if(a[i]<a[i+1]){
            // line 8
            ans[1]+=a[i+1]-a[i];
            ans[a[i]+1]-=a[i+1]-a[i];
            ans[a[i+1]+1]+=a[i+1]-a[i];
        }
        else{
            // line 15
            ans[a[i+1]+1]+=a[i+1]-a[i]+m;
            ans[a[i]+1]-=a[i+1]-a[i]+m;
        }
    }
    for(int i = 1; i <= m; i++) ans[i]+=ans[i-1]; // prefix sums logic

    for(int i = 0; i < n-1; i++){ // required to add pairs to the ds in some sorted order
        if(a[i]<a[i+1]) v[a[i]].push_back(a[i+1]);
        else w[a[i+1]].push_back(a[i]), W[a[i]].push_back(a[i+1]);
    }

    for(int x = 1; x <= m; x++){ // line 6
        ans[x]+=query(x,maxn-1,1)-(x-1)*query(x,maxn-1,0);
        for(auto u : v[x]) update(u,1,0), update(u,u,1);
    }
    init();

    for(int x = m; x >= 1; x--){ // line 11
        for(auto u : w[x]) update(x,1,0), update(x,x,1);
        ans[x]+=query(x,maxn-1,1)-(x-1)*query(x,maxn-1,0);
    }
    init();

    for(int x = 1; x <= m; x++){ // line 13
        ans[x]+=query(1,x-1,1)-(x-m-1)*query(1,x-1,0);
        for(auto u : W[x]) update(u,1,0), update(u,u,1);
    }

    cout << *min_element(ans+1, ans+m+1);
}