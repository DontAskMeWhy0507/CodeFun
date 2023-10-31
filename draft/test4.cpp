   #include <iostream>
   #include <string>
    using namespace std;
    int diem(string s){ 
        if(s=="J"||s=="Q"||s=="K") return 10;
     

   
    }
    int main()
    {       
        string a,b;
        cin>>a>>b;
        int n =  diem(a)+diem(b);
        if(n==22)cout<<2;
        else cout<<n;
        return 0;
    }