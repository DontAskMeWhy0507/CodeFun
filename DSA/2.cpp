#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap {
    private:
    vector<int> heap;
    public:
    Heap() {
        arr = vector<int>(1);
    }
    void insert(int x) {
        arr.push_back(x);
        int idx = arr.size() - 1;
        //Nếu cha lớn hơn con thì đổi chỗ cha và con.
        while (idx > 1 && arr[idx] < arr[idx / 2]) { 
            swap(arr[idx], arr[idx / 2]);
            idx /= 2;
        }
    }

    void print_arr() {
        for (int i = 1; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int findMin() {
        return arr[1];
    }

    void removeMin() {
        arr[1] = arr[arr.size() - 1];
        arr.pop_back();
        int idx = 1;
        while (true) {
            int left = indx * 2, right = left + 1;
            if (left >= arr.size()) return;


            int choose = left;
            if (right < arr.size() && arr[right] < arr[left]) choose = right;


            if (arr[indx] > arr[choose]) swap(arr[choose],arr[indx]);
            else return;
            indx = choose;
        }
    }

    int size() {
        return arr.size() - 1;
    }
}

 int main()
 {

 }