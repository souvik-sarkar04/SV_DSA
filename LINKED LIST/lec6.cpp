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

void PrintStack(stack<int> s)
{
    // If stack is empty then return
    if (s.empty())
        return;

    int x = s.top();

    // Pop the top element of the stack
    s.pop();

    // Recursively call the function PrintStack
    PrintStack(s);

    // Print the stack element starting
    // from the bottom
    cout << x << " ";

    // Push the same element onto the stack
    // to preserve the order
    s.push(x);
}

Node *oddEven_my(Node *head)
{
    vector<int> odd;
    vector<int> even;
    Node *temp = head;
    int count = 0;
    while (temp)
    {
        count++;
        if (count % 2 != 0)
        {
            odd.push_back(temp->data);
        }
        else
        {
            even.push_back(temp->data);
        }
        temp = temp->next;
    }
    // cout<<"Print odd:"<<endl;
    // PrintStack(odd);
    // cout<<"Print even:"<<endl;
    // PrintStack(even);
    Node *t1 = head;
    int c1 = 0, os = odd.size();
    while (t1)
    {
        c1++;
        if (c1 <= os)
        {
            t1->data = odd[0];
            odd.erase(odd.begin(), odd.begin() + 1);
        }
        else
        {
            t1->data = even[0];
            even.erase(even.begin(), even.begin() + 1);
        }

        t1 = t1->next;
    }
    cout << endl;
    return head;
}

// BRUTE FORCE SOLUTION

// We start traversing the LL and we JUMP the temp BY 2 PLACES STARTING FROM THE HEAD(ODD INDEX) and we push it in a new VECTOR. T.C. 0(n/2)
// We assign temp to index 2 and we again JUMP IT BY 2 and we JUMP until we reach the LAST NODE (as null->next has no sense).
// REPLACING THE VALUES OF ORIGINAL LL:
// We assign temp at FIRST INDEX of LL and i at 0th INDEX of VECTOR. We traverse both LL and vector
// simultneously using temp and i until temp is NULL and i exceeds length of list and we STOP.

Node *oddEven_brute(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    vector<int> arr;
    Node *temp = head; // we assign temp to 1st index of LL
    // ODD INDEX ELEMENTS PUSHED INTO ARRAY, T.C. = O(n/2)
    while (temp != NULL || temp->next != NULL) // we are doing (temp->next)->next so temp->next cannot be NULL
    {
        arr.push_back(temp->data);
        temp = temp->next->next; // JUMP OF 2 elements
    }
    if (temp) // There is a possibility for ODD LENGTH LL where temp->next = null for LAST(ODD) INDEX hence the element does not get considered
    // so, to push it into the array as a valid element, this block is written
    {
        arr.push_back(temp->data);
    }
    // EVEN INDEX ELEMENTS INSERTION
    temp = head->next;
    while (temp != NULL || temp->next != NULL) // we are doing (temp->next)->next so temp->next cannot be NULL
    {
        // T.C. O(n/2)
        arr.push_back(temp->data);
        temp = temp->next->next;
    }
    if (temp) // There is a possibility for EVEN LENGTH LL where temp->next = null for LAST(EVEN) INDEX hence the element does not get considered
    // so, to push it into the array as a valid element, this block is written
    {
        arr.push_back(temp->data);
    }
    int i = 0;
    temp = head;
    while (temp != NULL)
    {
        // T.C. O(n)
        temp->data = arr[i];
        i++;
        temp = temp->next;
    }
    return head;
}
// T.C. O(2n) S.c. O(n) due to extra array

// The Space Complexity has to be optimised so the new approach is to change the links of odd index nodes and link them together and change the links of even index nodes and link them together
// we place odd pointer at 'head' and even pointer at 'head->next'.
//  To link odd elements among themselves, we specify odd->next = odd->next->next and we move the odd pointer to the newly linked odd index node
// Same procedure is applied on even : we specify even->next = even->next->next and we move the even pointer to the newly linked even index node
// even is at last so we STOP.
// We MEMORIZE the FIRST EVEN INDEX NODE as evenIndex as we need to point the LAST ODD INDEX's next to evenHead.

Node *oddEven_optimal(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *odd = head;
    Node *even = head->next;
    Node *evenHead = head->next;
    // while(odd!=NULL && odd->next!=NULL && even!=NULL && even->next!=NULL)

    // Simultaneously, odd and even linkages are changed and then simultaneously they are also moved forward, so, T.C. = O(n/2)*2 = O(n).
    // odd comes before even so checking even condition suffices
    while (even != NULL && even->next != NULL)
    {
        // even if the LINKED LIST has ODD NUMBER OF ELEMENTS and consequently has last ODD index, still the condition above holds
        // as the LAST ODD INDEX gets linked to its previous odd index BEFORE the updation of even occurs
        // and the condition is checked that the current even element now points to nullptr

        odd->next = odd->next->next;
        // pointing odd to only odd->next suffices as that anyway implies that the new ODD will JUMP 2 PLACES and point to the ORIGINAL odd->next->next
        odd = odd->next;

        even->next = even->next->next;
        // pointing even to only even->next suffices as that anyway implies that the new EVEN will JUMP 2 PLACES and point to the ORIGINAL even->next->next
        even = even->next;
    }
    odd->next = evenHead; // linking last odd index to first even index
    return head;
}

//Check TLE in CODING NINJAS
Node *segregateEvenOdd(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *dummyOdd = new Node(-1);
    Node *dummyEven = new Node(-1);
    Node *odd = dummyOdd;
    Node *even = dummyEven;
    Node *temp = head;

    while (temp && odd && even)
    {
        if ((temp->data) % 2 != 0)
        {
            odd->next = temp;
            cout<<"ODD: "<<odd->data<<endl;
            odd = odd->next;
        }
        else
        {
            even->next = temp;
            cout<<"EVEN: "<<even->data<<endl;
            even = even->next;
        }
        temp = temp->next; //Do not forget
    }
    even->next = dummyOdd->next;
    return dummyEven->next;
    //dummy node has job in linking seperate lists and returning NE WHEAD, not in traversal
}

int main()
{
    vector<int> num1 = {9, 5, 3, 8, 1};
    Node *head1 = convertArr2LL(num1);
    print(head1);
    // head1 = oddEven_my(head1);
    // print(head1);
    // head1 = oddEven_brute(head1);
    // print(head1);
    // head1 = oddEven_optimal(head1);
    // print(head1);
    head1 = segregateEvenOdd(head1);
    print(head1);
    return 0;
}