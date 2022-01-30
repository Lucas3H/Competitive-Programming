// https://www.spoj.com/problems/INVCNT/

#include<bits/stdc++.h>

using namespace std;

#define fr(i, n) for(ll i = 0; i < n; i++)
#define frr(i, n) for(ll i = 1; i <= n; i++)
#define frm(i, n) for(ll i = n-1; i >= 0; i--)

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int, int> ponto;
typedef vector<vector<ll>> matrix;

#define mem(v, k) memset(v, k, sizeof(v));

#define db cout << "Debug" << endl;

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007

map<ll, ll> m;
set<ll> s;
ll bit[4*MAXN], v[4*MAXN];
ll n;

void update(ll i, ll v){
    while(i <= n){
        bit[i]+=v;
        i += i &(-i);
    }
}

ll query(ll i){
    ll sum = 0;
    while(i > 0){
        sum += bit[i];
        i -= i&(-i);
    }

    return sum;
}

ll build(){
    fr(i, n+1) bit[i] = 0;

    ll inv = 0;
    frr(i, n) {
        inv += i - (ll)1 - query(m[v[i]]);
        update(m[v[i]], (ll)1);
    }

    return inv;
}

int main(){
	ios::sync_with_stdio(false);
    int t;
    cin >> t;

    while(t--){
        m.clear();
        s.clear();

        cin >> n;
        frr(i, n){
            cin >> v[i];
            s.insert(v[i]);
        }

        ll i = (ll)1;
        for(auto x: s) m[x] = i++;

        //for(auto x: s) cout <<x  << " " << m[x] << endl;

        cout << build() << endl;
    }

}
