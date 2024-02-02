#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// Arrays can contain ANY DATAT TYPE(even pair<int>, <int>) but all the elements should be of SAME DATA TYPE
// Declaring array OUTSIDE main() is GLOBAL DECLARATION and all elements in it are ASSIGNED 0.
// ARRAY MAXIMUM SIZE: INSIDE main() : 10^6, GLOBALLY: 10^7
// Array indexing is from 0 to (n-1).
// Array creates 6 blocks in memory and first block is stored in random address 'x', we can predict that a[1] is stored in 'x+1' address and so on, that is corresponding elements are stored in CONTIGUOUS MEMORY LOCATIONS.
// As array cannot be accessed using random addresses, we access its elements using INDEXES.

// In interview, for HARDER problems, first say brute solution, then better(if applicable) and then OPTIMAL(not for EASIER problems).

// LARGEST ELEMENT of array
// BRUTE: SORT array and print LAST element
// T.C. O(nlogn)(for quick and merge sort) S.C. O(1)
int largest_brute(vector<int> arr)
{
    int n = arr.size();
    sort(arr.begin(), arr.end()); // NOTICE THE ITERATORS PASSED INSIDE sort
    return arr[n - 1];
}
// OPTIMAL: ASSUME that FIRST ELEMENT is the largest. We compare ALL ELEMENTS with largest and if it is larger than the value stored in largest, it is ASSIGNED to largest.
// T.C. O(n) S.C. O(1)
void largest_optimal(vector<int> arr)
{
    int max = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    cout << max << endl;
}

void secondLargest_my(vector<int> arr)
{
    int max = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    int n = arr.size(); // store array size BEFOREHAND and then use it as it will be MANIPULATED IN LOOP(Applicable for all variables whose value will be manipulated)
    for (int i = 0; i < n; i++)
    {
        // cout << "SIZE:" << arr.size() << "i:" << i << endl;
        // if (i - arr.size() <= 0)
        // {
        //     cout << "in" << endl;
        //     int p = i - arr.size();
        //     i = i - p - 1;
        // }
        // if(i-arr.size()>0)
        // {
        //     break;
        // }
        arr.erase(find(arr.begin(), arr.end(), max));       // technique to obtain the FIRST OCCURRENCE of max using find() and passing it to erase() to delete it
        if (find(arr.begin(), arr.end(), max) == arr.end()) // if find() does not give any iterator, i.e., if element is ABSENT, it returns arr.end()
        {
            break;
        }
    }

    int smax = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if (smax < arr[i])
        {
            smax = arr[i];
        }
    }
    cout << smax << endl;
}

// T.C. O(nlogn + n), nlogn for sorting, n for WORST CASE traversal in case the secondL is at first index or NOT PRSENT AT ALL
int secondLargest_brute(vector<int> arr)
{
    int n = arr.size();
    sort(arr.begin(), arr.end()); // NOTICE THE ITERATORS PASSED INSIDE sort
    int largest = largest_brute(arr);
    int secondL = -1;                // secondL = -1 as the secondL may not be present at all
    for (int i = n - 2; i >= 0; i--) // leaving the last element(assumed as largest), entire array is traversed and compared with largest
    {
        if (arr[i] != largest)
        {
            secondL = arr[i];
            break;
        }
    }

    return secondL;
}

// BETTER SOLUTION:
//  We do FIRST PASS and find out LARGEST ELEMENT
//  We take sLargest = -1(assuming all positives in array, take sLargest = INT_MIN if there are also negatives in array)
// We compare all elements with sLargest and also check if the array element is largest. If array element is largest, then it is not assigned in sLargest otherwise it is assigned

// T.C. O(n) + O(n) = O(2n)
int secondLargest_better(vector<int> arr)
{
    int largest = largest_brute(arr);
    int sLargest = -1;
    for (int i = 0; i < arr.size(); i++)
    {
        if (sLargest < arr[i] && arr[i] != largest)
        {
            sLargest = arr[i];
        }
    }
    return sLargest;
}

// OPTIMAL APPROACH:
//  We take LARGEST as arr[0] and sLargest = -1(assuming all positives, for negative elements in array, sLargest = INT_MIN)
// Now, we TRAVERSE the array and we check if arr[i] >=largest. If yes, then, we assign a[i] to largest and IMPORTANTLY, we assign largest's INITIAL VALUE to sLargest as logically, if a NEW VALUE becomes largest, the original value of largest becomes the NEW sLargest.
// If now we encounter a situation where a[i] is not greater than largest but is GREATER THAN the CURRENT VALUE of sLargest, then we assign that value to sLargest.
// Values that are lower thsn both largest and sLargest are automatically filtered.

