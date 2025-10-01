for (int i = 2; i <= maxV; ++i) 
	invVal[i] = (MOD - (MOD / i) * invVal[MOD % i] % MOD) % MOD;

