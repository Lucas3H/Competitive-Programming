/*
	Essa estrutura de dados faz a mesma coisa que a Segtree. Mas aqui, o problema a ser resolvido é 
	o seguinte: dado um Array v e um intervalo [l, r], quantos elementos distintos há nesse intervalo.
	Todas as queries são feita em O((N + Q)*sqrt(N)). Não pode ser usada quando há update.
*/

struct MO{
	typedef long long ll;

	ll sz, n, q, l, r,  ans;
	ll v[100100], freq[1000100];

	struct qry{
		int l, r, ind;
		bool operator < (const qry& x) const{
			if (l/sz == x.l/sz) return (r < x.r);
			return l < x.l;
		}
	};
	qry qq[200100];


	void add(ll val){
		freq[val] ++;
		if(freq[val] == 1) ans++;
	}

	void remove(ll val){
		freq[val]--;
		if(freq[val] == 0) ans--;
	}

	ll query(int x,int y){
		while(r < y) add(v[++r]);
		while(l > x) add (v[--l]);
		while(r > y) remove(v[r--]);
		while(l < x) remove(v[l++]);
		return ans;
	}
}


int main(){
	fastio;
	cin >> n;
	sz = (int)floor(sqrt(n)); 
	frr(i,n) cin >> v[i];
	cin >> q;
	fr(i,q){
		qry a;
		cin >> a.l >> a.r;
		a.ind = i;
		qq[i]= a;
	}

	sort(qq,qq+q);
	int res[200100];
	fr(i,q){
		qry a = qq[i];
		res[a.ind] = query(a.l,a.r); 
	}

	fr(i,q) cout<< res[i] << endl;
}
