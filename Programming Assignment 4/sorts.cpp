#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	int size=nums.size();
	int arr[size];
	for(int i=0;i<size;i++)
	{
		arr[i]=nums[i];
	}
	for(int i=1;i<size;i++)
	{
		int j=i-1;
		int temp= arr[i];
		for(j=i-1;j>=0;j--)
		{
			if(arr[j]>temp)
			{
			arr[j+1]=arr[j];
			}
			else
				{
					break;
				}
		}
		arr[j+1]=temp;
	}
	for(int i=0;i<size;i++)
	{
		nums[i]=arr[i];
	}
	return nums;
}

//=====================================================================================
ListItem<long> * merge(ListItem<long>* first,ListItem<long>* second)
{
	ListItem<long>* temp=NULL;
	if(first==NULL)
	{
		return second;
	}
	if(second==NULL)
	{
		return first;
	}
	if(first->value<=second->value)
	{
		temp=first;
		temp->next=merge(first->next,second);
	}
	else
	{
		temp=second;
		temp->next=merge(first,second->next);
	}
	return temp;
}
ListItem<long>* mergelist(ListItem<long>* head)
{
	if(head==NULL || head->next==NULL)
	{
		return head;
	}	
	ListItem<long>* s1=head,*s2=head;
	while(s1->next && s1->next->next)
	{
		s1=s1->next->next;
		s2=s2->next;
	}
	ListItem<long>* temp=s2->next;
	s2->next=NULL;
	ListItem<long>* second=temp;
	head=mergelist(head);
	second=mergelist(second);
	return merge(head,second);

}
vector<long> MergeSort(vector<long> nums)
{
	List<long> mylist;
	for(int i=0;i<nums.size();i++)
	{
		mylist.insertAtHead(nums[i]);
	}
	ListItem<long>* temp=mergelist(mylist.getHead());
	cout<<endl;
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i]=temp->value;
		temp=temp->next;
	}
	return nums;
}

//=====================================================================================

int partition(long v[],int start,int end)
{
	int i,j,temp;
	i=start;
	j=end;
	temp=(i+j)/2;
	temp=(i+j+temp)/3;
	long pivot= v[temp];
	while(i<=j)
	{
		while(v[i]<pivot)
		{
			i++;
		}
		while(v[j]>pivot)
		{
			j--;
		}
		if(i<=j)
		{
			int temp2=v[i];
			v[i]=v[j];
			v[j]=temp2;
			i++;
			j--;
		}
	}
	return i;
}
void qSort(long temp[],int start,int end)
{
if(start<end)
{
int index=partition(temp,start,end);
if(start<index-1)
{
qSort(temp,start,index-1);
}
if(index<end)
{
qSort(temp,index,end);
}
}
}
vector<long> QuickSortArray(vector<long> nums)
{
long arr[nums.size()];
for(int i=0;i<nums.size();i++)
{
	arr[i]=nums[i];
}
qSort(arr,0,nums.size()-1);
for(int i=0;i<nums.size();i++)
{
	nums[i]=arr[i];
}
return nums;
}

//=====================================================================================
void swap(long *t1, long* t2)
{
	long t=*t1;
	*t1=*t2;
	*t2=t;
}

