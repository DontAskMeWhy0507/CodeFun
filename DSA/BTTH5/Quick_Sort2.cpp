#include <bits/stdc++.h>
using namespace std;


void quickSort(vector <int> &arr) {
    // Complete this function
    vector <int> lower, higher;
    if(arr.size() <= 1) return ;
     auto pivot = arr[0];
     for (auto i : arr) {
         if (i < pivot) lower.push_back(i);
         else if (i > pivot)higher.push_back(i);
     }
     
     quickSort(lower);
     quickSort(higher);
     
     arr = vector<int>();
     for(auto i: lower) arr.push_back(i);
     arr.push_back(pivot);
    for(auto i: higher) arr.push_back(i);
    
    for(auto i: arr) cout << i << " ";
    cout << endl;

}


int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);

    return 0;
}
