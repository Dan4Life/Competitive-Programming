#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int mxN = (int)1e6+2;

template<int SZ>
struct Trie{
	int trie[26][SZ], jmp[20][SZ];
	int cur, IND, sz[SZ];
	char letter[SZ];
	vector<int> v;
	
	void init(){ cur=0; IND=0; v.clear(); memset(jmp,0,sizeof(jmp)); }
	
	void add(char x){
		int c = x-'a';
		if(!trie[c][cur]) trie[c][cur]=++IND;
		int p = cur; cur = trie[c][cur];
		sz[cur] = sz[p]+1; v.pb(cur);
		jmp[0][cur] = p; letter[cur] = x; 
		for(int j = 1; j < 20; j++)
			jmp[j][cur] = jmp[j-1][jmp[j-1][cur]];
	}
	
	void undo(int num){ v.pb(end(v)[-num-1]); cur = v.back(); }
	
	char get(int x){
		int xd = sz[cur]-x, lol = cur;
		for(int i = 0; i < 20; i++)
			if(xd>>i&1) lol=jmp[i][lol];
		return letter[lol];
	}
};

Trie<mxN> trie;

void Init(){ trie.init(); };

void TypeLetter(char L){ trie.add(L); };

void UndoCommands(int U){ trie.undo(U); };

char GetLetter(int P){ return trie.get(P+1); };

// Remove main() before submitting
int main(){
	Init();
	TypeLetter('a');
	TypeLetter('b');
	TypeLetter('c');
	TypeLetter('d');
	TypeLetter('e');
	cout << GetLetter(0) << "\n";
	UndoCommands(3);
	cout << GetLetter(1) << "\n";
	TypeLetter('x');
	TypeLetter('y');
	TypeLetter('z');
	cout << GetLetter(0) << "\n";
	cout << GetLetter(1) << "\n";
	cout << GetLetter(2) << "\n";
	cout << GetLetter(3) << "\n";
	cout << GetLetter(4) << "\n";
}
