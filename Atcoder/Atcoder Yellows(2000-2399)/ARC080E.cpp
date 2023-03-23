/*
Solved with help (mostly by myself, except the toposort part :/)
Basically we can solve the problem greedily in reverse
When we greedily find the smallest pairs of integers using segment tree like this:
Lets denote the optimal pair as {f,s} for current range {l,r}, then:
f = index with smallest a_i such that the parity of that index is same as l
s = index with smallest a_i > f such that the parity of that index is same as r(or different from f)
The data on segtree should the min value and its position in a range for odd and even indexes
Now we can 'walk on segment tree' to get both f and s in o(log N) (or binsearch in o(logN*logN))
We need to efficiently find the smallest odd(or even depending on l) index such that the array is cut into at most three parts
The next pair has to be among the three parts(and as small as possible)
The mistake I made was just sorting based on how deep each pair is...
But the toposort idea comes from the following fact:
We know that for two pairs {a,b} and {c,d} such that {c,d} is inside one of the three parts formed by {a,b}, then:
We must pick {a,c} before {a,c}. That is the ONLY constraint.
So knowing this, we can simulate minimum toposort using khan's algorithm
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pi pair<int,int>
#define fi first
#define se second
const int maxn = (int)2e5+10;

int n;
int a[maxn];
tuple<int,int,int,int> b[maxn];
priority_queue<pi, vector<pi>, greater<pi>> pq;

struct Data{
    int mn[2], ind[2];
} segTree[maxn*4];

Data combine(Data &a, Data &b){
    Data c;
    for(int i = 0; i < 2; i++){
        if(a.mn[i]<b.mn[i]) c.mn[i]=a.mn[i],c.ind[i]=a.ind[i];
        else c.mn[i]=b.mn[i],c.ind[i]=b.ind[i];
    }
    return c;
}

void update(int i, int v, int p=1, int l=1, int r=n){
    if(l==r){
        int j = i%2, k = (i+1)%2;
        segTree[p].mn[j]=v;
        segTree[p].mn[k]=maxn;
        segTree[p].ind[j]=i;
        segTree[p].ind[k]=-1;
        return;
    }
    int mid = (l+r)/2;
    if(i<=mid) update(i,v,p*2,l,mid);
    else update(i,v,p*2+1,mid+1,r);
    segTree[p] = combine(segTree[p*2], segTree[p*2+1]);
}

int query(int i, int j, int k, int p=1, int l=1, int r=n){
    if(i>j or r<i or l>j) return -1;
    if(i<=l and r<=j) return segTree[p].ind[k];
    int mid = (l+r)/2;
    int left = query(i,j,k,p*2,l,mid);
    int right = query(i,j,k,p*2+1,mid+1,r);
    if(left==-1) return right;
    if(right==-1) return left;
    if(a[left]<a[right]) return left;
    return right;
}

void solve(int l, int r){
    if(l>r) return;
    int f = query(l,r-1,l%2);
    int s = query(f+1,r,r%2);
    update(f,maxn); update(s,maxn);
    pq.push({a[f],a[s]}); b[a[f]] = make_tuple(l,r,f,s);
}

int32_t main(){
    cin >> n;
    for(int i = 1; i <= n; i++) 
        cin >> a[i], update(i,a[i]);

    solve(1,n);
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        int l = get<0>(b[cur.fi]);
        int r = get<1>(b[cur.fi]);
        int f = get<2>(b[cur.fi]);
        int s = get<3>(b[cur.fi]);
        cout << a[f] << " " << a[s] << " ";
        solve(l,f-1); solve(f+1,s-1); solve(s+1,r); 
    }
}