void rotate ( int arr[], int n, int k){
 int tmp;

for(int x=k;x>0;x--){
 tmp=arr[n-1];
 for (int i=n-1;i>=1;i++){
     arr[i]=arr[i-1];
 }
 arr[0]=tmp;

}
  
}