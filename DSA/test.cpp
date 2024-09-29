vector<int> dynamicArray(int n, vector<vector<int>> queries) {
    vector<vector<int>> arr(n,vector<int>());
    int last = 0;
    vector <int> result;
    for(int i=0;i<queries.size();i++){
        int x = queries[i][1];
        int y = queries[i][2];
        int index = (x^last)%n; 
        if(queries[i][0]==1){
            arr[index].push_back(y);
        }
        else{
            last = arr[index][y%arr[index].size()];
            result.push_back(last);
        }
    }
    return result;
}