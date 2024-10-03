#include <iostream>
using namespace std;

// Mỗi bước lặp chọn phần tử nhỏ nhất trong mảng lên đầu mảng
void SelectionSort (int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(a[i], a[min]);
        }
    }
}

// Mỗi bước lặp đổi chỗ 2 phần tử liền kề nếu chúng không theo thứ tự
void BubbleSort (int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// Mỗi bước lặp chèn phần tử vào đúng vị trí trong mảng đã sắp xếp
void InsertionSort (int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void CountingSort (int a[], int n) {
    
}

int main() {
    int n = 10;
    int a[] = {10, 29, 2, 30, 1, 99, 100, 3, 4, 5};
    //SelectionSort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}