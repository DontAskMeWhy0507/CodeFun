bool areAnagrams(string str1,string str2){
 int len1 = str1.length();
 int len2 = str2.length();
 
 for( int i = 0; i<len1; ++i) str1[i]=tolower(str1[i]);
 for( int i = 0; i<len2; ++i) str2[i]=tolower(str2[i]);
 int a[26];
 fill_n(a,26,0);  //memset
 for( auto ch:str1) {a[ch-'a']++;}
for( auto ch:str2) {a[ch-'a']--;}
 for (int i=0;i<26;++i)
  {if(a[i]) return false;}
  
  return false;
}