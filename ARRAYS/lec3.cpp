#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int missingNumber(vector<int> arr, int n)
{
    int hash[n+1] = {0};
    for (int i = 0; i < arr.size(); i++)
    {
        hash[arr[i]]++;
    }
    for (int i = 1; i < n+1; i++)
    {
        if (hash[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

int consecutiveOnes(vector<int> &a)
{
    int cnt = 1;
    vector<int> c;
    for(int i=0; i<a.size(); i++)
	{
        if(a[i] == 1 && a[i+1] == 1)
        {
            cnt++;
        }
        else{
            c.push_back(cnt);
            cnt=1;
        }
    }
    int max = c[0];
    for(int i=0; i<c.size(); i++)
	{
        if(c[i]>max)
        {
            max = c[i];
        }
    }
    return max;
}
int getSingleElement(vector<int> &a){
	// Write your code here.
	int max = a[0];
	for(int i=0; i<a.size(); i++)
	{
		if(max<a[i])
		{
			max = a[i];
		}
	}
	int hash[max+1]={0};//whenever some UPDATION in Array values is to be done, it should FIRST be INITALIZED to 0
	for(int i=0; i<a.size(); i++)
	{
		hash[a[i]]++;
	}
    for(int i=0; i<=max; i++)
	{
    }
	for(int i=0; i<=max; i++)
	{
		if(hash[i] == 1)
		{
			return i;
		}
	}	
}
void setZeros(vector<vector<int>> &a)
{
	// Write your code here.
    int cnt=0;
	for(int i=0; i<a.size(); i++)
	{
		for(int j=0; j<a[0].size(); j++)
		{
			if(a[i][j]==0)
			{
				for(int k=0; k<a[0].size(); k++)
				{
					a[i][k]=0;
				}
				for(int l=0; l<a.size(); l++)
				{
					a[l][j]=0;
				}
                cnt=1;
                break;
			}
		}
        if(cnt==1)
        {
            break;
        }
	}
    for(int i=0; i<a.size(); i++)
	{
		for(int j=0; j<a[0].size(); j++)
		{
            cout<<a[i][j]<< " ";
        }
        cout<<endl;
    }
}
int main()
{
    vector<int> arr = {1, 2, 3,4,6,7,8};    
    vector<int> arr1 = {1, 1,2,2,3,4,4,5,5};    
    vector<int> arr2 = {0,1,1,0,0,1,1,1,1, 0, 1,1};    
vector<vector<int>> vect 
    { 
        /* Element one with 2 values in it. */
        {1, 2,3},  
        
        /* Element two with 3 values in it. */
        {4, 0, 6},  
        
         /* Element three with 4 values in it. */
        {7, 8, 9}  
    }; 
    cout << missingNumber(arr, 8);
    cout<<endl;
    cout << getSingleElement(arr1);
    cout<<endl;
    cout << consecutiveOnes(arr2);
    cout<<endl;
    setZeros(vect);
    return 0;
}