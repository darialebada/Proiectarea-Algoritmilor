#include <fstream>
#include <vector>

using namespace std;

// memorise where subtree starts in dfs
vector<int> start;
// memorise where subtree ends in dfs
vector<int> finish;
// adjacency list
vector<vector<int>> adj;
// nodes after dfs
vector<int> dfs_arr;

void dfs(int node, int& timestamp) {
    // start visiting node's subtree
    start[node] = ++timestamp;
    // add node to vector
    dfs_arr.push_back(node);

    // get neighbours
    for (auto neigh : adj[node]) {
        dfs(neigh, timestamp);
    }

    // finish visiting node's subtree
    finish[node] = timestamp;
}

int ans_question(int node, int e) {
    // if subtree length is lower than e, return -1
    if (finish[node] - start[node] < e) {
        return -1;
    }

    // return node
    return dfs_arr[start[node] + e - 1];
}

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    // read data from stdin
    int n, q;
    fin >> n >> q;

    // resize adj list
    adj.resize(n + 1);

    int x;
    for (int i = 2; i <= n; i++) {
        fin >> x;
        // edge (x, y)
        adj[x].push_back(i);
    }

    int timestamp = 0;
    start.resize(n + 1);
    finish.resize(n + 1);

    // dfs starting from node 1
    dfs(1, timestamp);

    int d, e;
    for (int i = 0; i < q; i++) {
        fin >> d >> e;
        fout << ans_question(d, e) << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
