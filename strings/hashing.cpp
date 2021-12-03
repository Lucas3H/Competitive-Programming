/*
	String Hashing

 	Complexity:
 		hash_s     : O(|s|)
 		operator() : O(1)

	Details:
		- To use more than one prime, you may use __int128 or array<int>
		- You may easily change it to handle vector<int> instead of string

	Based on: 
		https://github.com/gabrielmorete/Competitive-Programming/blob/master/Caderninho/Strings/string_hashing.cpp
*/

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count()); // Random number generator
static long long base = uniform_int_distribution<int>(27, mod1 - 1)(rng);	// In case TL, use const
// Remember (alfabet < base < mod)

struct hash_s{
	const long long mod1 = 1000015553, mod2 = 1000028537;
	// Other large primes: 1000041323, 100663319, 201326611

	// If smaller primes are needed(For instance, need to store the mods in an array):
	// 50331653, 12582917, 6291469, 3145739, 1572869
	string s; 
	long long n;
	vector<long long> hsh1, pwr1, hsh2, pwr2;

	hash_s() : n(0) {}
	hash_s(string _s) : n(_s.size()), s(_s), hsh1(n), pwr1(n), hsh2(n), pwr2(n){	
		pwr1[0] = pwr2[0] = 1;
		for (int i = 1; i < n; i++){
			pwr1[i] = (base * pwr1[i - 1]) % mod1;
			pwr2[i] = (base * pwr2[i - 1]) % mod2;
		}
		hsh1[0] = hsh2[0] = s[0] - 'a' + 1;
		for (int i = 1; i < n; i++){
			hsh1[i] = (hsh1[i - 1] * base + (long long)(s[i] - 'a' + 1))%mod1;
			hsh2[i] = (hsh2[i - 1] * base + (long long)(s[i] - 'a' + 1))%mod2;
		}
	}
	long long hash(int i, int j){ // hash no intervalo [i, j]
		if (i == 0) return (hsh1[j] << 30)^(hsh2[j]);;
		long long ret1 = ((hsh1[j] - (hsh1[i - 1] * pwr1[j - i + 1])) % mod1 + mod1) % mod1;
		long long ret2 = ((hsh2[j] - (hsh2[i - 1] * pwr2[j - i + 1])) % mod2 + mod2) % mod2;
		return (ret1 << 30)^(ret2);
	}
};


/*
 	Maximum Common Prefix
	
	Based on this function it's easy to code other variants like:
 		- lexicographically smaller/greater

 	Complexity:	 O(log(a.size(), b.size()))
*/
int max_pref(const hash_s & a, const hash_s & b){
	int l = -1, r = min(a.s.size(), b.s.size()), m;
	while(l < r - 1){
		m = (l + r)/2;
		if(a.hash(0, m) == b.hash(0, m)) l = m;
		else r = m;
	}

	return l + 1;
}