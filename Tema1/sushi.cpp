#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector <int> &prices, vector <int> &grades) {
	// max money that can be paid
	int max_money = n * x;
	// table for dynamic programming method
	vector < vector<int> > dp(m + 1, vector<int>(max_money + 1, 0));

	// "padding" for the table - base case
	for (int i = 0; i <= max_money; i++) {
		dp[0][i] = 0;
	}
	for (int i = 0; i <= m; i++) {
		dp[i][0] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int cost = 1; cost <= max_money; cost++) {
			// don't use sushi i => solution is the previous one (step i - 1)
			dp[i][cost] = dp[i - 1][cost];

			// check if i can use sushi i (if price is lower than solution)
			if (prices[i] <= cost) {
				// make sure that i have previously only used total_cost - price[item] money
				dp[i][cost] = max(dp[i][cost],
								  grades[i] + dp[i - 1][cost - prices[i]]);
			}
		}
	}

	return dp[m][max_money];
}

int task2(int n, int m, int x, vector <int> &prices, vector <int> &grades) {
	// duplicate each sushi type
	prices.resize(2 * m + 1);
	grades.resize(2 * m + 1);
	for (int i = m + 1; i <= 2 * m; i++) {
		prices[i] = prices[i - m];
		grades[i] = grades[i - m];
	}

	return task1(n, 2 * m + 1, x, prices, grades);
}

int task3(int n, int m, int x, vector <int> &prices, vector <int> &grades) {
	// duplicate each sushi type
	prices.resize(2 * m + 1);
	grades.resize(2 * m + 1);
	for (int i = m + 1; i <= 2 * m; i++) {
		prices[i] = prices[i - m];
		grades[i] = grades[i - m];
	}

	m = 2 * m + 1;
	int max_money = n * x;
	// table for dynamic programming method
	// dp[sushi type][cost][number of items at the moment]
	vector < vector < vector<int> > > dp(m + 1,
										 vector < vector<int> >(max_money + 1,
										 vector<int>(n + 1, 0)));

	// "padding" for the table - base case
	for (int cost = 0; cost <= max_money; cost++) {
		for (int k = 0; k <= n; k++)
			dp[0][cost][k] = 0;
	}

	// same as task1, but with maximum k items chosen
	for (int i = 1; i <= m; i++) {
		for (int cost = 1; cost <= max_money; cost++) {
			for (int k = 1; k <= n; k++) {
				// don't use sushi i => solution is the previous one (step i - 1)
				dp[i][cost][k] = dp[i - 1][cost][k];

				// check if i can use sushi i (if price is lower than solution)
				if (prices[i] <= cost) {
					// make sure that i have previously only used
					// total_cost - price[item] money
					// and number_friends - 1 sushi types
					dp[i][cost][k] = max(dp[i][cost][k],
								  	  	 grades[i] + dp[i - 1][cost - prices[i]][k - 1]);
				}
			}
		}
	}

	return dp[m][max_money][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m + 1, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 1; i <= m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	// get rating for each sushi type
	vector<int> grades_sum(m + 1);
	for(int i = 0; i < m; ++i) {
		int sum = 0;
		for(int j = 0; j < n; ++j) {
			sum += grades[j][i];
		}
		grades_sum[i + 1] = sum;
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades_sum);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades_sum);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades_sum);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