//T.C. O(n)
int secondLargest_optimal(vector<int> arr)
{
    int largest = arr[0], sLargest = -1, smallest = arr[0], sSmallest = INT_MAX;
    for (int i = 1; i < arr.size(); i++) //i=1 as we assume variables for arr[0] and comparisons start from next element
    {
        if (arr[i] > largest) // = is not considered as there can be multiple largest values which will be automatically ignored OTHERWISE on following iterations, it gets assigned to sLargest
        {
            sLargest = largest; //first assign original value of largest to sLargest and then change value of largest
            largest = arr[i];
        }
        else if(arr[i] < largest && arr[i] >sLargest)
        {
            sLargest = arr[i];
        }
        if(arr[i]<smallest)
        {
            sSmallest = smallest;
            smallest = arr[i];
        }
        else if(arr[i]!=smallest && arr[i] <sSmallest)
        {
            sSmallest = arr[i];
        }
    }
    cout<<"second smallest:"<<sSmallest;
    return sLargest;
    // return {sLargest, sSmallest}; vector<int> is the return type
    //ALWAYS GIVE PROPER VARIABLE NAMES IN INTERVIEW
}
bool checkSorted_my(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > arr[i + 1] && i != arr.size() - 1) // i!=arr.size()-1 is IMPORTANT CHECK as i+1 will evaluate to arr.size() OTHERWISE
        {
            return 0;
        }
        // cout<<arr[i]<<" ";
    }
    return 1;
}
bool checkSorted_main(vector<int> arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] >= arr[i - 1]) // consider = as 2 consecutive elements can be equal
        {                         // here CURRENT element is checked with PREVIOUS ELEMENT
            // starting from i=1 also NULLIFIES the condition check whether i+1 can equate arr.size()
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void removeDuplicates_my(vector<int> arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        // cout<<arr[i]<< " "<<arr[i-1]<<endl;
        if (arr[i] == arr[i - 1])
        {
            arr.erase(find(arr.begin(),
                           arr.end(), arr[i]));
            if (find(arr.begin(),
                     arr.end(), arr[i]) == arr.end())
            {
                continue;
            }
        }
    }
    int n1 = arr.size();
    cout << "Print:" << n1 << endl;
    for (int i = 0; i < n1; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Q demands to return length of array having only the UNIQUE ELEMENTS. Here, UNIQUE helps us to recall SET DS. 
//Iterating the array, it will NOT ACCEPT duplicate elements.
//PARTIALLY WORKING, NOT WORKING FOR MULTIPLE DUPLICATE ELEMENTS
//Lets have index variable and point to 0th index of array and put 1ST ELEMENT of set in it. We move index forward and insert eleemnts of set in array and so on.

//T.C. O(nlogn+n), insertion of elements in map ->nlogn, S.C. O(n) due to msp, needs to be OPTIMISED
int removeDuplicates_brute(vector<int> arr)
{
    set<int> st; //declare SET
    for(int i=0; i<arr.size(); i++)
    {
        st.insert(arr[i]);  //INSERTING elements in set
    }
    int index = 0;
    for(auto it:st)
    {
        arr[index] = it; //assigning elements of set(done using ITERATOR) into array
        index++;
    }
    return st.size(); //returning length of SET to show number of unique elements
}

//OPTIMAL APPROACH: TWO POINTER APPROACH(IMPORTANT)(APPLIES IN SORTED ARRAYS)
//Have a pointer i pointing to first element and pointer j to second element. If they are pointing to same element, then j is incremented but
//if they are not equal, then, the place next to first element is replaced by the new element initially pointed by j and now, i points to the second position where the new second element is placed.
//After the entire traversal, we obtain the number of unique elements as (i+1).

//T.C. O(n) S.C. O(1)
int removeDuplicates_optimal(vector<int> arr)
{
    int i=0;
    for(int j=1; j<arr.size(); j++) //j starts from 1 to IGNORE THE 1ST ELEMENT WHICH IS CONSIDERED UNIQUE
    {
        if(arr[j]!=arr[i])
        {
            arr[i+1] = arr[j]; //arr[j] is NOT EQUAL to arr[i] then the NEXT POSITION of i will be occupied by the new element
            i++; //Now, i must point to the new element to keep track of the NUMBER OF UNIQUE ELEMENTS
        }
    }
    return (i+1);
}

int main()
{
    vector<int> arr = {1, 2,2, 3, 4, 5, 5, 5};
    // largest_brute(arr);
    // largest_optimal(arr);
    // secondLargest_my(arr);
    cout << secondLargest_brute(arr);
    cout << secondLargest_better(arr);
    cout << secondLargest_optimal(arr);
    // cout << checkSorted_main(arr);
    cout<<endl;
    cout<<removeDuplicates_brute(arr);
    cout<<removeDuplicates_optimal(arr);
    // print(arr);
    return 0;
}