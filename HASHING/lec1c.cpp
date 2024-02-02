#include<iostream>
#include <bits/stdc++.h>
using namespace std;
//STL Map and unordered map solves the problem of number hashing in C++.
//MAP
//An array is given: 1,2,3,1,3,2
//Map is a data structure which has key:value pairs where the key is the number and the value is the number's frequency(in number hashing).
// if we get 1 in the array, we go to map and see 1 does not exist in array so mpp[1]++ occurs and now 1->1 is created where 1 is key and corresponding vlue is 1. 
//We get 2 in array, 2->1 is created where 2 is key and 1 is corresponding value 
//We get 3 in array, 3->1 is created where 3 is key and 1 is corresponding value 
//We get 1 in array, 1->2 is created where 1 is key and 2 is corresponding value 
//We get 2 in array, 2->2 is created where 2 is key and 2 is corresponding value 
// So, effectively mpp[arr[i]]++ is to be done.
//In array hashing, a size 13 is declared for 12 elements while map occupies LESSER MEMORY.
int main(){
int n;
cin>>n;
int arr[n];
for(int i=0; i<n; i++)
{
    cin>>arr[i];
}

//pre-compute
// Create a map of integers to integers
map<int, int> mpp;
//map stores KEYS in sorted order
for(int i=0; i<n; i++)
{
    mpp[arr[i]]++;
}

//METHOD OF ITERATING IN MAP
for(auto it:mpp)
{
    cout<<it.first<<"->"<<it.second<<endl;
}

int q;
cin>>q;
while(q--)
{
    int number;
    cin>>number;
    //fetch
    cout<<mpp[number]<<endl;
}
return 0;
} 

//use map<char,int> for CHARACTER HASHING, what you want to HASH : KEY, what you want to STORE: VALUE

//TIME COMPLEXITY OF MAP:
// both the storing and fetching of elements in map in best,average and worst case takes logN time, where N is the number of elements in the map

//Unordered map: When we print its key:value pairs, the order of key:value pairs is CHANGING.
// TIME COMPLEXITY in BEST and AVERAGE CASE is O(1)(constant time) and for WORST CASE, it takes O(n).
//FIRST PREFERENCE: UNORDERED MAP as WORST CASE COMPLEXITY OCCURS VERY RARELY.
//If it gives TLE, we use normal map.

//Map is created using DIVISION method, FOLDING method and MID SQUARE method.

//DIVISION METHOD: Say, for hashing an array: 2,5,16,28,139 , we cannot use an array of size greater than 10.
// We see that this array has indexes from 0 to 9. This fact is used as we take MODULO of each number and we correspond the result with the indexes of hash array and increment the values contained in it. 
//Retrieving is done like 139%10 = 9 and index 9 in hash array has value 1 so it occurs once.
// But now the QUESTION is if number%10 gives the SAME VALUE for MULTIPLE NUMBERS? 
// We now take an array : 2,5,16,28,139,38,48,28,18 
// 0
// 1
// 2->2
// 3
// 4
// 5->5
// 6
// 7
// 8->28->38->48
// 9->139
//LINEAR CHAINING occurs(with the help of LINKED LIST) when multiple numbers give same modulo and when same number comes back, like 28, then it gets linked with previous 28 and then new 28 links with 38 and breaks the link between previous 28 and 38.
//This is done to store MANY VALUES in LIMITED MEMORY.

//COLLISIONS mean the KEYS are stored in SAME HASH INDEX(like values are 18,28,38,...,1008) and here, TLE occurs which is VERY RARE.

//key can be ANY DATA STRUCTURE in a MAP, even pair<int,int>
//key in UNORDERED MAP CANNOT be pair<int,int>