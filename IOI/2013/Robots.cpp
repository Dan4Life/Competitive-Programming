#include "robots.h"
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
const int mxN = (int)5e4+10;
pair<int,int> toy[1000010];
int n, m, t, x[mxN], y[mxN];
 
bool chk(int tim){
    priority_queue<int> pq;
    while(sz(pq))pq.pop(); int j=0;
    for(int i = 0; i < n; i++){
        while(j<t and toy[j].fi<x[i])
            pq.push(toy[j++].se);
        int xd = tim;
        while(xd-- and sz(pq)) pq.pop();
    }
    while(j<t) pq.push(toy[j++].se);
    for(int i = m-1; i >= 0; i--){
        int xd = tim;
        while(xd-- and sz(pq)){
            if(pq.top()>=y[i]) return 0;
            pq.pop();
        }
    }
    return !sz(pq);
}
 
int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    n = A, m = B, t = T;
    for(int i = 0; i < n; i++) x[i] = X[i];
    for(int i = 0; i < m; i++) y[i] = Y[i];
    for(int i = 0; i < t; i++) toy[i] = {W[i],S[i]};
    sort(x,x+n), sort(y,y+m); sort(toy,toy+t);
    int l = 0, r = t+1;
    while(l<r){
        int mid = (l+r)/2;
        if(chk(mid)) r=mid;
        else l=mid+1;
    }
    return l==t+1?-1:l;
}
