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

//WORKING
Node *sort012_brute_my(Node *head)
{
    // cout<<"Hi i am in";
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    vector<int> arr;
    Node *temp = head;
    while (temp != NULL)
    {
        // cout<<"Hi i am in loop";
        if (temp->data == 0)
        {
            arr.push_back(temp->data);
            // cout<<"temp->data: "<<temp->data<<" ";
        }
        temp = temp->next; // ALWAYS write this line OUTSIDE IF BLOCK DIRECTLY in LOOP BODY
    }
    Node *temp1 = head;
    while (temp1 != NULL)
    {
        if (temp1->data == 1)
        {
            arr.push_back(temp1->data);
            //  cout<<"temp1->data: "<<temp1->data<<" ";
        }
        temp1 = temp1->next;
    }
    Node *temp2 = head;
    while (temp2 != NULL)
    {
        if (temp2->data == 2)
        {
            arr.push_back(temp2->data);
            //  cout<<"temp2->data: "<<temp2->data<<" ";
        }
        temp2 = temp2->next;
    }
    Node *temp3 = head;
    int i = 0;
    while (temp3 != NULL)
    {
        // cout<<"arr[i]: "<<arr[i]<<" ";
        temp3->data = arr[i];
        i++;
        temp3 = temp3->next;
    }
    return head;
}

//BRUTE FORCE: DATA REPLACEMENT APPROACH
// In the first traversal, we count the number of 0s, 1s and 2s. 
//Next, we apply another traversal and we replace the first nodes of LL by the number of zeroes, then the nodes by number of 1s and the last nodes by number of 2s present.
Node* sort012_brute(Node* head)
{
     if (head == NULL || head->next == NULL)
    {
        return head;
    }
    int count0=0;
    int count1=0;
    int count2=0; //you can DECLARE variables in one line but NOT INITALIZE THEM
    //   cout<<"Count: "<<count0<<" "<<count1<<" "<<count2<<endl;
    Node* temp = head;
    while(temp)
    {
        if(temp->data == 0)
        {
            count0++;
        }
         else if(temp->data == 1)
        {
            count1++;
        }
         else
        {
            count2++;
        }
       
        temp = temp->next;
    }
    // cout<<"Count: "<<count0<<" "<<count1<<" "<<count2<<endl;
    temp = head;
    int i=1; //it is LL, FIRST POSITION is FIRST INDEX
    while(temp)
    {
        if(count0)
        {
            temp->data =0;
            count0--;
        }
        else if(count1)
        {
            temp->data =1;
            count1--;
        }
        else
        {
            temp->data =2;
            count2--;
        }

        //NOTE:
        //Using the VARIABLES DIRECTLY and DECREMENTING THEM until THEY ATTAIN 0 and RENDER IF CONDITION FALSE 
        //is a GOOD ALTERNATIVE than taking counter variable i

        // if(i<=count0)
        // {
        //     temp->data = 0;
        // }
        // else if(i>count0 && i<=count0+count1)
        // {
        //     temp->data = 1;
        // }
        // else{
        //     temp->data =2;
        // }
        // i++;
        temp = temp->next;
    }
    return head;
}

//WORKING
Node *sort012_optimal_my(Node *head)
{
    // cout<<"Hi i am in";
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *temp = head;
    Node *zero;
    Node *one;
    Node *two;
    while (temp)
    {
        if (temp->data == 0)
        {
            zero = temp;
            break;
        }
        temp = temp->next;
    }
    temp = head;
    while (temp)
    {
        if (temp->data == 1)
        {
            one = temp;
            break;
        }
        temp = temp->next;
    }
    temp = head;
    while (temp)
    {
        if (temp->data == 2)
        {
            two = temp;
            break;
        }
        temp = temp->next;
    }

    temp = head;
    Node *zeroHead = zero;
    Node *oneHead = one;
    Node *twoHead = two;

    while (temp)
    {
        if (temp->data == 0 && temp != zero)
        {
            zero->next = temp;
            zero = zero->next;
        }
        if (temp->data == 1 && temp != one)
        {
            one->next = temp;
            one = one->next;
        }
        if (temp->data == 2 && temp != two)
        {
            two->next = temp;
            two = two->next;
        }
        temp = temp->next;
    }
    Node* head1 = zeroHead; /*after MODIFICATIONS in LL, specifying the NEW NODE is PREFERABLE to avoid runtime errors*/
    zero->next = oneHead;
    one->next = twoHead;
    two->next = nullptr;
    return head1;
}

