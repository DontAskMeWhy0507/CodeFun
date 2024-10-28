#include <iostrea>
#include <vector>
#include <queue>
using namespace std;
vector<double> runningMedian(vector<int> a) {
    vector<double> res;
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i = 0; i < a.size(); i++) {
        if (maxHeap.empty() || a[i] < maxHeap.top()) {
            maxHeap.push(a[i]);
        } else {
            minHeap.push(a[i]);
        }
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        if (maxHeap.size() == minHeap.size()) {
            res.push_back((maxHeap.top() + minHeap.top()) / 2.0);
        } else {
            res.push_back(maxHeap.top());
        }
    }
    return res;
}