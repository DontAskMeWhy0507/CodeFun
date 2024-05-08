
#include <iostream>
#include <string>   
using namespace std;
int insert(int arr[], int n, int pos, int value)
{
 for (int i = n; i >= pos; i--) {
 arr[i] = arr[i-1];
 }
  arr[pos-1] = value;
 return n+1;
}

int main()
{
    int n,arr[100],pos,value;
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
    cin>>value>>pos;
    n=insert(arr,n,pos,value);
   
    for (int i = 0; i < n; i++)
    {
        cout<<arr[i]<<" ";
    }

    
}