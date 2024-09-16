int superDigit(string n, int k) {
    long long sum = 0;
    for (long long i = 0; i < n.length(); i++)
    {
        sum += (n[i] - '0'); 
    }
    sum *= k;
    if(sum <10) return sum;
    string s = to_string(sum);
    return sum(s,1);
}