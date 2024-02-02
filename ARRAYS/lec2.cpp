#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// WORKING
void leftRotateOne(vector<int> arr)
{
    int n = arr.size();
    int t = arr[n - 1];
    arr[n - 1] = arr[0];
    for (int i = 0; i < n - 2; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[n - 2] = t;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

// T.C. O(n) S.C. O(1)(NO EXTRA space, SPACE for ALGORITHM - O(n) for the array supplied)
void leftRotateOne_main(vector<int> arr)
{
    int n = arr.size();
    int temp = arr[0]; // storing the 1st element so that its value is not lost
    for (int i = 1; i < n; i++)
    {
        arr[i - 1] = arr[i]; // LEFT ELEMENTS are assigned the value placed just to their RIGHT
    }
    arr[n - 1] = temp; // LAST ELEMENT is assigned the VALUE of ORIGINAL FIRST ELEMENT
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}
void leftRotateD(vector<int> arr, int d)
{
    int n = arr.size();
    int t = arr[n - d];
    arr[n - 1] = t;
    for (int i = 0; i < n - 2; i++)
    {
        if (i + d < arr.size())
        {
            arr[i] = arr[i + d];
        }
    }
    arr[n - 2] = t;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

void moveZeroes(vector<int> arr)
{
    int n = arr.size() - 1;
    int s = 0, e = n;
    while (s <= e)
    {
        if (arr[s] == 0 && arr[e] != 0)
        {
            swap(arr[s], arr[e]);
            s++;
            e--;
        }
        else if (arr[s] == 0 && arr[e] == 0)
        {
            e--;
        }
        else
        {
            s++;
        }
        cout<<"s: "<<s<<" e: "<<e<<endl;
    }
    for (int i = 0; i <=n; i++)
    {
        cout << arr[i] << " ";
    }
}
void moveZeroes_main(vector<int> arr)
{
    int n = arr.size() - 1;
    int s = 0, e =1;
    for (int i = 0; i < n; i++)
    {
        // cout<<"arr[i]:"<<arr[i]<<" ";
        // if (arr[i] == 0 && i<n)
        // {
        //     cout<<"i: "<<i<<endl;
        //     swap(arr[i], arr[i + 1]);
        // }
    
     if (arr[s] == 0 && arr[e] != 0)
        {
            swap(arr[s], arr[e]);
            s++;
            e++;
        }
        else if (arr[s] == 0 && arr[e] == 0)
        {
            e++;
        }
        else
        {
            s++;
            e++;
        }
    }
    for (int i = 0; i <=n; i++)
    {
        cout << arr[i] << " ";
    }
}
int linear_search(vector<int> arr, int num)
{
    int n = arr.size() - 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == num)
        {
            return i;
        }
    }
    return -1; // in case the element is NOT FOUND
}

// WORKING
// BRUTE FORCE: elements are in SORTED order and also UNIQUE in the union array so that reminds us of SET
// do not use UNSORTED SET as we need SORTED ORDER of UNION ELEMENTS
// O(n1logn + n2logn + (n1+n2))(n1,n2 are elements of a and b, n1+n2 is due to the fact if all elements are unique in a and b), SC O(n1+n2)(set with all unique elements WORST CASE) + O(n1+n2)(to return answer, the vector is used)
void union_arrays(vector<int> a, vector<int> b)
{
    set<int> st;
    for (int i = 0; i < a.size(); i++)
    {
        st.insert(a[i]);
    }
    for (int i = 0; i < b.size(); i++)
    {
        st.insert(b[i]);
    }
    vector<int> c(st.size()); // it is assigned SET'S SIZE as that will give the number of UNIQUE UNION ELEMENTS
    int index = 0;
    for (auto it : st)
    {
        c[index] = it; // or c[index++] = it;
        index++;
        // c.push_back(it);
    }
    for (int i = c.size() - 1; i >= 0; i--)
    {
        if (c[i] == 0)
        {
            c.pop_back();
        }
        else
        {
            break;
        }
    }
    for (int i = 0; i < c.size(); i++)
    {
        cout << c[i] << " ";
    }
}

// ARRAYS ARE SORTED --> TWO POINTER APPROACH is the OPTIMAL APPROACH
// i pointer is kept on FIRST ELEMENT of FIRST ARRAY
// j pointer is kept on FIRST ELEMENT of SECOND ARRAY
// We take an extra union array and its first element will be SMALLEST among all union elements
// SO, we COMPARE elements pointed at by i and j
// Suppose if a[i]<=b[j], we assign union's 1st element as a[i] and move i pointer to NEXT INDEX of array a
// We again compare a[i] and b[j] but now, if the smaller element among the 2 is a PART OF THE UNION ARRAY, then, it is IGNORED and i is again incremented
// In case of comparison, if b[j]>=a[i], we assign b[j] to union array and increment j, however, if b[j] is already PART OF UNION ARRAY, it is IGNORED and j is again incremented
//  If iteration of ONE OF THE ARRAYS IS OVER, then, we check if the REMAINING ELEMENTS of the SECOND ARRAY is a part of uion. If not, they are made a part of union.

// T.C. O(n1+n2) as we iterate through all elements of both arrays, S.C. = O(n1+n2)(WORST CASE if all elements are UNIQUE and it is just for returning, it is NOT EXTRA SPACE)
void sortedArray(vector<int> a, vector<int> b)
{
    int n1 = a.size();
    int n2 = b.size();
    int i = 0;
    int j = 0;
    vector<int> unionArr;
    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
        {
            if (unionArr.size() == 0 || unionArr.back() != a[i]) // size=0 is considered as when union aray is EMPTY, element is ALWAYS PUSHED in it
            {
                unionArr.push_back(a[i]);
            }
            i++;
        }
        else
        {
            if (unionArr.size() == 0 || unionArr.back() != b[j]) // size=0 is considered as when union aray is EMPTY, element is ALWAYS PUSHED in it
            {
                unionArr.push_back(b[j]);
            }
            j++;
        }
    }
    // ELEMENTS OF NON-EXHAUSTED ARRAY ARE ITERATED AND CHECKED WITH UNION ARRAY AND PUSHED IF NOT A PART OF UNION ARRAY
    while (j < n2)
    {
        if (unionArr.size() == 0 || unionArr.back() != b[j]) // size=0 is considered as when union aray is EMPTY, element is ALWAYS PUSHED in it
        {
            unionArr.push_back(b[j]);
        }
        j++;
    }
    while (i < n1)
    {
        if (unionArr.size() == 0 || unionArr.back() != a[i]) // size=0 is considered as when union aray is EMPTY, element is ALWAYS PUSHED in it
        {
            unionArr.push_back(a[i]);
        }
        i++;
    }
    for (int i = 0; i < unionArr.size(); i++)
    {
        cout << unionArr[i] << " ";
    }
}

