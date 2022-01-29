/*
	Fast exponentiation

	It's used to compute n^e fast.	

	Complexity: O(log(e))
*/

ll fastxp(ll n, ll e){
    ll ans = 1, pwr = n;
    while(e){
        if(e%2)  ans = ans * pwr % MOD;
        e /= 2;
        pwr = pwr * pwr % MOD;
    }
    return ans % MOD;
}