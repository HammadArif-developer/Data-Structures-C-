#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"
#include <iostream>
using namespace std;
template <class T>
LinkedList<T>::LinkedList()
{
head = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{   
 	head=NULL;
	for(ListItem<T> *otemp = otherLinkedList.head;otemp!=NULL;otemp=otemp->next)
	{
	insertAtTail(otemp->value);
	}
	
}

template <class T>
LinkedList<T>::~LinkedList()
{
if(head==NULL)
{
delete head;
}
else
{
ListItem<T>* temp = head->next;
while(temp!=NULL)
{
    deleteHead();
    temp=temp->next;
}
delete temp;
}
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
if (head==NULL)
{
    ListItem<T> *temp = new ListItem<T>(item);
    head = temp;
    temp=NULL;
    delete temp;
}
else
{
    ListItem<T>* temp = new ListItem<T>(item);
    temp->next=head;
    head->prev=temp;
    head=temp;
    temp = NULL;
    delete temp;
}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
if (head==NULL)
{
    ListItem<T>* temp = new ListItem<T>(item);
    head = temp;
    temp=NULL;
    delete temp;
}
else
{
    ListItem<T>* temp = head;
    while (temp->next!=NULL)
    {
        temp=temp->next;
    }
    ListItem<T>* newnod = new ListItem<T>(item);
    temp->next=newnod;
    newnod->prev=temp;
    temp=NULL;
    newnod=NULL;
    delete temp;
    delete newnod;

}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
if(head==NULL)
{
    return;
}
ListItem<T>* temp = head;
while(temp!=NULL)
{
    if(temp->value==afterWhat)
    {
       ListItem<T>* newnod = new ListItem<T>(toInsert);
       temp->next=newnod;
       newnod->prev=temp;
       newnod=NULL;
       delete newnod;
    }
    temp=temp->next;
}
temp=NULL;
delete temp;
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
if(head==NULL)
{
    return NULL;
}
ListItem<T>* temp = head;
while(temp->next!=NULL)
{
    temp=temp->next;
}
return temp;
}
template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
if(head==NULL)
{
    cout<<"empty list";
}
else
{
ListItem<T>* temp = head;
while(temp!=NULL)
{
    if(temp->value==item)
    {
       return temp;
    }
    temp=temp->next;
}
return temp;
}
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
if(head==NULL)
{
    cout<<"Empty list";
}
if(head->value==item)
{
   if(head->next==NULL)
    {
    ListItem<T>* temp = head;
    head=NULL;
    delete temp;
    }
    else
    {
    ListItem<T>* temp = head;
    head=head->next;
    head->prev=NULL;
    temp->next=NULL;
    delete temp;
    }
}
else
{
ListItem<T>* temp = head;
while(temp!=NULL)
{
    if(temp->value==item)
    {
	if(temp->next==NULL)
	{
	deleteTail();
	break;
        }
	else
	{
       (temp->prev)->next=temp->next;
       (temp->next)->prev=temp->prev;
       
       temp->next=NULL;
       temp->prev=NULL;
       delete temp;
	break;
	}
    }
    else
    {
     temp=temp->next;
    }
}
}
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(head==NULL)
    {
        cout<<"empty";
    }
    if(head->next==NULL)
    {
    ListItem<T>* temp = head;
    head=head->next;
    temp->next=NULL;
    delete temp;
    }
    else
    {
    ListItem<T>* temp = head;
    head=head->next;
    head->prev=NULL;
    temp->next=NULL;
    delete temp;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
if(head==NULL)
{
delete head;
}
if(head==getTail())
{
delete head;
}
else
{
    ListItem<T>* temp = getTail();
    ListItem<T>* prevtemp = temp->prev;
    prevtemp->next=NULL;
    temp->prev=NULL;
    temp->next=NULL;
    delete temp;
}
}
template <class T>
int LinkedList<T>::length()
{
int count1=0;
if(head==NULL)
{
    return count1;
}
else
{
ListItem<T>* temp = head;
while(temp!=NULL)
{
    count1++;
    temp=temp->next;
}
return count1;
}
}
#endif
