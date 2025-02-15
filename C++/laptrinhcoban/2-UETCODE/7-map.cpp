/*
Cho hai dãy số A,B chứa các số nguyên. 
Bạn hãy viết chương trình đếm số lượng cặp chỉ số i,j
sao cho Ai+Bj=0
.*/


#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    long long m, n;
    // Read the sizes of the arrays
    cin >> m >> n;

    vector<long long> A(m);
    vector<long long> B(n);

    // Read the elements of array A
    for (long long i = 0; i < m; ++i) {
        cin >> A[i];
    }

    // Read the elements of array B
    for (long long i = 0; i < n; ++i) {
        cin >> B[i];
    }

    // Create a hash map to store frequencies of elements in B
    unordered_map<long long, long long> freqB;
    for (long long i = 0; i < n; ++i) {
        freqB[B[i]]++;
    }

    // Count pairs (i, j) such that A[i] + B[j] = 0
    long long count = 0;
    for (long long i = 0; i < m; ++i) {
        int complement = -A[i];
        if (freqB.find(complement) != freqB.end()) {
            count += freqB[complement];
        }
    }

    // Output the result
    cout << count << endl;

    return 0;
}
