/* Dynamic allocation*/
int main ()
{
    int i,n;
    int * p;
    cout << "How many numbers would you like to type? ";
    cin >> n;
    p= new (nothrow) int[n];
    if (p == nullptr)
        cout << "Error: memory could not be allocated";
    else
    {
        for (i=0; i<n; i++)
        {
            cout << "Enter number: ";
            cin >> p[i];
        }
        cout << "You have entered: ";
        for (i=0; i<n; i++){
            cout << p[i];
            if(i < n-1)
                    cout << ", ";
        }
        delete[] p;
    }
    return 0;
}
