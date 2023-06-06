/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int64_t SolveTask1(const vector<int>& a, const vector<int>& b, const int n) {
    int64_t sum = 0;

    // merged lists
    vector<int> ab(2 * n);

    // add values from first list
    for (int i = 0; i < n; i++) {
        ab[i] = a[i];
    }

    // add values from second list
    for (int i = n; i < 2 * n; i++) {
        ab[i] = b[i - n];
    }

    // time complexity O (n*logn)
    sort(ab.begin(), ab.end());

    // adding to the sum the largest n numbers from the merged list
    for (int i = 2 * n - 1; i >= n; i--) {
        sum += ab[i];
    }

    return sum;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int k, int n) {
    // max values from pairs before any moves
    vector<int> added(n);
    // min values from pairs before any moves
    vector<int> not_added(n);

    for (int i = 0; i < n; i++) {
        added[i] = max(a[i], b[i]);
        not_added[i] = min(a[i], b[i]);
    }

    // sort elements in ascending order
    sort(added.begin(), added.end());
    // sort elements in descending order
    sort(not_added.begin(), not_added.end(), greater<int>());

    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        // make no more than k moves
        if (i < k && not_added[i] > added[i]) {
            sum += not_added[i];
        } else {
            sum += added[i];
        }
    }

    return sum;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b, n) : SolveTask2(a, b, moves, n);
    fout << res << "\n";

    return 0;
}
