#include <iostream>

using namespace std;

int solve (int n, int m)
{
  if(n<0) return 0;
  if(n==0) return 1;

  int ans = 0;
  for (int i = m+1; i <= n; i++)
    ans += solve(n-i,i);
    return ans;
  
}

int main(){
  int n;
  cin>>n;
  cout<< solve(n,0);

 
}