#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    Node(int data1, Node *next1, Node *back1)
    {
        data = data1;
        next = next1;
        prev = back1;
    }
    Node(int data1)
    {
        data = data1;
        next = nullptr;
        prev = nullptr;
    }
};

// CODESTUDIO
Node *convertArr2DLL(vector<int> arr)
{
    // Node* head = new Node(head,nullptr, nullptr); //invoking the 1st constructor
    Node *head = new Node(arr[0]); // invoking the 2nd constructor
    Node *prev = head;
    for (int i = 1; i <= arr.size() - 1; i++)
    {
        Node *temp = new Node(arr[i], nullptr, prev); // 1st constructor is invoked to signify that next points to nullptr and back points to prev of arr[i]
        prev->next = temp;                            /*here, initially, the prev's next was pointing to null since it was created. This line instructs it to point to temp so that prev's next can be currently temp.*/
        prev = temp;                                  /*or prev = prev->next; here, the linking of prev and temp is done, hence, to MOVE FORWARD and make 'temp' the 'prev' of the next iteration, temp is assigned to prev.
                                          This step also serves the purpose in the next iteraton's FIRST LINE where the new NODE created will have its back pointed to its prev.*/
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

// WORKING
void findPairs(Node *head, int sum)
{
    if (head == NULL || head->next == NULL)
    {
        cout << "There is no such pair" << endl;
    }
    int cnt = 0;
    Node *temp1 = head;
    while (temp1->next != NULL)
    {
        temp1 = temp1->next;
    }
    Node *end = temp1;
    Node *temp = head;
    while (temp != NULL || end != NULL)
    {
        if (temp->data + end->data == sum)
        {
            cout << temp->data << "+" << end->data << ",";
            // Once the PAIR SUM is obtained, it is IMPORTANT to shift the start(here, temp) to the NEXT ELEMENT for its pair to be identified and shift the end to the last node of the LL so that pairs can be found.
            temp = temp->next;
            end = temp1;
            cnt++;
        }
        if (temp == end)
        {
            // if temp==end that means the traversal from the last node until temp is done by end and NO PAIR SUM is obtained, so, temp should move forward and end should move to LAST NODE for finding out pairs
            temp = temp->next;
            end = temp1;
        }
        // IN all other scenarios, where pair sum is not obtained for a PARTICULAR TEMP, end is shifted back to try and find pair sum of that PARTICULAR TEMP.
        end = end->prev;
    }
    cout << cnt << endl;
    if (cnt == 0)
    {
        cout << "There is no such pair" << endl; // to return no pair if it is not present
    }
}

// Take temp1 at head and temp2 to head->next and take sum of datas of temp1 and temp2. Check the sum and then store the pair in a data structure if the sum is valid and we increment temp2
// until the sum of temp1 and temp2 EXCEED 5(exceeding logic absent in my code) and temp2's forward movement is TERMINATED THERE. Then, temp1 is moved to its next and temp2 will start at next of temp1 and the above procedure repeats.
// We stop when both temp1 and temp2 are NULL.

// T.C. NEARLY O(n^2)(as inner loop nearly traverses entire LL)(needs OPTIMISATION) S.C. O(n)
void findPairs_brute(Node *head, int sum)
{
    Node *temp1 = head;
    vector<pair<int, int>> ds;
    pair<int, int> pair1;
    while (temp1 != NULL)
    {
        Node *temp2 = temp1->next;
        while (temp2 != NULL && temp1->data + temp2->data <= sum) // we stop when the sum is GREATER than the given sum(IMPORTANT CHECK)
        {
            if (temp1->data + temp2->data == sum)
            {
                pair1.first = temp1->data;
                pair1.second = temp2->data;
                ds.push_back(pair1);
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}
Node* findTail(Node* head)
{
    if(head==NULL || head->next == NULL)
    {
        return head;
    }
    Node* temp = head;
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    return temp;
}

// OPTIMAL APPROACH: We use SORTED PROPERTY to find pair sum. We make left pointer to point at HEAD and right pointer to point at TAIL of LL.
// We check the sum of datas and if the sum EXCEEDS GIVEN SUM, then we move RIGHT TO ITS PREVIOUS NODE(as RESULTANT SUM CAN BE EQUAL TO GIVEN SUM ONLY IF RIGHT MOVES BACKWARD AS THE LL IS SORTED IN NON-DECREASING ORDER).
//If the sum is LESS THAN GIVEN SUM, we INCREMENT LEFT to increase left->data +right->data. Above 2 operations are POSSIBLE as LL IS SORTED.
// Once we get a pair, they are stored. After the pair is obtained, left is INCREMENTED FORWARD and right is INCREMENTED BACKWARD.
// We STOP when right has CROSSED OVER left.

//T.C. O(n+n)= O(2n)(n for finding tail, n for traversal) S.C. O(1)(vector is for storing answer, not extra space)
void findPairs_optimal(Node *head, int sum)
{
     vector<pair<int, int>> ds;
    pair<int, int> pair1;
    if(head==NULL)
    {
        // return ds;
    }
    Node *left = head;
    Node *right = findTail(head);
   
    while (left->data < right->data) //As LL is SORTED
    {
        if (left->data + right->data == sum)
        {
            pair1.first = left->data;
            pair1.second = right->data;
            ds.push_back(pair1);
            left = left->next;
            right = right->prev;
        }
        else if(left->data + right->data < sum)
        {
            left = left->next;
        }
        else{
            right = right->prev;
        }
    }
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 9, 7, 6};
    Node *head = convertArr2DLL(arr);
    print(head);
    cout << endl;
    findPairs(head, 10);
    return 0;
}