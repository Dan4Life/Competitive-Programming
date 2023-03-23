#include <bits/stdc++.h>
using namespace std;

int n, x, ans;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; priority_queue<int, vector<int>, greater<int>> S, SS;
    for(int i = 0; i < n; i++) cin >> x, S.push(x);
    for(int i = 0; i < n; i++) cin >> x, SS.push(x);
    while(!S.empty()){
        if(S.top()<=SS.top()) S.pop(), SS.pop();
        else{
            ans++;
            int x = S.top(), y = SS.top();
            S.pop(), SS.pop();
            S.push(y), SS.push(x);
        }
    }
    cout << ans;
}
