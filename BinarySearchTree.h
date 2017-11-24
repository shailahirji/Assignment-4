/*
 * BinarySearchTree.h
 *
 *  Created on: Oct 30, 2017
 *      Author: fatma.serce
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <iostream>
#include"LinkedList.h"

using namespace std;

template<class T>
struct node {
    T data;
    node<T>* left;
    node<T>* right;
};

template<class T>
class BinarySearchTree {
private:
    node<T>* root;
    void inOrderT(node<T>*);
    void preOrderT(node<T>*);
    void postOrderT(node<T>*);
    void destroy(node<T>*);
    int treeHeight(node<T>*);
    int max(int, int);
    int treeNodeCount(node<T>*);
    int treeLeaveCount(node<T>*);
    void treeInsert(node<T>*&, T&);
    T treeSearch(node<T>*, T&);
    //==============implemented By Shaila====
    void treeFilterSearch(node<T>*, T&, LinkedList<T>*);
    //=======================================
    node<T>* findMax(node<T>*);
    void deletenode(node<T>*&, T&);

public:
    BinarySearchTree();
    void inOrder() {
        inOrderT(root);
    }
    void preOrder() {
        preOrderT(root);
    }
    void postOrder() {
        postOrderT(root);
    }
    int height() {
        return treeHeight(root);
    }
    int nodeCount() {
        return treeNodeCount(root);
    }
    int leaveCount() {
        return treeLeaveCount(root);
    }
    void insert(T& item) {
        treeInsert(root, item);
    }
    T search(T& item) {
        return treeSearch(root, item);
    }
    //==== implemented by Shaila
    void filter(T& item, LinkedList<T>*p) {
        //        LinkedList<T>::LinkedList();
        return treeFilterSearch(root, item, p);
    }
    //======================
    //	void insert(T&); //non-recursive function call
    node<T>* findMax() {
        return findMax(root);
    }
    void deletenode(T& item) {
        deletenode(root, item);
    }
    ~BinarySearchTree() {
        destroy(root);
    }

};

template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    root = NULL;
}

template<class T>
void BinarySearchTree<T>::inOrderT(node<T>* p) {
    if (p != NULL) {
        inOrderT(p->left);
        cout << p->data;
        inOrderT(p->right);
    }
}

//inorder traversal without recursion
//template <class T>
//void BinarySearchTree<T>::inOrderT(node<T>* p){
//	stack< node<T>* > s;
//	while(p!= NULL || !s.isEmpty())
//	if(p!= NULL){
//		s.push(p);
//		p = p->left;
//	}else{
//		p = s.pop();
//		cout<<p->data:
//		p = p->right;
//	}
//}

template<class T>
void BinarySearchTree<T>::preOrderT(node<T>* p) {
    if (p != NULL) {
        cout << p->data;
        preOrderT(p->left);
        preOrderT(p->right);
    }
}

template<class T>
void BinarySearchTree<T>::postOrderT(node<T>* p) {
    if (p != NULL) {
        postOrderT(p->left);
        postOrderT(p->right);
        cout << p->data;
    }
}
template<class T>
int BinarySearchTree<T>::max(int x, int y) {
    if (x > y)
        return x;
    return y;
}

template<class T>
int BinarySearchTree<T>::treeHeight(node<T>* p) {
    if (p != NULL) {
        return 1 + max(treeHeight(p->left), treeHeight(p->right));
    }
    return 0;
}

template<class T>
int BinarySearchTree<T>::treeNodeCount(node<T>* p) {
    if (p == NULL)
        return 0;
    else
        return 1 + treeNodeCount(p->left) + treeNodeCount(p->right);
}
template<class T>
int BinarySearchTree<T>::treeLeaveCount(node<T>* p) {
    if (p == NULL)
        return 0;
    else if (p->left == NULL && p->right == NULL)
        return 1;
    else
        return treeLeaveCount(p->left) + treeLeaveCount(p->right);
}
template<class T>
void BinarySearchTree<T>::destroy(node<T>* p) {
    if (p != NULL) {
        destroy(p->left);
        destroy(p->right);
        delete p;
        p = NULL;
    }
}

template<class T>
void BinarySearchTree<T>::treeInsert(node<T>*& p, T& item) {
    if (p == NULL) {
        p = new node<T>;
        p->data = item;
        p->left = p->right = NULL;
    } else if (item < p->data) {
        treeInsert(p->left, item);
    } else {
        treeInsert(p->right, item);
    }

}

template<class T>
T BinarySearchTree<T>::treeSearch(node<T>* p, T& item) {
    if (p == NULL)
        return item;
    else if (item < p->data)
        return treeSearch(p->left, item);
    else if (item > p->data)
        return treeSearch(p->right, item);
    return p->data;
}

//===================implemented by Shaila ==========================
/*
 * This function populates a linked list with values that occur before a specific value
 */
template<class T>
void BinarySearchTree<T>::treeFilterSearch(node<T> *p, T& item,
                                           LinkedList<T>* ll) {

    if (p != NULL && p->data < item) {	// if value at p<item
        treeFilterSearch(p->left, item, ll);	//traverse to left of p
        ll->insert(p->data);	//add the value into LL
        treeFilterSearch(p->right, item, ll);	///traverse to right of p
    } else if (p != NULL) {	//else if value is > or = to item,
        treeFilterSearch(p->left, item, ll);	//traverse left
        treeFilterSearch(p->right, item, ll);	//traverse right
    }

}
//========================================================
template<class T>
node<T>* BinarySearchTree<T>::findMax(node<T>* p) {
    if (p == NULL)
        return NULL;
    else if (p->right == NULL)
        return p;
    else
        return findMax(p->right);
}

template<class T>
void BinarySearchTree<T>::deletenode(node<T>*& p, T& item) {
    //item not found, do nothing
    if (p == NULL)
        return;
    else if (item < p->data)	//item is on the left subtree
        deletenode(p->left, item);
    else if (item > p->data)	//item is on the right subtree
        deletenode(p->right, item);
    else {	//item is equal to data,  it is found
        if (p->left != NULL && p->right != NULL) {	//if it is with two children
            p->data = findMax(p->left)->data;
            deletenode(p->left, p->data);
        } else {
            node<T>* old = p;
            if (p->left != NULL)
                p = p->left;
            else
                p = p->right;

            delete old;
        }
    }
}

#endif /* BINARYSEARCHTREE_H_ */

