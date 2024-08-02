class Solution {
public:
    int myAtoi(string s) {
        int i = 0, sign = 1;
        long asn = 0;
        while(s[i] == ' ') i++;
        if(s[i] == '+' || s[i] == '-') sign = 1 - 2 * (s[i++] == '-');

        while(s[i] >= '0' && s[i] <= '9') {
            asn = asn * 10 + (s[i++] - '0');

        }
        asn *= sign;
        return asn;
    }
};