// The Space Complexity has to be optimised so the new approach is to change the links of 0 nodes and link them together and do the same fr 1 nodes and 2 nodes. Then, link the end of 0 list to head of 1 list and so on.
// Also, as we are creating a NEW LIST by MANIPULATING the OLD LIST, so, we use 3 DUMMY NODES, zeroHead, oneHead and twoHead, assign the values -1 and point pointers to them, zero, one, two, respectively.
//We take temp at head of LL and here, it has value 1 so, we assign ONE'S NEXT to TEMP and increment point to the newly assigned node(so that in future, its next can be pointed to the JUST NEXT node which will have value 1) to the ONE LIST. Then, we increment temp.
//T.C. O(n) S.C. O(1)
//CODESTUDIO
Node* sort012_optimal(Node* head)
{
     if (head == NULL || head->next == NULL) //if(!head || !head->next) is an ALTERNATIVE
    {
        return head;
    }
     Node* zeroHead = new Node(-1); // creation of dummyNode
     Node* zero = zeroHead;
     Node* oneHead = new Node(-1);
     Node* one = oneHead;
     Node* twoHead = new Node(-1);
     Node* two = twoHead;
    Node* temp = head;
    while(temp)
    {
        if(temp->data ==0)
        {
           zero->next = temp;
           zero = zero->next;
        }
        if(temp->data ==1)
        {
           one->next = temp;
           one = one->next;
        }
        if(temp->data ==2)
        {
           two->next = temp;
           two = two->next;
        }
        temp = temp->next;
    }
    /*Head of L0 is zeroHead->next, Head of L1 is oneHead->next, Head of L2 is twoHead->next,
    Last of L0 will point to the Head of the list containing 1s and so on. */
    Node* head1 = zeroHead->next;

    // A VERY IMPORTANT EDGECASE
    //If the Original list does not have 0s at all or 1s at all or 2s at all, then 
    //the following 3 lines take care of that. 
    //In the first line, if there are no zeroes then zero stands at zeroHead and it starts pointing to oneHead directly.
    //If there are no 1s also, then the oneHead->next points to nullptr and so twoHead->next is executed and 0s(if exist) connect with 2s.
    //Even if 2s do not exist and twoHead->next points to nullptr, there is NO PROBLEM as then zero->next points to nullptr too and that eventually marks END OF LIST(interpretation of 3rd line also)   
    zero->next = oneHead->next? oneHead->next:twoHead->next;
    one->next = twoHead->next;
    two->next = nullptr; /*this line is VERY IMPORTANT. You need to TERMINATE the NEWLY CREATED LINKED LIST by ASSIGNING ITS LAST NODE to nullptr otherwise the result is INFINITE OUTPUT.*/
    return head1;
}
//ESSENCE:
// Usage of DUMMY NODES helps to reduce the 3 traversals needed to get the HEAD OF THE Lists of 0,1,2 as by creating the dummy nodes
//and then the consequent lists by pointing similar elements to them, we can access the head of each List by writing DUMMYNODE->NEXT and then we can finally get the head of the MODIFIED LIST using the FIRST_DUMMY_NODE->next

int main()
{
    vector<int> arr = {1, 0, 1, 2, 0, 2, 1};
    Node *head = convertArr2LL(arr);
    print(head);
    // cout << endl
    //      << "Updated:";
    // head = sort012_brute_my(head);
    // print(head);
     cout << endl
         << "Updated 1:";
    // head = sort012_brute(head);
    // print(head);
    // cout << endl
    //      << "Updated 2:";
    // head = sort012_optimal_my(head);
    // print(head);
    head = sort012_optimal(head);
    print(head);
    return 0;
}