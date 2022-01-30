/*
    Referências:
    - https://en.wikipedia.org/wiki/Erdős–Gallai_theorem
    - https://www.cambridge.org/core/services/aop-cambridge-core/content/view/FCA8B7DC763D3D504C68E3A5FDD8DE45/S0004972700002872a.pdf/a-simple-proof-of-the-erdos-gallai-theorem-on-graph-sequences.pdf

    Problemas:
    - https://codeforces.com/gym/101726/problem/A
*/


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

#define mp make_pair
#define pq priority_queue

#define mx(a, b) a = max(a, b);
#define mod(a, b) a = a%b;

#define MAXN 100010
#define MOD 1000000007

ll n;
ll a[MAXN];

ll r[MAXN]; // r[k] é o maior l tal que a[l] >= k
ll s[MAXN]; // s[k] = a[1] + a[2] + ... + a[k]

bool ord(int a, int b) {
    return a > b;
}
void set_r_s(){
    ll sum = 0;

    fr(i, n+2) r[i] = 0;

    a[0] = MAXN;
    frr(i, n){
        sum += a[i];
        s[i] = sum;

        r[a[i]] = i;
    }

    for(int i = n; i >= 1; i--){
        if(r[i] == 0){
            r[i] = r[i+1];
        }
    }

    return;
}

bool Erdos_Gallai(){
    // First Condition: Sum of all number is even
    if(s[n]%2 == 1) return 0;

    //Second Condition:
    /*
        a[1] + ... + a[k] <= k*(k-1) + min(k, a[k+1]) + ... + min(k, a[n])
    */

    frr(i, n){
        ll sum_mins;
        if(r[i] >= i+1) sum_mins = (r[i] - i)*i + s[n] - s[r[i]];
        else sum_mins = s[n] - s[i];

        if(s[i] > sum_mins +  i*(i-1)) return 0;

    }

    return 1;
}

int main(){
	ios::sync_with_stdio(false);

    int t;
    cin >> t;

    while(t--){
        cin >> n;
        frr(i, n) cin >> a[i];

        sort(a+1, a+n+1, ord);

        set_r_s();
        int l = Erdos_Gallai();

        if(l) cout << "Y" << endl;
        else cout << "N" << endl;
    }
}
