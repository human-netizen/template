
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 10, LOG_A = 20;

int basis[LOG_A];

void insertVector(int mask) {
	for (int i = LOG_A - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
			return;
		}

		mask ^= basis[i];
	}
}

int main() {
	for (int i = LOG_A - 1; i >= 0; i--) {
		if (!basis[i]) continue;

		if (ans & 1 << i) continue;

		ans ^= basis[i];
	}
}