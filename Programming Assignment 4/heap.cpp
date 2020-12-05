#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include<climits>

void Swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
MinHeap::MinHeap(int cap)
{
    capacity=cap;
    heap_size=0;
    harr=new int[cap];
}

void MinHeap::MinHeapify(int i)
{
    int l= left(i);
    int r= right(i);
    int small=i;
    if(l<heap_size)
    {
        if(harr[l]<harr[small])
        {
         small=l;
        }
    }
    if(r<heap_size)
    {
        if(harr[r]<harr[small])
        {
         small=r;
        }
    }
    if(small!=i)
    {
        Swap(&harr[i],&harr[small]);
        MinHeapify(small);
    }
}

int MinHeap::parent(int i)
{
    return (i-1)/2;
}

int MinHeap::left(int i)
{
    return (2*i)+1;
}

int MinHeap::right(int i)
{
    return (2*i)+2;
}

int MinHeap::extractMin()
{
    if(heap_size==1)
    {
        heap_size--;
        return harr[0];
    }
    else
    {
        int temp=harr[0];
        harr[0]= harr[heap_size-1];
        MinHeapify(0);
        heap_size--;
        return temp;
    }
}

void MinHeap::decreaseKey(int i, int new_val)
{
    if(new_val<i)
    {
        harr[i]=new_val;
        int temp=i;
        while(temp!=0 && harr[parent(temp)]>=harr[temp])
        {
            Swap(&harr[temp],&harr[parent(temp)]);
            temp=parent(temp);

        }


    }
}

int MinHeap::getMin()
{
    if(heap_size>0)
    {
        return harr[0];
    }

}

void MinHeap::deleteKey(int i)
{
    if(i<heap_size)
    {
    decreaseKey(i,getMin()-1);
    extractMin();
    }
}

void MinHeap::insertKey(int k)
{
    if(heap_size<capacity)
    {
        harr[heap_size]=k;
        int temp=heap_size;
        heap_size++;

        while(temp!=0 && harr[parent(temp)]>harr[temp])
        {
            Swap(&harr[temp],&harr[parent(temp)]);
            temp=parent(temp);
        }
    }
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif
