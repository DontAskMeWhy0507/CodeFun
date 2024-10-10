
void countSort(vector<vector<string>> arr) {
    int n = arr.size();

    // A vector with 100 elements, where each element is a vector of strings
    vector<vector<string>> buckets(100); 

    // Fill the buckets with the list of strings
    for (int i = 0; i < n; ++i) {
        int index = stoi(arr[i][0]);
        if (i < n / 2) {
            buckets[index].push_back("-");
        } else {
            buckets[index].push_back(arr[i][1]);
        }
    }

    // Print the sorted strings
    for (int i = 0; i < 100; ++i) {
        for (const string &str : buckets[i]) {  // Print each string in the bucket
            cout << str << " ";
        }
    }
    cout << endl;
}