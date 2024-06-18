//
// Created by matth on 5/31/2023.
//
#include<iostream>
#include "List.h"
using namespace std;
//Set all elements to zero
List::List()
{
    N = 0; // Initialize the number of values to 0
}

bool List::Empty()
{
    return N == 0;
}

void List::InsertAtEnd(ElementType x) {
    if (N < MAX) {
        listArray[N] = x; // Insert value at the end
        N++; // Increment the number of values
    }
}

void List::Delete(ElementType x)
{

    bool found=false;
    int pos=-1;

    for(int index=0;index<N &&!found;index++)
    {
        if(listArray[index]==x)
        {
            found=true;
            pos=index;
        }
    }


    if(found)
    {
        for(int index=pos;index<N;index++)
        {
            listArray[index]=listArray[index+1];
        }

        N--;
    }

}

void List::Display()
{
    for(int index=0;index<N;index++)
        cout<<"listArray["<<index<<"] = "<<listArray[index]<<endl;

}
int List::Search(ElementType x)
{
    for (int i = 0; i < N; i++)
    {
        if (listArray[i] == x)
        {
            return i + 1; // Return the position (index + 1) of the value in the list
        }
    }
    return 0; // Value not found
}
