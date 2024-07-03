#include<iostream>

using namespace std;

int Structure(int N, int prev, int**dp) {
	int sum = 0;
	int Ntemp = N;
	if (prev!=-1 && dp[N][prev] != -1) {
		return dp[N][prev];
	}

	if (N < prev && prev!=-1) {
		sum = 1;
	}

	int x = 1;
	N -= 1;

	while (N > 1) {
		if (prev == -1 || N<prev ) {
			sum += Structure(x, N, dp);
		}
		N -= 1;
		x += 1;
	}
	if (prev != -1) {
		dp[Ntemp][prev] = sum;
	}
	return sum;
}

int main() {

	int N = 0;
	cin >> N;

	int** dp = new int* [N];
	for (int i = 0; i < N; i++) {
		dp[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dp[i][j] = -1;
		}
	}

	cout << Structure(N, -1, dp);

	return 0;
}
