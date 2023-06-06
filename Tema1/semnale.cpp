#include <iostream>
#include <vector>

using namespace std;

const uint64_t MOD = 1000000007;

int comb(int n, int k) {
	int res = 1;

	vector <int> inv(k + 1, 0);
	// base cases
    inv[0] = 1;
	inv[1] = 1;

	// inv(i) = MOD - (MOD / i) * inv(MOD % i) % MOD
	// where MOD = prime
    for (int i = 2; i <= k; i++) {
        inv[i] = MOD - (uint64_t)(MOD / i) * inv[MOD % i] % MOD;
    }

	// n * (n - 1) * ... * (n - k + 1)
	for (int i = n - k + 1; i <= n; i++) {
		res = ((res % MOD) * i) % MOD;
	}

    // 1 / (k!)
	// (a / b) % MOD = (a * inv(b)) % MOD
	// where b * inv(b) = 1
	for (int i = 2; i <= k; i++) {
		res = ((res % MOD) * inv[i]) % MOD;
	}

    return res;
}

int type1(int num0, int num1) {
	// impossible case
    if (num1 > num0 + 1) {
		return 0;
	}

    return comb(num0 + 1, num1);
}

int type2(int num0, int num1) {
	// impossible case
	if (num1 > 2 * num0 + 1) {
		return 0;
	}

	// combinations for no consecutive ones
	int ans = type1(num0, num1);
	int num = num1 - 1;

	// combinations for groups of consecutive ones
	for (int groups11 = 1; groups11 <= num1 / 2; groups11++) {
		// possible combinations for placing either 1 or 11
		uint64_t comb_ones = type1(num0, num);
		// posible mods for placing 11 groups
		uint64_t comb_mod = comb(num, groups11);
		// total combinations
		uint64_t p = (comb_mod * comb_ones) % MOD;
		ans = (ans + p) % MOD;
		num--;
	}

	return ans;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
