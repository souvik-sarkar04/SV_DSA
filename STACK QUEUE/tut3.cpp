#include<iostream>
using namespace std;
//IMPLEMENTING STACK USING QUEUES:
// We take 2 queues q1 and q2. 
//Algorithm of push() - 
// 1) Add val to q2
// 2) Add element by element of q1 to q2
// 3) Swap elements of q1 and q2
// ESSENCE: The copying of q1's elements to q2 and then finally swapping the elements of q1 and q2 results in a queue which has elements
//in the REVERSE ORDER as compared to the order the elements would have possessed had they been DIRECTLY PUSHED IN THE QUEUE. 
//This changes the queue's behaviour from FIFO to LIFO as now, if pop() operation is carried out then the LAST INSERTED ELEMENT which is
//present at the TOP OF THE QUEUE because of REVERSE ORDER gets deleted thus implementing stack.
//T.C. O(n) for copying elements of q1 to q2 S.C. nearly O(n) (exactly O(2N))
int main(){

return 0;
}