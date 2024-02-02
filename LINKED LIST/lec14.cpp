#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        this->data = 0;
        this->next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

Node *convertArr2LL(vector<int> &arr)
{
    Node *head = new Node(arr[0]);
    Node *mover = head; // initally points to 'head', stands at first place now
    for (int i = 1; i < arr.size(); i++)
    {
        Node *temp = new Node(arr[i]);
        mover->next = temp;
        mover = temp; // we can also write mover = mover->next;
    }
    return head;
}

void print(Node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
int length = 0;
int lengthofLL(Node *head) // head is always provided as parameter
{
    // Copy paste the traversal and increment count to get length

    Node *temp = head; // head stored in a new pointer 'temp' so that head is NOT TAMPERED
    while (temp)       // while temp!=null or while temp is valid
    {
        length++;
        temp = temp->next; // temp->next means sending temp to point to next node
    }
    return length;
}

// If there exists a MINIMUM OF 1 NODE where we START AND WE RETURN BACK TO IT in a cycle, we say LL has a loop.
bool detectCycle(Node* head)
{
    cout<<"in";
   if(head==NULL || head->next == NULL)
   {
    return 0;
   } 
   //Thee entire following code is BASELESS as the LL with a loop will alwyas give INFINITE LENGTH on calculation with traversal

//    cout<<"in1";
//    int cnt=0;
//    Node* temp = head;
//    Node* temp1 = head;
//     cout<<"in2";
//     cout<<temp->data<<" "<<temp1->data<<endl;
//     while(temp1!=NULL)
//     {
//         cnt++;
//         cout<<"Length:"<<cnt<<endl;
//         temp1 = temp1->next;
//     }
// //    int l = lengthofLL(temp);
  
//    cout<<"Length:"<<cnt;
//    while(cnt-1!=0)
//    {
//     cout<<temp->data<<endl;
//     temp = temp->next;
//     cnt--;
//    }
//    if(temp->next!=NULL)
//    {
//     return 1;
//    }
//    return 0;
//As in a loop, an element has a pointer EMERGING and a pointer ENTERING into it so it is visited MORE THAN ONCE. 
//So, we realise that we need to MEMORISE that we have SEEN IT BEFORE during traversal

vector<int> arr(10001);
Node* temp = head;
int p;
while(temp)
{
    arr[temp->data]++;
    if(arr[temp->data]>=2)
    {
        return 1;
    }
    temp = temp->next;
}
return 0;
}

//HASHING APPROACH
// T.C. O(n*2*logn), logn comes from map, 2 comes from 2 operations, finding and inserting
//S.C. O(n) It is to be OPTIMISED
bool Cycle_brute(Node* head)
{
    map<Node*,int> mpp; //TECHNIQUE to DECLARE MAP
    Node* temp = head;
    while(temp!=NULL)
    {
        if(mpp.find(temp)!=mpp.end()) //This is the way to CHECK if an element is FOUND in the map or not
        {
            return 1;
        }
        mpp[temp] = 1; //This is the way to INSERT ELEMENTS(here, NODE) in map
        temp = temp->next;
    }
    return 0; //FOR A LINEAR LL, the loop terminates at NULL and executes this line which signifies that there is NO LOOP
}

//OPTIMAL APPROACH: TORTOISE AND HARE ALGORITHM
//WHY does this algorithm work for DETECTING LOOP IN LL?
//When fast and slow start moving, they have 0 SEPERATION. with each TRAVERSAL, the SEPERATION INCREASES as 1,2,3,4,etc.
//What a LOOP does is if the length of the loop is n, then on the (n+1)th traversal, when the slow and fast pointers should
//IDEALLY have n SEPERATION, the loop brings both of them on the SAME NODE as the LOOP'S SIZE is n.

//INTUITION: Loop is of 7 length. After entering loop, slow and fast have seperation d(say,5).
//After moving by one(slow) and two(fast) steps, now it is (d-1)(say,4). The REDUCTION in distance is 1 as fast is moving TOWARDS SLOW by 2 STEPS and slow is moving AWAY FROM FAST by 1 STEP, so, overall reduction in distance is 1.
//In EACH FOLLOWING TRAVERSAL, THIS SEPERATION D deceases to d-1, d-2, until it is 0 at a common node.
//Because the DIFFERENCE IN DISTANCE is 1, so the decremented value of d IS BOUND TO REACH 0. Any other difference in distance other than 1 does not guarantee the d to decrement to 0.

//T.C. O(n) S.C. O(1)
bool detectCycle_optimal(Node* head)
{
    Node* slow = head;
    Node* fast = head;
    while(fast!=NULL && fast->next!=NULL)
    //fast->next!=NULL(reaching LAST NODE is STOPPING condition of ODD length
    //fast!=NULL(reaching NULL is STOPPING condition of EVEN length ))
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast)
        {
            return 1;
        }
    }
    return 0;
}


int main()
{
    vector<int> arr = {1,2,3};
    Node* head = convertArr2LL(arr);
    print(head);
    int l = lengthofLL(head);
   cout<<"Length:"<<l;
    cout<<endl;
    head->next->next->next = head;
   cout<<"loop:"<<endl;
    cout<< head->next->next->next->data;
    if(Cycle_brute(head))
    {
        cout<<"LOOP EXISTS"<<endl;
    }
   else
    {
        cout<<"LOOP does not EXIST"<<endl;
    }
    cout<<detectCycle_optimal(head);
}