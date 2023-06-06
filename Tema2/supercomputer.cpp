#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Kahn's algorithm for topological sort
int top_sort(int type, vector<vector<int>> adj, vector<int> dep,
             vector<int> in_degree, queue<int> q_1, queue<int> q_2) {
    vector<int> topsort;

    while (!q_1.empty() || !q_2.empty()) {
        // change type if the current used queue is empty
        if (type == 1 && q_1.empty()) {
            type = 2;
        } else if (type == 2 && q_2.empty()) {
            type = 1;
        }

        // extract first node from queue (after type)
        int node;
        if (type == 1) {
            node = q_1.front();
            q_1.pop();
        } else {
            node = q_2.front();
            q_2.pop();
        }

        // add node to solution
        topsort.push_back(node);

        // check neighbours
        for (int i = 0; i < adj[node].size(); i++) {
            int neigh = adj[node][i];

            // decrement indegree for neighbour
            in_degree[neigh]--;

            // add to correct queue
            if (in_degree[neigh] == 0) {
                if (dep[neigh] == 1) {
                    q_1.push(neigh);
                } else {
                    q_2.push(neigh);
                }
            }
        }
    }

    // get number of context switches
    int ans = 0;
    int prevDep = dep[topsort[0]];
    for (auto i : topsort) {
        if (dep[i] != prevDep) {
            prevDep = dep[i];
            ans++;
        }
    }

    return ans;
}

int
num_switch(int n, int m, vector<vector<int>> adj, vector<int> dep,
           vector<int> in_degree) {
    // queue for tasks using dataset 1
    queue<int> q_1;
    // queue for tasks using dataset 2
    queue<int> q_2;

    for (int node = 1; node <= n; node++) {
        // add nodes with indegree 0 in queue by dataset type
        if (in_degree[node] == 0) {
            if (dep[node] == 1) {
                q_1.push(node);
            } else {
                q_2.push(node);
            }
        }
    }

    // get number of context switches starting with dataset type 1
    int num_1 = top_sort(1, adj, dep, in_degree, q_1, q_2);
    // get number of context switches starting with dataset type 2
    int num_2 = top_sort(2, adj, dep, in_degree, q_1, q_2);

    // get minimum number of context switches
    return min(num_1, num_2);
}


int main() {
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");

    // n vertices, m edges
    int n, m;
    fin >> n >> m;

    // adjacency list
    vector<vector<int>> adj(n + 1);
    // dependencies list
    vector<int> dep(n + 1);
    // indegree list
    vector<int> in_degree(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        fin >> dep[i];
    }

    int x, y;
    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        // directed edge (x, y)
        adj[x].push_back(y);
        // add another directed edge with y as head end
        ++in_degree[y];
    }

    fout << num_switch(n, m, adj, dep, in_degree);

    fin.close();
    fout.close();
    return 0;
}
