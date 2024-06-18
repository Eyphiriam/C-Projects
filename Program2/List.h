//file: List.h

typedef int ElementType;

struct node{
    ElementType data;
    node * next;
};

class List
{ public:
    List(); //Create an empty list
    bool Empty(); // return true if the list is empty, otherwise return false
    void InsertAtEnd(ElementType x); //insert a value x on the end of the list
    void Delete(ElementType x); //if value x is in the list, remove x
    void Display(); //Display the data values in the list in the order inserted
    int Search(ElementType X); // Find and return the location of x. If x is not in the list, return 0.


private:
    node * first; //pointer to first node
};
