/*
	Convex Hull Trick

	Description: DP optimization from O(n^2) to O(n log n)

		- If type=min, the angular coeficients must be in increasing order
		- If type=max, the angular coeficients must be in decreasing order

	Complexity:
		- Build is O(n)
		- Query is O(log n)
*/

struct CHT{
	using pll = pair<long, long>;
	using ll = long long;
	deque<pll> Hull;
	ll type=1; //0 max e 1 min

	ll getVal(pll a, ll x) {return a.f*x + a.s;}

	ll cmp(pll a, pll b, pll c){return ((double)(b.s - c.s)/(c.f - b.f) <= (double)(a.s - b.s)/(b.f - a.f));}

	void insert(ll inc, ll y){
	    Hull.push_front({inc,y});
	    while((Hull.size())> 2 && cmp(Hull[0],Hull[1],Hull[2]))
	      	Hull[1]=Hull[0], Hull.pop_front();
	}
	ll query(ll x) {
	    int l = -1, r = Hull.size() - 1;
	    while (r - l > 1) {
	        int m = (l + r) / 2;
	        if (type^(getVal(Hull[m], x) <= getVal(Hull[m + 1], x)))
	           	l = m;
	        else
	            r = m;
	    }
	    return getVal(Hull[r], x);
	}
};

pll l[MAXN];
ll n;
CHT c;

void build(){
	cin >> n;

	frr(i, n) cin >> l[i].f >> l[i].s;
	sort(l + 1, l + 1 + n);
	for(int i = 1; i <= n; i++)
		c.insert(l[i].f, l[i].s);
}