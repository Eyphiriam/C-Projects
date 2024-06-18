#include"List.h"
#include<iostream>
using namespace std;
List::List(){
    first = NULL;
}
bool List::Empty(){
    return first==NULL;
}
void List::Display(){
    node *p = first;
    while(p!=NULL){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}
int List::Search(ElementType x)
{
    if (Empty()) {
        return 0;
    }

    node* current = first;
    int position = 1;
    while (current != nullptr) {
        if (current->data == x) {
            return position;
        }
        current = current->next;
        position++;
    }

    return 0;
}

void List::InsertAtEnd(ElementType d){
    node *p = new node;
    p->data = d;
    p->next = NULL;
    if(first == NULL){
        first = p;
    }else{
        node *cur = first;
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = p;
    }
}
void List::Delete(ElementType d) {
    if (first == NULL) {
        cout << "The list is empty" << endl;
    } else if (this->first->data == d) {
        node *current = first;
        this->first = this->first->next;
        delete current;
    } else {
        node *previous = this->first;
        node *current = first->next;
        while (current != NULL) {
            if (current->data == d) {
                break;
            } else {
                previous = current;
                current = current->next;
            }
        }
        if (current == NULL) {
            cout << "Can't remove value: no match found.\n";
        } else {
            previous->next = current->next;
            delete current;
        }
    }
}