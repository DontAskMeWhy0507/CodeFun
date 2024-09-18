    unordered_map<long, long> save;
long stoneDivision(long n, vector<long> s) {
    if(save.find(n) != save.end()) return save[n];
    long res = 0;
    for (long div : s)
    {
        if(n % div == 0 && n != div)
        {
            res = max(res, 1 + div * stoneDivision(n / div, s));
        }
    }
    if (res == 0) return 0;
    return save[n] = res;
}
