int getWinner(char * path)
{
    ifstream file(path);
    int n;
    file>>n;
    string s[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            file>>s[i][j];
        }
    }
    
   
}