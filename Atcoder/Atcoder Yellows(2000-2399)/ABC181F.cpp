/*
Solved with editorial
I mustn't have been the only one who thought something like sliding the circle pixel by pixel...
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 110;

int n;
int x[maxn], y[maxn], p[maxn];

int findSet(int i){return i==p[i]?i:p[i]=findSet(p[i]); }
bool isSameSet(int i, int j){ return findSet(i)==findSet(j); }

void unionSet(int i, int j){
    int x = findSet(i), y = findSet(j);
    if(x!=y) p[y]=x;
}

inline double dis(int i, int j){ return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]); }

bool chk(double r){
    for(int i = 0; i <= n+3; i++) p[i]=i;
    for(int i = 0; i < n; i++){
        x[n]=x[i],y[n]=100;
        x[n+1]=x[i],y[n+1]=-100;
        for(int j = i+1; j < n+2; j++)
            if(dis(i,j)<=r) unionSet(i,j);
    }
    return !isSameSet(n,n+1);
}

int32_t main()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
    
    double l = 0, r = 200*200;
    for(int itr = 0; itr < 300; itr++){
        double mid = (l+r)/2;
        if(chk(mid))l=mid;
        else r=mid;
    }
    cout << fixed << setprecision(4) << sqrt(l)/2;
}
