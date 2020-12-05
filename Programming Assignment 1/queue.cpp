#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue):list(otherQueue.list)
{
     
}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
return (list.getHead())->value;
}

template <class T>
T Queue<T>::dequeue()
{
T head_element=(list.getHead())->value;
list.deleteHead();
return head_element;
}

template <class T>
int Queue<T>::length()
{
return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
if(list.length()==0)
    {
        return true;
    }
    return false;
}


#endif
