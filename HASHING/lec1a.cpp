#include<iostream>
using namespace std;
//We are given an array: 1,2,1,3,2. 1 appears 2 times in the array, 3 appears 1 time in the array, 4 appears 0 times,
//2 appears 2 times. (VERY IMPORTANT) Any number can be asked that HOW MANY TIMES IT APPEARS IN THE ARRAY. 
//1st Approach: ITERATION(BRUTE FORCE)
//T.C. O(n) for counting frequency of each number, let frequencies of 'q' numbers are to be calculated, so, T.C. O(qn)
//Let q and n be of order 10^5. So, T.C. = O(10^10), WE KNOW 10^8 OPERATIONS TAKES 1 SECOND TO RUN, 10^10 operations will take 100s(huge)

int count(int a[], int n, int num)
{
    int cnt = 0;
    for(int i=0; i<n; i++)
    {
        if(a[i]==num)
        {
            cnt++;
        }
        return cnt;
    }
}

//The above procedure can be SIMPLIFIED using HASHING.
//HASHING means PRESTORING DATA and FETCHING THEM WHEN REQUIRED.
//A HASH ARRAY(HA)/FREQUENCY ARRAY of size 13 is taken and ALL elements are assigned 0.
//We will do some PRE-CALCULATION.
//We start the traversal, we encounter 1 so we go to hash array and increment value of a[1] to 1,
// we encounter 2, so we increment value of HA's a[2] to 1, we encounter 1, so we increment HA's a[1] to 2. 
// We encounter 3, so we increment value of HA's a[3] = 1. We encounter 2, so we increment a[2] to 2.
//The ABOVE PRE-STORING SIGNIFIES that the indexes of HASH ARRAY signify the ACTUAL VALUES and the values contined by these indexes are the actual frequencies.
// We get frequency of 1 as hash[1], for 3 we get hash[3] and so on.
//This procedure is called NUMBER HASHING.

int main(){

int n;
cin>>n;
int arr[n];
for(int i=0; i<n; i++)
{
    cin>>arr[i];
}

//precompute
int hash[13] = {0};
for(int i=0; i<n; i++)
{
    hash[arr[i]] +=1; //IMPORTANT, VALUE of arr[i] serves as INDEX of HASH ARRAY
}
int q;
cin>>q;
while(q--)
{
    int number;
    cin>>number;
    
//fetch
cout<<hash[number]<<endl;
}
//If HASH ARRAY is declared INSIDE MAIN, then its MAXIMUM SIZE is 10^6.
//If HASH ARRAY is declared GLOBALLY, then its MAXIMUM SIZE is 10^7.
//The above values are for INT arrays, for boolean, it is 10^7 INSIDE MAIN and 10^8 GLOBALLY.
return 0;
}