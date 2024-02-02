#include<iostream>
using namespace std;
//CHARACTER HASHING
int main(){
string s;
cin>>s;

int hash[26] = {0}; //size is 26 due to 26 alphabets
for(int i=0; i<s.length(); i++)
{
    char ch = s[i];
    hash[ch-'a']++;
    //here a is assumed index 0, b is assumed index 1 and so on
    // as 'a'-'a' = 0, 'b'-'a' = 1, 'c'-'a'=2 in ASCII code.
    //The above code having 26 size array works ONLY FOR LOWERCASE CHARACTERS.
    //If string has uppercase characters or other special characters, HASH ARRAY WITH 256 CHARACTERS are required.
    //int hash[256] = {0}; ch-'a' is replaced by ch directly(here, ch AUTOCASTS itself into an integer as the index of hash array).
    //CHARACTER HASHING does not have any limit of size on array, so, ARRAYS are always PREFERRED for CHARACTER HASHING.
}

int q;
cin>>q;
while(q--)
{
    char ch;
    cin>>ch;
    cout<<hash[ch-'a']<<endl;
}
return 0;
}


