//============================================================================
// Name        :LinkedList.h
// Author      :Dr Fatma Serce
// Modified    :Shaila Hirji
// Copyright   : Your copyright notice
// Description : This class is a generic implementation of LinkedList using 				
//              Modifications were made to this class by adding an :
//                                                      insert() function
//                                                      existing deletenodeLL() function was modified
//              This class was used when implementing the filter feature of the Phone Book App 

//============================================================================
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

using namespace std;
template<class T>
struct nodeLL {
    T data;
    nodeLL *next;
};

template<class T>
class LinkedList {
private:
    LinkedList(const LinkedList &) = delete; //copy constructor

protected:
    int count;
    nodeLL<T> *head, *last;
public:
    LinkedList();

    bool isEmpty();

    int length();

    T front();

    T back();

    void insertFirst(T &);

    void insertLast(T &);

    //////////////my added function
    virtual void insert(T &);

    virtual T deletenodeLL(T &);
    ////////////////////////////

    void destroylist();

    LinkedList<T> &operator=(LinkedList<T> &);

    template<class U>

    friend ostream &operator<<(ostream &os, LinkedList<U> &list);

    virtual ~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList() {
    head = last = NULL;
    count = 0;
}

template<class T>
bool LinkedList<T>::isEmpty() {
    return head == NULL;
}

template<class T>
int LinkedList<T>::length() {
    return count;
}

template<class T>
T LinkedList<T>::front() {
    return head->data;
}

template<class T>
T LinkedList<T>::back() {
    return last->data;
}

template<class T>
void LinkedList<T>::insertFirst(T &item) {
    nodeLL<T> *temp = new nodeLL<T>;
    temp->data = item;
    temp->next = head;
    head = temp;
    count++;
    if (last == NULL)
        last = temp;

}

template<class T>
void LinkedList<T>::insertLast(T &item) {
    nodeLL<T> *newnodeLL = new nodeLL<T>;
    newnodeLL->data = item;
    newnodeLL->next = NULL;
    if (head == NULL) {
        head = last = newnodeLL;
    } else {
        last->next = newnodeLL;
        last = newnodeLL;
    }
    count++;
}

///////////////// my edit /////////////////////////////////
template<class T>
void LinkedList<T>::insert(T &item) {
    insertLast(item); //calls insert last as the default insert method
}

template<class T>
T LinkedList<T>::deletenodeLL(T &item) {
    if (head == NULL) //check for empty list
        cerr << "empty list";
    else {
        if (head->data == item) { //if head is to be deleted
            nodeLL<T> *p = head;
            head = head->next;
            delete p;
            count--;
            if (head == NULL)
                last = NULL;
        } else {
            //two pointers to traverse list
            nodeLL<T> *p = head;
            nodeLL<T> *q = p->next;
            while (q != NULL && q->data != item) { //traverse through list to find desired nodeLL
                p = q;
                q = q->next;
            }
            if (q != NULL) { //item to be deleted was found, delete it
                p->next = q->next; //re assign p's next to nodeLL after q-- the nodeLL to be deleted
                count--; //decrement count
                if (last == q)
                    last = p; //if nodeLL deleted was last nodeLL, reassign it
                delete q; //delete the nodeLL and free memory
            }
        }
    }
    return item; //return the nodeLL deleted
}
///////////////////////////////////////////////////////////////

template<class T>
void LinkedList<T>::destroylist() {
    nodeLL<T> *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        delete p;
    }
    last = NULL;
    count = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &list) {
    if (this != &list) {
        copylist(list);
    }
    return *this;
}

template<class T>
ostream &operator<<(ostream &os, LinkedList<T> &list) {
    nodeLL<T> *p = list.head;
    while (p != NULL) {
        cout << p->data;
        p = p->next;
    }
    return os;
}

template<class T>
LinkedList<T>::~LinkedList() {
    destroylist();
}

#endif /* LINKEDLIST_H_ */
