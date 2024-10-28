
int cookies(int k, vector<int> A) {
    int ans = 0;
    priority_queue<int,vector<int>,greater<int>> pq;
    for (auto x : A) pq.push(x);
    while (pq.size() > 1 && pq.top() < k) {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        int newCookies = first +second*2;
        pq.push(newCookies);
        ans++;
    } 
    if (pq.top() < k) return -1;
    
    return ans;
    
}