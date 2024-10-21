#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
 
struct grade
{
    int points, num, id;
};
 
bool cmp(grade a, grade b)
{
    if(a.points!=b.points) return a.points>b.points;
    if(a.num!=b.num) return a.num>b.num;
    return a.id<b.id;
}
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, t, p;
    cin >> n >> t >> p;
    grade person[2005];
    vector<int> V(t, 0);
    vector< vector<int> > VV;
    for(int i = 0; i < n; i++)
    {
        vector<int> v;
        for(int j = 0; j < t; j++)
        {
            int a; cin >> a; v.pb(a);
        }
        int cnt=0;
        for(auto u : v) cnt+=u;
        for(int j = 0; j < v.size(); j++)
            V[j]+=(v[j]==0);
        person[i].id=i+1;
        person[i].num=cnt;
        person[i].points=0;
        VV.pb(v); v.clear();
    }
    for(int i = 0; i < VV.size(); i++)
        for(int j = 0; j < VV[i].size(); j++)
            if(VV[i][j]==1) person[i].points += V[j];
    sort(person, person+n, cmp);
    for(int i = 0; i < n; i++)
        if(person[i].id==p)
            cout << person[i].points << " " << i+1 << "\n";
}
