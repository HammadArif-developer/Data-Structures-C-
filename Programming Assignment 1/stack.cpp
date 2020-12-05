#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{

}

template <class T>
Stack<T>::Stack(Stack<T>& otherStack):list(otherStack.list)
{

}

template <class T>
Stack<T>::~Stack()
{
    
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    return (list.getHead())->value;
}

template <class T>
T Stack<T>::pop()
{
T head_element=(list.getHead())->value;
list.deleteHead();
return head_element;
}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    if(list.length()==0)
    {
        return true;
    }
    return false;
}

#endif
