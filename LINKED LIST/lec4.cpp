#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    Node(int data1, Node *next1, Node *prev1)
    {
        data = data1;
        next = next1;
        prev = prev1;
    }
    Node(int data1)
    {
        data = data1;
        next = nullptr;
        prev = nullptr;
    }
};
Node *convertArr2DLL(vector<int> arr)
{
    Node *head = new Node(arr[0]); // invoking the 2nd constructor
    Node *prev = head;
    for (int i = 1; i <= arr.size() - 1; i++)
    {
        Node *temp = new Node(arr[i], nullptr, prev);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

void print(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
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
//NON-WORKING
Node *reversemy1(Node *head)
{
    Node *temp = head;
int length1 = lengthofLL(head);
 cout << length1;
    cout << endl;
    int i = 1;
    while (i <= length1 && temp != NULL)
    {
        int j = 1;
        Node *temp1 = head;
        // swap(i, length - i + 1);
        Node *front_main = temp->next;
        Node *back_main = temp->prev;
        while (temp1 != NULL && j <= length1)
        {
            Node *front_sub = temp1->next;
            Node *back_sub = temp1->prev;
            if (j == length1 - i + 1)
            {
                temp1->next = front_main;
                front_main->prev = temp1;
                temp->prev = back_sub;
                back_sub->next = temp;
                break;
            }
            j++;
            temp1 = temp1->next;
        }
        temp = temp->next;
        i++;
    }
   
    return head;
}

// void reverse(int a)
// {
//     int s=0, e = length-1;
//     for(int i=0; i<length; i++)
//     {
//         swap(a[s], a[e]);
//         s++;
//         e--;
//     }
// }

//NON-WORKING
Node* reversemy2(Node* head)
{
    Node* start = head;
    Node* end1 = head;
    while(end1->next !=NULL)
    {
         cout<<"Elements:"<<end1->data<<endl;
        end1 = end1->next;
       
    }
    Node* end = end1;
    cout<<end->data<<" "<<start->data<<" "<<endl;
    Node* start2 = head;
    Node* end2 = end;
    while(start2->data!=end2->data)
    {
        
        cout<<"Hello"<<endl;
        Node* end_next = end2->next;
        Node* end_prev = end2->prev;
        Node* start_next = start2->next;
        Node* start_prev = start2->prev;
        start2 = start2->next;
        end2 = end2->prev;
        cout<<"Hi"<<endl;
        // cout<<end_next->data;
        // <<" "<<end_prev->data<<" "<<start_next->data<<" "<<start_prev->data;
        cout<<"Do"<<endl;
        if(start_next->data == end2->data || end_prev->data==start2->data)
        {
            
        //     end->next = end_prev;
        // end->prev = start_prev;
        // start->next = end_next;
        // start->prev = start_next;
        break;
        }
        end->next = start_next;
        end->prev = start_prev;
        start->next = end_next;
        start->prev = end_prev;
        cout<<"Original:"<<start->data<<" "<<end->data<<endl;
        
        cout<<"Final:"<<start->data<<" "<<end->data<<endl;
cout<<"Done"<<endl;
    }

    return head;
}

Node* reverse(Node* head)
{
    Node* start = head;
    Node* end1 = head;
    while(end1->next !=NULL)
    {
         cout<<"Elements:"<<end1->data<<endl;
        end1 = end1->next;
       
    }
    Node* end = end1;
    // cout<<end->data<<" "<<start->data<<" "<<endl;

    while(end!=NULL)
    {
        cout<<end->data<<" ";
        end = end->prev;
    }
    cout<<endl;
    return head;
}

//BRUTE-FORCE
//T.C. - O(2n) because of 2 traversals
//S.C. - O(n) due to external stack, OPTIMISATION OF SPACE COMPELXITY REQUIRED
Node* reverse_main2(Node* head)
{
    //using STACK'S LIFO PRINCIPLE to REVERSE LINKED LIST
    Node* temp = head;
    stack<int> s;
    while(temp!=NULL) //T.C. - O(n)
    {
        s.push(temp->data); //First Element of LL is PUSHED FIRST
        temp = temp->next;
    }
    Node* temp1 = head;
    while(temp1!=NULL) //T.C. - O(n)
    {
        temp1->data = s.top(); //Hence, First element of Linked List will be POPPED LAST and Last element will be POPPED FIRST so Linked list is reversed
        s.pop();
        temp1 = temp1->next;
    }
    return head;
}


//IN SINGLE TRAVERSAL
// T.C. = O(n)
//S.C. = O(1) no extra space used
Node* reverse_main1(Node* head)
{
    if(head==NULL || head->next==NULL)
    {
        return head;
    }
    Node* temp = head;
     Node* last = NULL;
    while(temp!=NULL)
    {
    //     Node* front  = temp->next;
    //     Node* back  = temp->prev;
    //    temp->next = back;
    //    temp->prev = front;

    //OBSERVE THE SWAPPING TECHNIQUE VERY CAREFULLY
    //Here DATA POINTS are NOT SWAPPED but the FORWARD AND BACKWARD LINKS between EACH AND EVERY NODE have been SWAPPED.
    //SWAPPING LINKAGES BETWEEN ELEMENTS is an EFFECTIVE WAY to REVERSE the Linked list.
    //To traverse the entire LL, the 'prev' is called as now the updated 'prev' points to the original forward element
     last = temp->prev;
    temp->prev = temp->next;
    temp->next = last;
    //The above 3 lines have to be explained to interviewer and explain the thought of 3rd variable required to swap LINKS
    temp = temp->prev;
    }
    //Now, the last points to nullptr so its previous node is the NEW HEAD which the Q demands as the final answer
return last->prev;
}
int main()
{

    vector<int> arr = {1, 2, 3, 4};
    Node* head = convertArr2DLL(arr);
    print(head);
    cout << endl;

    // head = reverse(head);
    // print(head);

    head = reverse_main1(head);
    print(head);
    return 0;
}