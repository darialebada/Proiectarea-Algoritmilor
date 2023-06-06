#include <fstream>
#include <vector>

using namespace std;
// for easier writing
typedef unsigned long long ull;

// check if current solution is valid
bool check_solution(ull mid, int n, int k, vector<ull> cars) {
    ull sum = 0;
    int ferry = 0;

    for (int i = 0; i < n && ferry < k; i++) {
        if (cars[i] + sum <= mid) {
            sum += cars[i];
        } else {
            // can't fit on current ferry, we need a new one
            sum = cars[i];
            ferry++;
        }
    }

    if (ferry == k) {
        // not enought ferries, wrong mid value
        return false;
    }
    return true;
}

ull
binary_search(int n, int k, vector<ull> cars, ull left, ull right) {
    ull res, mid;

    while (left <= right) {
        // for big numbers
        mid = left + (right - left) / 2;

        if (check_solution(mid, n, k, cars)) {
            // we assume the solution is correct
            res = mid;
            // search for a smaller solution
            right = mid - 1;
        } else {
            // wrong solution, search for a higher one
            left = mid + 1;
        }
    }

    return res;
}

ull
get_cars_on_ferry(int n, int k, vector<ull> cars) {
    ull left = 0, right = 0;

    // right = sum of all weights from vector cars
    // left = max weight from vector cars
    for (int i = 0; i < n; i++) {
        right += cars[i];
        if (left < cars[i]) {
            left = cars[i];
        }
    }

    // binary search on solution
    return binary_search(n, k, cars, left, right);
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    int n, k;
    fin >> n >> k;
    vector<ull> cars(n);
    for (int i = 0; i < n; i++) {
        fin >> cars[i];
    }

    fout << get_cars_on_ferry(n, k, cars);

    fin.close();
    fout.close();
    return 0;
}
