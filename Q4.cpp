#include<iostream>

using namespace std;

struct Data {
	int value;
	int pos;
	Data(int val, int p) {
		value = val;
		pos = p;
	}
};


int MaxPower(int M, int N, int**arr) {
	Data max1(-1, 0);
	Data max2(-1, 0);
	Data pmax1(0, -1);
	Data pmax2(0, -1);

	for (int j = N - 1; j >= 0; j--) {		//column
		//resetting max
		max1.value = -1;
		max2.value = -1;
		for (int i = 0; i < M; i++) {		//row
			int num = arr[i][j];
			if (i != pmax1.pos) {
				num += pmax1.value;
			}
			else {
				num += pmax2.value;
			}

			if (num >= max1.value) {
				max2.value = max1.value;
				max2.pos = max1.pos;

				max1.value = num;
				max1.pos = i;
			}
			else if (num >= max2.value) {
				max2.value = num;
				max2.pos = i;
			}
		}
		//resetting current and updating previous for the next column
		if (max1.value > pmax1.value) {
			if (pmax1.value > max2.value) {
				pmax2.value = pmax1.value;
				pmax2.pos = pmax1.pos;
			}
			else {
				pmax2.value = max2.value;
				pmax2.pos = max2.pos;
			}
			pmax1.value = max1.value;
			pmax1.pos = max1.pos;
		}
		else if (max1.value > pmax2.value) {
			pmax2.value = max1.value;
			pmax2.pos = max1.pos;
		}
	}
	return max1.value;
}

int main() {
	int M=0, N=0;
	cin >> M >> N;

	int** arr = new int* [M];

	for (int i = 0; i < M; i++) {
		arr[i] = new int[N];
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N ; j++) {
			cin >> arr[i][j];
		}
	}

	int max = 0;
	if (M == 1) {		//special case extracted in O(M)
		for (int i = 0; i < N; i++) {
			int val = arr[0][i];
			if (val > max) {
				max = val;
			}
		}
	}
	else {
		max = MaxPower(M, N, arr);
	}

	cout << max << endl;
	return 0;
}

