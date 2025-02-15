// Pointer array 1 demension
int * getPointerToArray(int n)
{
    int *arr;
    arr = new int [n];   
    for (int i = 0; i < n; i++)
    {
        cin >> *(arr+i);
    }
    return arr;
}

// Pointer array 2 demension
int ** getPointerToArray2D(int n, int m)
{
    int **arr = new int *[n];   // or int **arr = (int **)malloc(n*sizeof(int *)); 
    for (int i = 0; i < n; i++)
    {   
        arr[i] = new int [m];       // or arr[i] = (int *)malloc(m*sizeof(int));
        for (int j = 0; j < m; j++)
        {
            cin >> *(*(arr+i)+j);
        }
    }
    return arr;
}

// Có 3 loại cấp phát bộ nhớ cho c++:
// 1. Cấp phát bộ nhớ tĩnh (Static memory allocation) - Cấp phát bộ nhớ tĩnh khi biên dịch chương trình. vd: int a[100];
// 2. Cấp phát bộ nhớ động (Dynamic memory allocation) - Cấp phát bộ nhớ động khi chương trình đang chạy. vd: int *a = new int[100];    
// 3. Cấp phát bộ nhớ tĩnh (Automatic memory allocation) - Cấp phát bộ nhớ tự động khi chương trình đang chạy. vd: int a;
