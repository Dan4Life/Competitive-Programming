#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5+10;
int n, a[N], p[N], vis[N];
 
bool chk(int m, int A[], int X[], int Y[], int P[], int Q[]){
    for(int i = 0; i < n; i++) a[i] = A[i];
    for(int i = 0; i < m; i++) swap(a[X[i]],a[Y[i]]), P[i]=Q[i]=0;
    for(int i = 0; i < n; i++) p[a[i]]=i, vis[i]=0;
    vector<array<int,2>> v; v.clear();
    for(int i = 0; i < n; i++){
        if(vis[i] or i==a[i]) continue; int j = i;
        while(!vis[j]){
            if(!vis[a[j]]) v.push_back({j,a[j]}); 
            vis[j] = 1; j=a[j];
        }
    }
    if(v.size()>m) return 0;
    for(int i = 0; i < n; i++) a[i]=A[i], p[a[i]]=i;
    for(int i = 0; i < m; i++){
        swap(a[X[i]],a[Y[i]]), swap(p[a[X[i]]],p[a[Y[i]]]);
        if(i<v.size()){
            P[i] = p[v[i][0]], Q[i] = p[v[i][1]]; 
            swap(a[P[i]],a[Q[i]]), swap(p[a[P[i]]],p[a[Q[i]]]);
        }
    }
    return 1;
}
 
int findSwapPairs(int N, int A[], int m, int X[], int Y[], int P[], int Q[]) {
    n = N; int l = 0, r = m;
    while(l<r){
        int mid = (l+r)/2;
        if(chk(mid,A,X,Y,P,Q)) r=mid;
        else l=mid+1;
    }
    chk(l,A,X,Y,P,Q); return l;
}
