/*
Solved with editorial
Solution is genius!
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN = (int)5e2+10;
string a[mxN];
char grid[2][mxN][mxN];

int main() {
	int n, m; cin >> n >> m;
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < 2; k++){
				if(a[i][j]=='#') grid[k][i][j]='#';
				else{
					grid[k][i][j] = '.';
					if(!k and (!j or (i%2 and j!=m-1))) grid[k][i][j] = '#';
					if(k and grid[k^1][i][j]=='.') grid[k][i][j] = '#';
				}
			}
		}
	}
	for(int i = 0; i < 2; i++,cout<<"\n")
		for(int j = 0; j < n; j++,cout<<"\n")
			for(int k = 0; k < m; k++)
				cout << grid[i][j][k];
}
