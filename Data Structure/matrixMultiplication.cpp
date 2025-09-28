
ll MOD = 1e9 + 9;

void matmul(vector<vector<ll>> &a, vector<vector<ll>> b) {
	int n = a.size(), m = a[0].size(), p = b[0].size();
	vector<vector<ll>> c(n, vector<ll>(p));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			for (int k = 0; k < m; k++) {
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
			}
		}
	}

	a = c;
}

struct Matrix {
	vector<vector<ll>> mat;
	Matrix() {}
	Matrix(vector<vector<ll>> a) { mat = a; }
	Matrix(int n, int m) {
		mat.resize(n);
		for (int i = 0; i < n; i++) { mat[i].resize(m); }
	}

	int rows() const { return mat.size(); }
	int cols() const { return mat[0].size(); }

	void makeiden() {
		for (int i = 0; i < rows(); i++) { mat[i][i] = 1; }
	}

	Matrix operator*=(const Matrix &b) {
		matmul(mat, b.mat);
		return *this;
	}

	Matrix operator*(const Matrix &b) { return Matrix(*this) *= b; }
};

int main() {
	ios::sync_with_stdio(false) , cin.tie(0);
	ll n , m , c;
	cin >> n >> m >> c;
	Matrix mat(n, n), vec(n, 1), cur(n, n);
	cur.makeiden();
	for (int i = 0; i < n; i++) { cin >> vec.mat[i][0]; }

	for (int i = 0; i < c; i++) {
		int idx; cin >> idx;
		debug(n - idx);	
		mat.mat[n - 1][n - idx] = 1;
	}

	for (int i = 1; i < n; i++) { mat.mat[i - 1][i] = 1; }

	m--;
	while (m > 0) {
		if (m & 1) cur *= mat;
		mat *= mat;
		m >>= 1;
	}
	Matrix res = cur * vec;
	cout << res.mat[0][0] << '\n';
}

