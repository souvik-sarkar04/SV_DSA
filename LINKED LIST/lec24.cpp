#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node *child;
    Node()
    {
        this->data = 0;
        this->next = nullptr;
        this->child = nullptr;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
        this->child = nullptr;
    }
    Node(int data, Node *next, Node *child)
    {
        this->data = data;
        this->next = next;
        this->child = child;
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

Node *convertArr2LL_vertical(vector<int> &arr)
{
    if (arr.size() == 0) // EDGE CASE
    {
        return NULL;
    }
    Node *head = new Node(arr[0]);
    Node *mover = head; // initally points to 'head', stands at first place now
    for (int i = 1; i < arr.size(); i++)
    {
        Node *temp = new Node(arr[i]);
        mover->child = temp;
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
// Traverse in the BOTTOM direction towards childs and put them in array.
// WORKING(commented portion)

// T.C. Assume n is number of HEAD NODES and assume M is number of child nodes of each head node, so, T.C. = O(N*M)(traversal) + O(XlogX)(x=N*M)(sorting) + O(N*M)(convert_vertical) = O((N*M)*2 + XlogX)
// S.C. O((N*M)*2) (one for array, one for NEW LL)  (NEEDS OPTIMISATION)
Node *flatten_brute(Node *head)
{
    vector<int> arr;
    Node *temp = head;
    while (temp != NULL)
    {
        Node *temp1 = temp;
        while (temp1 != NULL)
        {
            arr.push_back(temp1->data);
            temp1 = temp1->child;
        }
        temp = temp->next;
    }
    sort(arr.begin(), arr.end());
    // Node* dummyNode = new Node(-1);
    // Node* current = dummyNode;
    // for(int i=0; i<arr.size(); i++)
    // {
    //     Node* newNode = new Node(arr[i]);
    //     current->child = newNode;
    //     current = newNode;
    // }
    // ALTERNATIVE: CALL A CONVERT FUNCTION WHICH VERTICALLY ALIGNS THE NODES OF LL

    return convertArr2LL_vertical(arr);
}

Node *merge2LL(Node *head1, Node *head2)
{
    if (head1 == NULL && head2 == NULL)
    {
        return NULL;
    }

    Node *dummyNode = new Node(-1);
    Node *curr = dummyNode;
    Node *temp1 = head1;
    Node *temp2 = head2;
    while (temp1 != NULL && temp2 != NULL) // traversal done till BOTH of them are ACTIVE
    {
        if (temp1->data <= temp2->data)
        {
            curr->child = temp1;
            curr = temp1;
            temp1 = temp1->child;
        }
        else
        {
            curr->child = temp2;
            curr = temp2;
            temp2 = temp2->child;
        }
    }
    if (temp1 != NULL)
    {
        curr->child = temp1;
    }
    if (temp2 != NULL)
    {
        curr->child = temp2;
    }
    return dummyNode->child;
}

Node *flatten_optimal_my(Node *head)
{
    vector<int> arr;
    Node *temp = head;
    while (temp != NULL)
    {
        Node *temp1 = temp->next;
        merge2LL(temp, temp1);
        temp = temp->next->next;
    }
}

// OPTIMISATION:
//  Use the SORTED property, The LL is reused rather than creating new list.
// T.C. O(n1+n2)
Node *merge2LL_vertical(Node *list1, Node *list2)
{
    Node *dummyNode = new Node(-1);
    Node *res = dummyNode;
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data < list2->data)
        {
            res->child = list1;
            res = list1;
            list1 = list1->child;
        }
        else
        {
            res->child = list2;
            res = list2;
            list2 = list2->child;
        }
        res->next = NULL; // elements should be added at CHILD, next should be null
    }
    if (list1 != NULL)
    {
        res->child = list1;
    }
    else
    {
        res->child = list2;
    }
    return dummyNode->child;
}

// CONCEPT OF RECURSION will be used as firstly the last 2 head nodes will be merged into one list and this will act as one list parameter 
//for the future recursion while the other list parameter will be the head node just after this merged list.
// We move head upto the LAST HEAD NODE and then we RETURN the entire node along with the associated sub-list as it is a sorted sub-list. 
//Then, we BACKTRACK and pass it to merge() function and also pass the previous head node and compute their merged list. The BACKTRACKING continues until he FIRST HEAD NODE is passed.

//the flatten_optimal() call sends the head to the last and when head->next==NULL is found then it is returned and then merge_vertical()
//merges the last head node with the previous head node and creates a new head node with its children which gets passed to the PREVIOUS RECURSION CALL 
//where the head of this MODIFIED LIST is merged with the HEAD THAT IS PASSED TO THE RECURSIVE FUNCTION using merge().
//Thus, recursion resolves the problem that was being faced where after MERGING TWO GIVEN HEAD NODES, the procedure to move on was
//not clear, that is achieved by recursion.

//T.C. Assume number of horizontal nodes = n and each head node has m children, so,
//T.C. O(N*merge) = O(N*(M+M))(merge deals with child nodes in both lists) = O(N*2M), S.C. O(N)(Recursive stack space)
Node *flatten_optimal(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *mergedHead = flatten_optimal(head->next);
    return merge2LL_vertical(head, mergedHead);
}
int main()
{

    return 0;
}
