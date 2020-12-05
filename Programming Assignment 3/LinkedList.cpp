#ifndef __LIST_CPP
#define __LIST_CPP
#include <iostream>
#include <cstdlib>
#include "LinkedList.h"
using namespace std;
template <class T>
LinkedList<T>::LinkedList()
{	
	
	head=NULL;

}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{	
	
	if (otherLinkedList.head==NULL)

	{
		
		head==NULL;	
	}

	else if (otherLinkedList.head->next==NULL)

	{
		
		insertAtHead(otherLinkedList.head->value);
	}
	
	else 

	{  
		insertAtHead(otherLinkedList.head->value);
		ListItem<T> *current_nodeoldlist=otherLinkedList.head;
		head=new ListItem <T>(getHead()->value);
		ListItem<T>*previousnode_new=head;
		ListItem<T> *current_newnode;
		int counter=0;
		while (current_nodeoldlist->next!=NULL) //this inserts all nodes except the last node
		{
			current_nodeoldlist=current_nodeoldlist->next;
			current_newnode=new ListItem<T>(current_nodeoldlist->value);
			previousnode_new->next=current_newnode;
			current_newnode->prev=previousnode_new;
			previousnode_new=current_newnode;
		}
			
	}

}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T>* currentnode=head;
	ListItem<T>* temp;

	if (head==NULL)
	{
		return;
	}

	else if(head->next==NULL) 
	{
		delete head;
		head=NULL;
	}

	else 
	{
		while (currentnode->next!=NULL)
		{
			temp=currentnode;
			currentnode=currentnode->next;
			delete temp;
		}
		temp=NULL;
		delete currentnode;
		currentnode=NULL;
	}
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	if (head==NULL)
	{
		head=new ListItem<T>(item);
	}

	else 
	{	ListItem<T> *newnode;
		newnode=new ListItem<T>(item);
	 	newnode->prev=NULL;
	 	newnode->next=head;
	 	head->prev=newnode;
	 	head=newnode;
	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	if (head==NULL)
	{
		head=new ListItem<T>(item);
	}
	else 
	{
		ListItem<T>* tail=getTail();
	
		ListItem<T> *newnode;
		newnode=new ListItem<T>(item);
		newnode->next=NULL;
		newnode->prev=tail;
		tail->next=newnode;
		tail=newnode;
	}



}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{	
	 ListItem<T> *current_node=head;
	 ListItem<T> *previousnode;
	
	if (head==NULL)
	{	//cout<<"head==NULL"<<endl;
		return;
	}

	else if ((head->value==afterWhat) && (head->next==NULL)) {
		ListItem<T> *newnode=new ListItem<T>(toInsert);
		newnode->next=NULL;
		newnode->prev=head;
		head->next=newnode; 
		//cout<<"I am inside ((head->value==afterWhat) && (head->next=NULL) "<<endl;
	}
	else if (getTail()->value==afterWhat)
	{	//cout<<"get_tail"<<endl;
		insertAtTail(toInsert);

	}

	else 
	{  	//cout<<"inside else"<<endl;
		bool isFound=false;
		while ((current_node->next!=NULL) && (isFound==false))
		{	
			if (current_node->value==afterWhat)
			{	
				previousnode=current_node;
				current_node=current_node->next;
				isFound=true;
				ListItem<T> *newnode=new ListItem<T>(toInsert);
				previousnode->next=newnode;
				current_node->prev=newnode;

				newnode->next=current_node;
				newnode->prev=previousnode;
			}
			else 

			{
				current_node=current_node->next;
			}

		}

	}

}

