/*
Solved with editorial
There is almost 0 chance i could have gotten this myself wtf 

UPD: Actually I understand the problem now(after thinking about it for a few more minutes and thanks to https://codeforces.com/blog/entry/93165?#comment-831761).
Take a look at it from this perspective: (Read the official editorial first)
The problem is basically: 
"Given a permutation that has two parts of lengths N and M. 
You are only allowed to swap elements in different parts. 
Calculate the min number of swaps needed to sort or show its impossible."

First, ignore the constraint that you can only swap from two parts.
Now its a really standard problem that can be done with graph theory:
Basically, let's make a graph such that i->p[i] for each i in 1 to n+m
First off, we dont need self loops, since they are already fixed correctly, so we can ignore them.
If you notice, the graph is actually a functional graph. Therefore, its going to be a rooted DAG + an extra edge going out from the root.
But if you notice again, the DAG is actually going to be a straight line since the array is a permutation
(Because each node has EXACTLY 1 outgoing edge to a UNIQUE number)
The extra edge goes from the root to the leaf of the line therefore each component is nothing but a loop(or cycle or ring))
Basically, now you have just a couple of rings and you want to make n components such that i->i for each i at the end.
If you notice, given a loop of length n, the min number of swaps needed to sort is n-1 (use recursion starting with base case n=2).
Do that for each component, and you get N+M-K (N+M is the total number of nodes, K is the number of loops (or CCs with sizes >=2))

Now, back to the original problem. Add the constraints back to this standard problem.
When we swap, we basically either increase or reduce the number of CCs by 1, so we want to make sure there are N+M CCs by the end.
But the constraint forces us to swap only with components that have at least 1 element each from both part else we would be making "illegal" swaps.
This implies we must first connect all the components that have only 1 part to each other. We can call these CCs "pure".
Let the number of these components be R and B for each part of the permutation respectively.
Assuming R>=B(can be switched if not), we can connect all the B CCs to random 'R' pure CCs using B moves (somewhat like perfect matching).
Notice now, there are just R-B pure red CCs. We can connect all of them together, then connect to any of the other CCs(as they are all unpure now) in R-B moves.
This makes a total of B+R-B moves = R moves = max(R,B).
So we have n+m-k+max(R,B) moves.
But notice now, since we connected all the pure components, K reduces by max(R,B).
So its now: n+m-(k-max(R,B))+max(R,B) = N+M-K+max(R,B)+max(R,B) = N+M-K + 2*max(R,B) □

This problem was really nice, but it was so unapproachable initially due to skill issue :P
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn=(int)2e5+10;

int a[maxn];
bool vis[maxn];
vector<int> adj[maxn];
int n, m, r, b, ans, ok; 

void dfs(int s, int type=3){
    vis[s]=1;
    for(auto u : adj[s]){
        if(type!=3){
            if(!type and u>n) ok=0;
            if(type and u<=n) ok=0;
        }
        if(!vis[u]) dfs(u,type);
    }
}

int main()
{
    cin >> n >> m; ans = n+m;
    for(int i = 1; i <= n+m; i++) cin >> a[i];
    for(int i = 1; i <= n+m; i++)
        adj[i].push_back(a[i]);
    for(int i = 1; i <= n+m; i++)
        if(!vis[i]) ans--, dfs(i);
    fill(vis, vis+maxn,0);
    for(int i = 1; i <= n+m; i++){
        if(vis[i]) continue; 
        ok=1; dfs(i,(i>n));
        if(a[i]==i or !ok) continue;
        if(i<=n) r++; 
        else b++;
    }
    cout << ans+2*max(r,b);
}
