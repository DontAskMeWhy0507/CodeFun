
/*Thầy Long viết n bài báo  khoa học, mỗi bài báo của thầy Long được một số người đọc và trích dẫn tham khảo. 
 Mức độ ảnh hưởng của các nhà khoa học có thể được đánh gia thông qua chỉ số h-index. 
 Chỉ số h-index càng cao, thì mức độ ảnh hưởng càng cao.  Chỉ số h-index của một nhà khoa học là k
 nếu như nhà khoa học đó có ít nhât k bài báo, mà mỗi bài báo được trích dẫn ít nhất k lần.  
 Cho một dãy n số biểu diễn số lần các bài báo khoa học của thầy Long được trích dẫn, 
 bạn hãy viết chương trình tính chỉ số h-index lớn nhất của thầy Long nhé. */
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n];
    for (int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    int ans = 0;
    for(int i = 0; i<n;i++)
    {
        int tmp = min((n-i),a[i]);
        if(tmp>ans)ans = tmp;
    }
        cout<<ans;
}