ListItem<long>* partitionl(ListItem<long>* head, ListItem<long>* tail)
{
	long pivot= tail->value;
	ListItem<long>* temp=head->prev;
	ListItem<long>* j=head;
	while(j!=tail)
	{
		if(j->value<=pivot)
		{
			if(temp!=NULL)
			{
				temp=temp->next;
			}
			else
			{
				temp=head;
			}
			swap(&(temp->value),&(j->value));
		}
		j=j->next;
	}
	if(temp==NULL)
	{
		temp=head;
	}
	else
	{
		temp=temp->next;
	}
	swap(&(temp->value),&(tail->value));
	return temp;
}
void qlsort(ListItem<long>* head,ListItem<long>* tail)
{
if(tail!=NULL && head!=tail && head!=tail->next)
{
	ListItem<long>* temp=partitionl(head,tail);
	if(temp->prev!=head)
	{
		qlsort(head,temp->prev);
	}
	if(temp->next!=tail)
	{
		qlsort(temp,tail);
	}
}
}
vector<long> QuickSortList(vector<long> nums)
{
int size = nums.size();
List<long> mylist;
for(int i=0;i<size;i++)
{
mylist.insertAtHead(nums[i]);
}
qlsort(mylist.getHead(),mylist.getTail());
ListItem<long>* temp=mylist.getHead();
for(int i=0;i<nums.size();i++)
{
	nums[i]=temp->value;
	temp=temp->next;
}
return nums;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
int size=nums.size();
MinHeap myheap(size);
for(int i=0;i<size;i++)
{
	myheap.insertKey(nums[i]);
}
for(int i=0;i<size;i++)
{
	nums[i]=myheap.extractMin();
}
return nums;
}

//=====================================================================================
vector<long> QueenOfAllSorts(vector<long> nums)
{
	long kp= nums.size();
	long kn=kp;
	long *p_arr=new long[kp];
	long *n_arr=new long[kn];
	for(int i=0;i<kp;i++)
	{
		p_arr[i]=-1;
		n_arr[i]=-1;
	}
	for(int i=0;i<nums.size();i++)
	{
		if(nums[i]<0)
		{

			if(nums[i]*-1>kn)
			{
				long temp=kn;
				kn=(nums[i]*-1)*100;
				long *np_arr=new long[kn];
				for (int j = 0; j < kn; j++)
				{
					np_arr[j]=-1;
				}
				for(int j=0;j<temp;j++)
				{
					np_arr[j]=n_arr[j];
				}
				np_arr[nums[i]*-1]=nums[i]*-1;
				delete n_arr;
				n_arr=np_arr;

			}
			else if(n_arr[nums[i]*-1]==-1)
			{
					n_arr[nums[i]*-1]=(nums[i]*-1);
			}
			else
			{
				if(n_arr[nums[i]*-1]==nums[i]*-1)
				{
					n_arr[nums[i]*-1]=(nums[i]*-1)+1;
				}
				else
				{
					n_arr[nums[i]*-1]=n_arr[(nums[i]*-1)]+1;
				}
			}
		}
		else
		{
			if(nums[i]>kp)
			{
				long temp=kp;
				kp=nums[i]+1;
				long *np_arr=new long[kp];
				for (int j = 0; j < kp; j++)
				{
					np_arr[j]=-1;
				}
				for(int j=0;j<temp;j++)
				{
					np_arr[j]=p_arr[j];
				}
				np_arr[nums[i]]=nums[i];
				delete p_arr;
				p_arr=np_arr;
			}
			else if(p_arr[nums[i]]==-1)
			{
					p_arr[nums[i]]=nums[i];
			}
			else
			{
				if(p_arr[nums[i]]==nums[i])
				{
					p_arr[nums[i]]=nums[i]+1;
				}
				else
				{
					p_arr[nums[i]]=p_arr[nums[i]]+1;
				}
			}

		}
	}
	nums.clear();
	for(int i=kn-1;i>0;i--)
	{
		if(n_arr[i]==i)
		{	
			nums.push_back(n_arr[i]*-1);
		}
		else if(n_arr[i]==-1)
		{
			continue;
		}
		else
		{
			int q=0;
			q=n_arr[i]-i;
			q++;
			for(int j=0;j<q;j++)
			{
				nums.push_back(i*-1);
			}
		}
	}
	for(int i=0;i<kp;i++)
	{
		if(p_arr[i]==i)
		{	
			nums.push_back(p_arr[i]);
		}
		else if(p_arr[i]!=-1)
		{
			int q=0;
			q=p_arr[i]-i;
			q++;
			for(int j=0;j<q;j++)
			{
				nums.push_back(i);
			}
		}
	}
return nums;
}
#endif