// BRUTE FORCE: We will pick up 1 element in first array and checking entire second array and also keeping track whether it has already been taken
// Taking a visitor array having all zeroes. Once iteration in ANY ONE ARRAY is completed, intersection is obtained.

// T.C. O(n1*n2) S.C. O(n2)/O(n1) due to visitor array and depending on which array the visitor array corresponds to
// Generally, visitor array should CORRESPOND TO SMALLER ARRAY to REDUCE S.C.
void intersectionArray(vector<int> a, vector<int> b)
{
    int n1 = a.size();
    int n2 = b.size();
    vector<int> visitor(n2);
    // visitor array corresponds to the ELEMENTS OF SECOND ARRAY. Now, if we encounter an element which is considered in intersection, then corresponding to ITS INDEX IN SECOND ARRAY, the index of visitor array will also have value 1 and that will TERMINATE THE ENTRY OF DUPLICATE INTERSECTION VALUES
    // ESSENCE: Whenever there is a need to keep track WHETHER A PARTICULAR ELEMENT OF AN ARRAY IS CONSIDERED IN THE OUTPUT OR NOT, an array like visitor array helps to KEEP TRACK
    vector<int> ans(n2);
    fill(visitor.begin(), visitor.end(), 0);
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (a[i] == b[j] && visitor[j] == 0)
            {
                ans.push_back(a[i]);
                visitor[j] = 1;
                break;
            }
            if (b[j] > a[i])
            {
                break;
            }
        }
    }
}

// 2 ARRAYS ARE SORTED -> TWO POINTER APPROACH
//  i pointer is kept on FIRST ELEMENT of FIRST ARRAY
//  j pointer is kept on FIRST ELEMENT of SECOND ARRAY
//  if elements do not match and if a[i]<b[j], i should move forward to have chance of having intersection with element corresponded by j
// vice versa for j
// If they match, we put that in empty array and increment both pointers
// when any one of the pointers EXCEEDS THE LENGTH of the array, the intersection is obtained

// T.C. O(n1+n2) if in distinct steps, only 1 pointer moves and 2 pointers DO NOT MOVE simultaneously(WORST CASE)
// S.C. O(1), WORST CSE O(n1+n2) to store ans and return, not an EXTRA SPACE
void intersectionArray_optimal(vector<int> a, vector<int> b)
{
    int n1 = a.size();
    int n2 = b.size();
    int i = 0;
    int j = 0;
    vector<int> unionArr;
    while (i < n1 && j < n2)
    {
        if (a[i] < b[j])
        {
            i++;
        }
        else if (b[j] < a[i])
        {
            j++;
        }
        else
        {
            unionArr.push_back(b[j]);
            i++;
            j++;
        }
    }
    for (int i = 0; i < unionArr.size(); i++)
    {
        cout << unionArr[i] << " ";
    }
}


void rotate(vector<int>& arr, int n) {
    // Write your code here
    // int n = arr.size();
    int t = arr[0];
    arr[0] = arr[n-1];
    for (int i = 2; i < n; i++)
    {
        int q = arr[i];
        arr[i] = arr[i -1];
    }
    arr[1] = t;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}


int main()
{
    vector<int> arr = {1, 2, 3, 3, 4, 5, 6};
    vector<int> arr1 = {1,0,2,3,2,0,0,4,5,1};
    // leftRotateOne(arr);
    leftRotateOne_main(arr);
    // leftRotateD(arr,3);
    cout << endl;
    moveZeroes(arr1);
    cout << endl;
    cout << "Move zeroes:" << endl;
    moveZeroes_main(arr1);
    cout<<endl;
    cout << linear_search(arr, 3);
    cout << endl;
    cout << "Union:" << endl;
    union_arrays(arr, arr1);
    sortedArray(arr, arr1);
    intersectionArray_optimal(arr, arr1);
    cout<<endl;
    rotate(arr,7);
    return 0;
}