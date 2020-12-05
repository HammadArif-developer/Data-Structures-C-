#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
using namespace std;
// HELPER FUNCTIONS HERE...
int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    else
        return b;
}
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){

    // your destructor code goes here
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
    int h=1;
    if(p!=NULL)
    {
        int max_height=max(height(p->left),height(p->right));
        h=max_height+1;
    }
    return h;
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    return (height(p->left) - height(p->right));
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    p->height=1+max(height(p->left),height(p->right));
}

// ROTATING HELPERS
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    node<T>* rightnode=p->right;
    p->right=rightnode->left;
    rightnode->left=p;
    return rightnode;

}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
    node<T>* leftnode=p->left;
    p->left=leftnode->right;
    leftnode->right=p;
    return leftnode;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){
    fixHeight(p);
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations
    if(p==NULL)
    {
        return NULL;
    }
    if(balanceFactor(p)>1)
    {
        if(balanceFactor(p->left)>0)
        {
            p=rotateright(p);
        }
        else
        {
            	node<T> *temp;
                temp = p->left;
                p->left = rotateleft(temp);
                p=rotateright(p);
        }

    }
    else if(balanceFactor(p)< -1)
    {
        if(balanceFactor(p->right)>0)
        {
            node<T> *temp;
            temp = p->right;
            p->right = rotateright(temp);
            p=rotateleft(p);

        }
        else
        {
            p=rotateleft(p);
        }
    }
    return p;

}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);

}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
    if (p==NULL)
    {
        p = new node<T>(k, value);
        return p;
    }
    else
    {
        if(p->key>k)
        {
            p->left=insertHelper(value,k,p->left);
            p=balance(p);
        }
        else if(p->key<k)
        {
            p->right=insertHelper(value,k,p->right);
            p=balance(p);
        }
    }
    return p;
}
template<class T>
node<T>* BST<T> :: search(T key){
  return searchHelper(key,root);

    // Search code goes here.
}
template <class T>
node<T>* searchHelper(T key, node<T> *p){
    if(p==NULL)
    {
     return p;
    }

    if(p->key==key)
    {
        return p;
    }
    else if(p->key>key)
    {
        return searchHelper(key,p->left);
    }
    else if(p->key<key)
    {
        return searchHelper(key,p->right);
    }

}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
if(p==NULL)
{
    return p;
}
if(p->left==NULL && p->left==NULL)
{
    return p;
}
else
{
    return findmin(p->left);
}
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    if(p->left==0)
    {
        return p->right;
    }
    p->left=removemin(p->left);
    return balance(p);

    // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
    //root=balance(root);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
/*if(p==NULL)
{
    return p;
}
else if(k<p->key)
{
    p->left=remove(p->left,k);
}
else if(k>p->key)
{
    p->right=remove(p->right,k);
}
else
{
    node<T>* l=p->left;
    node<T>* r=p->right;
    delete p;
    if(r==NULL)
        return l;
    node<T>* n=findmin(r);
    n->right=removemin(r);
    n->left=l;
    return balance(n);
}
return balance(p);*/
if(p==NULL)
{
    return p;
}
else if(k<p->key)
{
    p->left=remove(p->left,k);
}
else if(k>p->key)
{
    p->right=remove(p->right,k);
}
else
{
    if(p->right==NULL && p->left==NULL)
    {
        delete p;
        p=NULL;
        return p;
    }
    else if(p->right==NULL)
    {
        node<T>* n=p;
        p=p->left;
        delete n;
        return p;
    }
    else if(p->left==NULL)
    {
        node<T>* n=p;
        p=p->right;
        delete n;
        return p;
    }
    else
    {
       node<T>* n=findmin(p->right);
       n->right=removemin(p->right);
       n->left=p->left;
       return balance(n);
    }
}
return balance(p);
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
