void yo(int i, int l, int r, int optl, int optr) {
	if(l > r) return;
	int mid = (l + r) / 2;
	dp[i][mid] = inf; // for maximum cost change it to 0
	int opt = -1;
	for(int k = optl; k <= min(mid - 1, optr); k++) {
		int c = dp[i - 1][k] + cost(k + 1, mid);
		if(c < dp[i][mid]) { // for maximum cost just change < to > only and rest of the algo should not be changed
			dp[i][mid] = c;
			opt = k;
		}
	}
	// for opt[1..j] <= opt[1...j+1]
	if (opt == -1) {
    // if we can't divide into k parts, then go right
		yo(i, mid + 1, r, optl, optr);
		return;
	}
	yo(i, l, mid - 1, optl, opt);
	yo(i, mid + 1, r, opt, optr);

	// for opt[1...j] >= opt[1...j+1]
	// yo(i, l, mid-1, opt, optr);
	// yo(i, mid+1, r, optl, opt);

}
//for(i = 1; i <= n; i++) dp[1][i] = cost(1, i);
//for(i = 2; i <= k; i++) yo(i, 1, n, 1, n);