//file: List.h
typedef int ElementType;
const int MAX = 100;
class List
{
public:
    List(); //Create an empty list
    bool Empty(); // return true if the list is empty, otherwise return false
    void InsertAtEnd(ElementType x); //insert a value x on the end of the list
    void Delete(ElementType x); //if value x is in the list, remove x
    void Display(); //Display the data values in the list in the order inserted
    int Search(ElementType X); // Find and return the location of x. If x is not in the list, return 0.

private:
    int N; //number of values in list
    ElementType listArray[MAX]; //the array to hold the list values
};

// Created by matth on 5/31/2023.
//

#ifndef ASSIGNMENT2_PROGRAM_1_LISTS_H
#define ASSIGNMENT2_PROGRAM_1_LISTS_H





#endif //ASSIGNMENT2_PROGRAM_1_LISTS_H
