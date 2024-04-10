#include <iostream>
using namespace std;
int main()
{
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  int mh,mk,ml;
  int th = 0, tk = 0, tl = 0;
  for (int i =0; i < n; i++)
  {
    h += a[i];
    for (int j = i+1; j < n; j++)
    {
      mk += a[j];
      for (int k = j+1; k < n; k++)
      {
        ml+= a[k];
      }
    }
  }
}