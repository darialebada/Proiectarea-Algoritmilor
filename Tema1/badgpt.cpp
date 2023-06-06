#include <fstream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

// function for 2x2 matrix multiplication
void matrix_mult(uint64_t M[2][2], uint64_t I[2][2]) {
    // matrix is 2x2, so we can easily calculate it
    uint64_t a = ((M[0][0] % MOD) * (I[0][0] % MOD))
                 + ((M[0][1] % MOD) * (I[1][0] % MOD));

    uint64_t b = ((M[0][0] % MOD) * (I[0][1] % MOD))
                 + ((M[0][1] % MOD) * (I[1][1] % MOD));

    uint64_t c = ((M[1][0] % MOD) * (I[0][1] % MOD))
                 + ((M[1][1] % MOD) * (I[1][1] % MOD));

    // add new values in matrix
    M[0][0] = a % MOD;
    // we know that Fibo(n) = M[0][1] = M[1][0], so it is
    // not necessarily to calculate M[1][0]
    M[0][1] = M[1][0] = b % MOD;
    M[1][1] = c % MOD;
}

uint64_t matrix_exp(uint64_t M[2][2], uint64_t n) {
    // identity matrix
    uint64_t I[2][2] = { {1, 0},
                         {0, 1} };

    // O(log n) matrix exponentiation
    while (n > 0) {
        // odd power
        if (n % 2 == 1) {
            matrix_mult(I, M);
        }
        matrix_mult(M, M);
        n /= 2;
    }

    return I[0][0];
}

uint64_t fibo(uint64_t n) {
    // base cases
    if (n == 0 || n == 1) {
        return 1;
    }

    // matrix exponentiation solution
    uint64_t M[2][2] = { {1, 1},
                         {1, 0} };

    return matrix_exp(M, n);
}

int bad_gpt() {
    ifstream fin("badgpt.in");
    char ch;
    uint64_t num;
    int ans = 1;

    // read each character from file
    while (fin >> ch && fin >> num) {
        if (ch == 'n' || ch == 'u') {
            ans = (ans * fibo(num)) % MOD;
        }
    }

    fin.close();
    return ans;
}

int main() {
    ofstream fout("badgpt.out");

    fout << bad_gpt();

    fout.close();
    return 0;
}
