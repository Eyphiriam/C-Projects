#include "List.h"
#include <iostream>
int menu();
int main()
{

    int choice;
    int element;
    List List;

    do {
        choice = menu();

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert: ";
                std::cin >> element;
                List.InsertAtEnd(element);
                break;
            case 2:
                std::cout << "Enter the value to delete: ";
                std::cin >> element;
                List.Delete(element);
                break;
            case 3:
                List.Display();
                break;
            case 4:{
                std::cout << "Enter the value to search: ";
                std::cin >> element;
                int position = List.Search(element);
                if (position != 0) {
                    std::cout << "Value found at position " << position << std::endl;
                } else {
                    std::cout << "Value not found in the list." << std::endl;
                }
                break;
        }
            case 5:
                system("pause");
                exit(0);

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while(choice!=5);
    }

//Displays a list of menu choices and prompt to enter user choice
//and returns the user choice
int menu()
{

    int choice;

    std::cout<<"\n\t1.Insert"<<std::endl;
    std::cout<<"\t2.Delete"<<std::endl;
    std::cout<<"\t3.Display"<<std::endl;
    std::cout<<"\t4.Search"<<std::endl;
    std::cout<<"\t5.Exit"<<std::endl;
    std::cout<<"\tEnter your choice:";
    std::cin>>choice;
    return choice;

}


