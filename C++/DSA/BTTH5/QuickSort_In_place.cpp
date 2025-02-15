#include <iostream>
#include <vector>
#include <algorithm> // for std::swap

// Print out int array
void dump(const std::vector<int>& arr) {
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Partition method, returns the pivot index
int partition(std::vector<int>& arr, int lt, int rt) {
    int pivot = rt; // choose right as pivot
    int pval = arr[pivot];
    int new_pivot = lt;

    for (int i = lt; i < rt; ++i) {
        if (arr[i] < pval) {
            std::swap(arr[i], arr[new_pivot++]);
        }
    }
    std::swap(arr[rt], arr[new_pivot]);

    dump(arr); // Display the array after partitioning
    return new_pivot;
}

// Quicksort implementation
void quicksort(std::vector<int>& arr, int lt, int rt) {
    if (lt >= rt) return;
    
    int pivot = partition(arr, lt, rt);
    quicksort(arr, lt, pivot - 1);
    quicksort(arr, pivot + 1, rt);
}

int main() {
    int size;
    std::cin >> size;

    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    quicksort(arr, 0, size - 1);

    return 0;
}
