#include <iostream>
using namespace std;

template<typename T>
class Node{
public:
    T data;
    Node* next;
    Node(T data){
        this->data = data;
        this->next = NULL;
    }
};

template<typename T>
class Linked_List{
    Node<T>* head;
    Node<T>* tail;
    int length;

    Node<T>* merge(Node<T>* left, Node<T>* right){
        Node<T>* head = NULL, *prev = NULL;
        if(left->data <= right->data){
            head = left;
            left = left->next;
        }
        else{
            head = right;
            right = right->next;
        }
        prev = head;
        while(left != NULL && right != NULL){
            if(left->data <= right->data){
                prev->next = left;
                left = left->next;
            }
            else{
                prev->next = right;
                right = right->next;
            }
            prev = prev->next;
        }
        while(left != NULL){
            prev->next = left;
            left = left->next;
            prev = prev->next;
        }
        while(right != NULL){
            prev->next = right;
            right = right->next;
            prev = prev->next;
        }
        return head;
    }
    Node<T>* midPoint(Node<T>* temp ){
        if(temp == NULL){
            return head;
        }
        Node<T>* fast = temp->next;
        Node<T>* slow = temp;
        while(fast != NULL && fast->next != NULL){
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    Node<T>* mergeSort(Node<T>* temp){
        if(temp == NULL || temp->next == NULL){
            return temp;
        }
        Node<T>* mid = midPoint(temp);
        Node<T>* leftHalf = temp;
        Node<T>* rightHalf = mid->next;
        mid->next = NULL;
        Node<T>* left = mergeSort(leftHalf);
        Node<T>* right = mergeSort(rightHalf);
        temp = merge(left, right);
        return temp;
    }
    void add(T data){
        Node<T>* newNode = new Node<T>(data);
        if(newNode == NULL){
            cout << "Error: Unable to create node now" << endl;
            return;
        }
        if(tail == NULL){
            head = newNode;
            tail = newNode;
            length++;
            return;
        }
        tail->next = newNode;
        tail = tail->next;
        length++;
        return;
    }

public:
    Linked_List(){
        head = NULL;
        tail = NULL;
        length = 0;
    }
    Linked_List(T data){
        head = new Node<T>(data);
        tail = head;
        length++;
    }
    ~Linked_List(){
        if(head == NULL)
            return;
        Node<T>* temp = head;
        tail = tail->next;
        while(head != NULL){
            temp = head;
            head = head->next;
            delete temp;
        }
        return;
    }
    void print(){
        if(head == NULL){
            cout << "Error: Cannot print an empty list" << endl;
            return;
        }
        Node<T>* temp = head;
        while(temp != NULL){
            cout << temp->data << "-->";
            temp = temp->next;
        }
        cout << endl;
    }
    void remove(int element){
        if(head == NULL){
            cout << "Error: List is empty" << endl;
            return;
        }
        if(head->data == element){
            Node<T>* temp = head;
            if(tail == head)
                tail = tail->next;
            head = head->next;
            delete temp;
            length--;
            return;
        }
        Node<T>* temp = head;
        Node<T>* prev = NULL;
        while(temp != NULL){
            if(temp->data == element){
                if(prev == NULL){
                    Node<T>* del = temp;
                    temp = temp->next;
                    delete del;
                    length--;
                    return;
                }
                else{
                    Node<T>* del = temp;
                    prev->next = temp->next;
                    temp = temp->next;
                    delete del;
                    length--;
                    return;
                }
            }
            else{
                prev = temp;
                temp = temp->next;
            }
        }
        cout << "Error: Element not found" << endl;
        return;
    }
    void insert(T data, int position = -1){
        if(position > length){
            cout << "Enter a valid position" << endl;
            return;
        }
        Node<T>* newNode = new Node<T>(data);
        if(newNode == NULL){
            cout << "Error: Unable to create node now" << endl;
            return;
        }
        if(position == -1){
            add(data);
            return;
        }
        if(head == NULL){
            head = newNode;
            tail = newNode;
            length++;
            return;
        }
        if(position == 1){
            head->next = newNode;
            head = newNode;
            if(length == 1)
                tail = head;
            length++;
            return;
        }
        int i = 1;
        Node<T>* prev = NULL, *temp = head;
        while(temp != NULL){
            if(i == position){
                newNode->next = temp;
                prev->next = newNode;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        length++;
        return;
    }
    int len(){
        return length;
    }
    void sort(){
        head = mergeSort(head);
    }
};
