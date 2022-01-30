/*
	SUM OVER SUBSETS
	
	Description: Iterate over all subsets of a mask
	
	Complexity: O(n * 2^n)
	
	Credits: https://codeforces.com/blog/entry/45223
*/
for(int i = 0; i < (1 << n); ++i)
	F[i] = A[i];
for(int i = 0;i < n; ++i) for(int mask = 0; mask < (1 << n); ++mask){
	if(mask & (1 << i))
		F[mask] += F[mask ^ (1 << i)];
}

/*
	Inclustion-Exclusion on val
*/
ans[0] = 0;	
for(int i = 0; i < (1 << n); ++i){
	if(__builtin_parity(i)) ans[i] = val[i];
	else ans[i] = MOD - val[i];
}
for(int i = 0;i < n; ++i) for(int mask = 0; mask < (1 << n); ++mask){
	if(mask & (1<<i)){
		ans[mask] = (ans[mask] + ans[mask^(1<<i)])%MOD;		
	}
}


/*
	Complexity: O(3^n)
*/
for (int mask = 0; mask < (1 << n); mask++){
	F[mask] = A[0];
    // iterate over all the subsets of the mask
    for(int i = mask; i > 0; i = (i-1) & mask){
    	F[mask] += A[i];
    }
}