template <class T>
void LinkedList<T>::insertSorted(T item)
{	ListItem<T> *current_node=head;
	ListItem<T> *previousnode=head;
	if (head==NULL)
	{
		insertAtHead(item);
	}
	else if (head->value>item)
	{
		insertAtHead(item);
	}
	else if (getTail()->value<item)
	{
		insertAtTail(item);	

	}

	else 
	{	bool isInserted=false;
		while ((current_node->next!=NULL) && (isInserted==false))
		{
			if (current_node->value>item)
			{
				previousnode=current_node->prev;
				ListItem<T> *newnode=new ListItem<T>(item);
				previousnode->next=newnode;
				current_node->prev=newnode;
				newnode->next=current_node;
				newnode->prev=previousnode;
				isInserted=true;
			}

			else 
			{
				current_node=current_node->next;
			}
		}

		if ((current_node->value>=item) && (isInserted==false)) //inserting just before tail node
		{
				previousnode=current_node->prev;
				ListItem<T> *newnode=new ListItem<T>(item);
				previousnode->next=newnode;
				current_node->prev=newnode;
				newnode->next=current_node;
				newnode->prev=previousnode;
				current_node->next=NULL;
		}


	}
}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{	
	ListItem<T>* head_list;
	head_list=head;
	return head_list;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{	

	if (head==NULL)
	{
		return NULL;
	}
	else 
	{
		ListItem<T>* tail=head;
		while(tail->next!=NULL)
		{
			tail=tail->next;
		}
		return tail;
	}





}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{	
	if (head==NULL)
	{
		return NULL;
	}

	else if (head->value==item)
	{
		return head;
	}

	else if (getTail()->value==item)
	{
		return getTail();
	}
	else 
	{	 ListItem<T> *current_node=head;
		while(current_node->next!=NULL)
		{
			if (current_node->value==item)
			{
				return current_node;
			}

			else 
			{
				current_node=current_node->next;
			}	
		}

		return NULL;
	}
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{	if (head==NULL)
	{
		return ;
	}

	else if (head->value==item)
	{	
		deleteHead();
	}

	else if (getTail()->value==item)
	{	
		deleteTail();
	}

	else
	{ 	
		ListItem<T> *current_node=searchFor(item);
		
		if (current_node==NULL)
		{
			return ;
		}

		else 
		{  
			ListItem<T> *previousnode=current_node->prev;
			ListItem<T> *nextnode=current_node->next;
			previousnode->next=nextnode;
			nextnode->prev=previousnode;
			delete current_node;
			current_node=NULL;
			return;
		}
	}
}

template <class T>
void LinkedList<T>::deleteHead()
{	ListItem<T> *current_node=head;
	if (head==NULL)
	{
		return ;
	}

	else if (head->next==NULL) //if there is single node in the linked list
	{
		delete head;
		head=NULL;

	}

	else 
	{	
		 head=head->next;
		 head->prev=NULL;
		 delete current_node;
		 current_node=NULL;
	}

}

template <class T>
void LinkedList<T>::deleteTail()
{
	if (getTail()==NULL)
	{
		return;
	}

	else if (getTail()->prev==NULL) //if there is a single node
	{
		ListItem<T> *current_tail=getTail();
		delete current_tail;
		head=NULL;
	}

	else 
	{	
		ListItem<T> *current_tail=getTail();
		ListItem<T> *previousnode=current_tail->prev;
		previousnode->next=NULL;
		delete current_tail;
		current_tail=NULL;


	}


}

template <class T>
int LinkedList<T>::length()
	 
{
	ListItem<T> *current_node=head;
	if (head==NULL)
	{
		return 0;
	}

	else if (head->next==NULL)
	{
		return 1;
	}

	else 	
	{	int counter=0;
		while (current_node->next!=NULL)
		{
			counter++;
			current_node=current_node->next;
		}
		counter++;
		return counter;
	}

}

template <class T>
void LinkedList<T>::reverse()
{
	if (head==NULL)
	{
		return;
	}	

	else if (head->next==NULL)
	{

	}

	else 
	{	
		ListItem<T> *previousnode=getTail();
		previousnode=previousnode->prev;
		head=getTail();
		head->prev=NULL;
		ListItem<T> *currentnode=head;
		while (previousnode->prev!=NULL)
		{	ListItem<T> *temp=previousnode;
			previousnode=previousnode->prev;
			currentnode->next=temp;
			temp->prev=currentnode;
			currentnode=currentnode->next;		
		}

		currentnode->next=previousnode;
		previousnode->prev=currentnode;
		currentnode=currentnode->next; //going to tail node
		currentnode->next=NULL;

		
	}
}

template <class T>
void LinkedList<T>::parityArrangement()
{
	if (head==NULL)
	{
		return;
	}

	else if(head->next==NULL)
	{
		return;
	}

	else 
	{	ListItem<T> *evennodehead=head->next;
		ListItem<T> *evennode=head->next;
		ListItem<T> *oddnode=head;

		while (oddnode->next->next!=NULL)
		{
			oddnode->next=oddnode->next->next;
			oddnode->next->prev=oddnode;
			if (evennode->next->next!=NULL)
			{
				evennode->next=evennode->next->next;
				evennode->next->prev=evennode;
				evennode=evennode->next;
			}
			oddnode=oddnode->next;	
			if (oddnode->next==NULL)
			{break;}
		}
		evennode->next=NULL;
		oddnode->next=evennodehead;
		evennode->prev=oddnode;

	}

}

template <class T>
int LinkedList<T>::isPalindrome()
{	ListItem<T> *currentnode=head;

	if (head==NULL)
	{
		return 0;
	}
	
	else if (head->next==NULL)
	{
		return 1;

	}

	else 
	{	
		ListItem<T> *currentnodestart=head;
		ListItem<T> *currentnode_end=getTail();

		while (currentnodestart->next!=NULL)
		{
			if (currentnodestart->value!=currentnode_end->value)
			{
				return 0;
			}
			currentnodestart=currentnodestart->next;
			currentnode_end=currentnode_end->prev;
		}

			if (currentnodestart->value!=currentnode_end->value)
			{
				return 0;
			}

			else 
			{
				return 1;
			}

	}
}

#endif
