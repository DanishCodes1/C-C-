#include <iostream>

using namespace std;


int* depots, * cuts, * cut_total;
int N, M, fixedM;

// Function to compute the product sum of depots from index i to j
int computeProductSum(int start, int end) {     //O(N)
    int sum = 0;
    int total = 0;
    for (int i = end; i >= start; i--) {
        total += depots[i] * sum;
        sum += depots[i];
    }
    return total;
}

void readjust_total(int cut_index) {    //linear complexity
    int start, end;

    //left
    if (cut_index == 0) {
        start = 0;
    }
    else {
        start = cuts[cut_index - 1] + 1;
    }
    end = cuts[cut_index];
    cut_total[cut_index] = computeProductSum(start, end);

    //right
    if (cut_index == fixedM - 1 || cuts[cut_index + 1] == -1) {
        end = N - 1;
    }
    else {
        end = cuts[cut_index + 1];
    }
    start = cuts[cut_index] + 1;
    cut_total[cut_index + 1] = computeProductSum(start, end);
}

int insertion_cut(int num) {       //insertion sort of single element O(N)
    int i = fixedM - 1;

    while (cuts[i - 1] == -1) {
        i--;
    }

    while (i > 0 && cuts[i - 1] > num) {
        cuts[i] = cuts[i - 1];
        cut_total[i + 1] = cut_total[i];
        i--;
    }
    cuts[i] = num;

    return i;
}



// Recursive function with memoization
void minStrategicValue(int start, int end, int M) {
    //if (i >= n - 1) return 0; // Base case: no or only one depot left.

    int sum = computeProductSum(start, end); // Compute sum for the whole segment without any cuts.
    if (M == 0) {
        return;
    }

    int min_value = sum; // Start with the value without any cuts as upper bound.
    int cut;
    if (start + 1 == end) {
        cut = start;
    }
    else {
        for (cut = start; cut < end; ++cut) { // Try cuts between every two depots
            int current_cut_sum = computeProductSum(start, cut) + computeProductSum(cut + 1, end);
            if (current_cut_sum <= min_value) {
                min_value = current_cut_sum;
            }
            else {      //the critical point for cut is found
                break;
            }
        }
        cut--;  //previous cut was correct
    }

    int index = insertion_cut(cut);
    readjust_total(index);
    M--;

    if (M == 0) {       //all cuts found
        return;
    }
    int max = 0;
    int max_index = -1;
    //now finding the segment that needs the next cut

    for (int i = 0; i <= fixedM; i++) {
        if (cut_total[i] > max) {
            max = cut_total[i];
            max_index = i;
        }
        else if (cut_total[i] == -1) {
            break;
        }
    }

    start = max_index - 1;
    end = max_index;
    if (cuts[end] == -1) {
        end = N - 1;
    }
    else {
        end = cuts[end];
    }

    if (start >= 0) {
        start = cuts[start];
    }

    minStrategicValue(start + 1, end, M);


    return;
}

int main() {
    int total = 0;
    while (true) {
        N = 0;
        M = 0;
        fixedM = 0;
        std::cin >> N >> M;
        fixedM = M;
        if (N == 0 && M == 0) break;

        depots = new int[N];
        cuts = new int[M];
        cut_total = new int[M + 1];
        for (int i = 0; i < M; i++) {
            cuts[i] = -1;
            cut_total[i] = -1;
        }
        cut_total[M] = -1;

        for (int i = 0; i < N; i++) {
            std::cin >> depots[i];
        }

        if (M == 0) {
            total = computeProductSum(0, N - 1);
        }
        else {

            minStrategicValue(0, N - 1, M);
            total = 0;
            for (int i = 0; i <= fixedM; i++) {
                if (cut_total[i] < 0) { continue; }
                total += cut_total[i];
            }
        }
        cout << total << endl;

        delete[] depots;
        delete[] cuts;
        delete[] cut_total;
        depots = NULL;
        cuts = NULL;
        cut_total = NULL;
    }
    return 0;
}