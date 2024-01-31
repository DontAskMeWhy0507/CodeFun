string pigLatin(string word){
   // int len=word.length();
    string s;
    if (s[0]=='u'||s[0]=='e'||s[0]=='o'||s[0]=='a'||s[0]=='i')
    {
        s=s+word;
      s+=  "way";
    }
 /*   else
    {
    for (int i=1; i<len; i++)
    {
        s=s+s[i];
    }
    s=s+word[0]+"ay";
} */

 return s;   
}