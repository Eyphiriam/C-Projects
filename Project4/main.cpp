#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;
struct node
{
    int dishNumber;
    int counter;
    struct node *left;
    struct node *right;
};

class BinarySearchTree{
    struct node *root = NULL;

public:
    struct node * getroot()
    {
        return this->root;
    }
    void setroot(struct node *root)
    {
        this->root=root;
    }
    struct node *newItem(int item)
    {
        struct node *temp =  (struct node *)malloc(sizeof(struct node));
        temp->dishNumber = item;
        temp->left = temp->right = NULL;
        temp->counter=1;
        return temp;
    }


    void Display(struct node *root)
    {
        if (root != NULL)
        {
            Display(root->left);
            if(root->dishNumber==1)
                cout<<root->dishNumber<<"- Fried Chicken "<<root->counter<<endl;
            if(root->dishNumber==2)
                cout<<root->dishNumber<<"- Pork Chops "<<root->counter<<endl;
            if(root->dishNumber==3)
                cout<<root->dishNumber<<"- Baked Chicken "<<root->counter<<endl;
            if(root->dishNumber==4)
                cout<<root->dishNumber<<"- Grilled Salmon "<<root->counter<<endl;
            if(root->dishNumber==5)
                cout<<root->dishNumber<<"- Roast Beef "<<root->counter<<endl;
            if(root->dishNumber==6)
                cout<<root->dishNumber<<"- Grilled Steak "<<root->counter<<endl;
            if(root->dishNumber==7)
                cout<<root->dishNumber<<"- Meat Loaf "<<root->counter<<endl;
            Display(root->right);
        }
    }
    struct node* IsThere(struct node* root,int dishNum)
    {

        if (root == NULL || root->dishNumber == dishNum)
            return root;

        if (root->dishNumber < dishNum)
            return IsThere(root->right, dishNum);

        return IsThere(root->left, dishNum);

        return NULL;
    }

    struct node* insert(struct node* node,int dishNum)
    {

        if (node == NULL) return newItem(dishNum);

        if (dishNum < node->dishNumber)
            node->left  = insert(node->left, dishNum);
        else if (dishNum > node->dishNumber)
            node->right = insert(node->right, dishNum);

        return node;
    }
};
int main()
{
    BinarySearchTree bst;
    string input;
    cout << "Please enter: \n";
    getline(cin,input);

    for(int i=0;i<input.length();i++)
    {
        if(input[i]!=' ')
        {
            int dn=input[i]-'0';
            if(bst.IsThere(bst.getroot(),dn)==NULL)
            {
                bst.setroot(bst.insert(bst.getroot(),dn));

            }
            else
            {
                struct node* temp;
                temp=bst.IsThere(bst.getroot(),dn);
                temp->counter+=1;
            }
        }
    }

    bst.Display(bst.getroot());
    return 0;
}