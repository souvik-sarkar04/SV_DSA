#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// QUEUE
// FIFO(First In FIrst Out)
// push(4) push(2) push(3) Insertion of elements
// top() gives 4 due to FIFO
//  pop()  removes element from top so it removes 4 due to FIFO
// now, top() gives 2.
// IMPLEMENTATION OF QUEUES USING ARRAYS:
//  point front and rear pointer variables to index 0.
//  Take a count variable as 0. if count<capacity, then push the element by assigning value to a[rear] and then INCREMENT rear by 1 and count by 1.
// If count=capacity, the QUEUE is full and no push operation is carried out.
// Now, the top() element is the FIRST INSERTED ELEMENT, i.e., a[front].
// When we started pushing elements in the queue, we observed that front=rear. So, we should ENSURE that front and rear variables
// DO NOT POINT TO THE SAME INDEX as that will be used to indicate that the QUEUE IS EMPTY.
// pop()- we send the front() pointer ahead(complying with FIFO) and DECREMENT count.
// Now, if we call top(), we get top element using a[front], that is why front was incremented.
//  We observe that as the FIRST ELEMENT has been POPPED, so the FIRST position is EMPTY.
// Now, if we want to push any element into th queue, we observe that even though rear=size but count<capacity, so, there is SCOPE of pushing elements.
// To aid that, we insert element in rear%size index(=0) and then we increment rear. In this way, the first position which was vacant gets utilised.
//  Now, we increment the count by 1 as well. This CIRCULAR ARRAY CONCEPT is achieved using rear%size concept.

// FIFO THROUGH QUEUE:
//  Initially rear and front both point to 0. Now, elemennts are pushed in rear position and rear increments by 1 progressively.
// In this process, front continues to remain at 0th index which means whenever element is popped and a[front] is called,
//  a[front] definitely returns the FIRST ENTERED ELEMENT.

// TRAVERSAL TO PRINT ELEMENTS OF QUEUE:
//  We run a for loop from front index to (rear-1) index. We print i%size index elements
// as the essence is the front can point to some intermediate index of the array and the traversal should start from there. However, elements that are behind front should also be printed
// hence, when rear exceeds the value of size, i%size ensures that the elements behind front index are also printed at the end.

class Queue
{
public:
    int front, rear, count, size;
    vector<int> arr;
    Queue(int capacity)
    {
        front = 0;
        rear = 0;
        count = 0;
        size = capacity;
        arr.resize(capacity);
    }
    void push(int val)
    {
        if (count < size)
        {
            arr[rear%size] = val;
            rear++;
            count++;
        }
        if (count >= size)
        {
            cout << "The queue is full" << endl;
        }
    }
    int pop()
    {
        if (front == rear) //count==0 is ALTERNATIVE CONDITION
        {
            cout << "Queue is empty" << endl;
        }
        else{
        int del = arr[front];
        front++;
        count--;
        return del;
        //ALTERNATIVE CODE:
        // arr[front%n] = -1;
        // front++;
    }
    }
    int top()
    {
        if(front!=rear) //or count==0
        {
            return arr[front%size];
        }
        else
        {
            return -1;
        }
    }
    void traverse()
    {
        for(int i=front; i<rear; i++)
        {
            cout<<arr[i%size]<<" ";
        }
    }
};
int main()
{
Queue ob(10);
ob.push(36);
ob.push(56);
ob.push(32);
ob.push(80);
ob.push(78);
cout<<"pop 1:"<<ob.pop()<<endl;
cout<<"pop 2:"<<ob.pop()<<endl;
cout<<"top 1:"<<ob.top()<<endl;
ob.traverse();
    return 0;
}