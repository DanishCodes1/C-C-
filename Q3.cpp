#include<iostream>
#include<algorithm>

using namespace std;


int findSegments(int *arr, int** minDP, int N) {
	int max = -1, cmnp = 0, next = 1;
	

	//forward
	for (int i = 0; i < N; i++) {
		int val = arr[i];
		if (val > max) {
			max = val;
		}
		if (next == val) {
			next += 1;
		}
		if (val == cmnp) {
			cmnp = next;
			next = cmnp + 1;
			if (next == max) {
				next++;
			}
		}
		minDP[0][i] = cmnp;		//storing history at each traversal
	}

	//backward
	max = -1;
	cmnp = 0;
	next = 1;

	for (int i = N - 1; i >= 0; i--) {
		int val = arr[i];
		if (val > max) {
			max = val;
		}
		if (next == val) {
			next += 1;
		}
		if (val == cmnp) {
			cmnp = next;
			next = cmnp + 1;
			if (next == max) {
				next++;
			}
		}
		minDP[1][i] = cmnp;		//storing history at each traversal
	}

	for (int i = 0; i < N - 1; i++) {
		//both sides of partition have the same MNPN
		if (minDP[0][i] == minDP[1][i + 1]) {
			return i + 1;
		}
	}

	return -1;
}


int main() {
	int M = 0, N = 0;
	cin >> N;

	int* arr = new int[N];
	int** minDP = new int *[2];
	for (int i = 0; i < 2; i++) {
		minDP[i] = new int[N];
	}

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		minDP[0][i] = -1;
		minDP[1][i] = -1;
	}

	int partition = findSegments(arr, minDP, N);

	if (partition != -1) {
		cout << 2 << endl;
		cout << "1 " << partition << endl;
		cout << partition + 1 << " " << N << endl;
	}
	else {
		cout << partition << endl;
	}

	return 0;
}

