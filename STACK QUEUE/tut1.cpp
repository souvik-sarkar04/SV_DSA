#include<iostream>
#include <bits/stdc++.h>
using namespace std;
//STACK:
// LIFO(Last In First Out) principle 
//Push: push(6) -> entering value 6 in stack
//top()- returns the topmost element
//pop()- deletes TOPMOST element
//Implementation using arrays:
// Consider an array of 5 elements. We take top variable as -1 and when any element is PUSHED, we INCREMENT top to 0 and put value in a[top].
//Again, if value is pushed, top is incremented and value is inserted in a[top]. In this way, we get stack as 6,3,7(say).
// Now, if top() is called, we can simply return a[top] which is currently 7. 
//Now, if pop() is called, the topmost element is DELETED so top is DECREMENTED by 1.
//top() now returns 3.
//calling size() will give size of stack so it should be (top+1) (as now, top points to 1st index and size of stack is 2).
//empty()- checks if stack is empty, confirmed if top=-1.

// Stack class.
//PERFECTLY WORKING STACK IMPLEMENTATION THROUGH ARRAYS
class Stack {
    
public:
    int top_index, size;
    vector<int> a;
    Stack(int capacity) {
        // Write your code here.
        top_index=-1; //Initially stack is EMPTY 
        size=capacity;
        // cout<<"capacity:"<<size;
        a.resize(size);
    }

//EDGE CASES in each of the functions are IMPORTANT otherwise undesirable output is obtained
    void push(int num) {
        // Write your code here.
        top_index = top_index+1; //initially top_index is -1 so it needs to be incremented to 0 atleast for entry of elements
        
        
        if(top_index!=size) //When index = size of array, then NO MORE ELEMENTS CAN BE PUSHED
        {
            a[top_index] = num;
        }
        else
        {
            top_index = top_index-1; //This line is IMPORTANT as top_index leaves this method with the VALUE 'size' and that creates problems 
            //to POP elements
            return;
        }
    }

    int pop() {
        // Write your code here.
        if(top_index!=-1)
        {
        int del = a[top_index];
        top_index = top_index-1; //by decrementing top, we remove the topmost element from stack
        return del;
        }
        else{
            return -1;
        }
    }
    
    int top() {
        // Write your code here.
        if(top_index!=-1)
        {
        return a[top_index];
    }
    else
    {
        return -1;
    }
    }
    
    int isEmpty() {
        // Write your code here.
        if(top_index==-1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    int isFull() {
        // Write your code here.
        // cout<<"size:"<<size;
        // cout<<"top:"<<top_index;
        if(top_index!=size)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    
};

int main(){

return 0;
}