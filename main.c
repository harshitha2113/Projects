#include<stdio.h>
#include "contact.h"
int main()
{
        int option, index;
        Addressbook addressbook;
        initialize(&addressbook);
        //loadcontact(&addressbook);
        do
        {
                printf("\nAddress Book Menu:\n");
                printf("1. Create contact\n");
                printf("2. List contact\n");
                printf("3. Search contact\n");
                printf("4. Edit contact\n");
                printf("5. Delete contact\n");
                printf("6. Save contact\n");
                printf("7. Exit\n");
                printf("Enter your option : ");
                //checking if input is valid
                int result = scanf(" %d",&option);
                if(result)
                {
                        switch(option)
                        {
                                case 1:
                                        createcontact(&addressbook);
                                        break;
                                case 2:
                                        listcontact(&addressbook);
                                        break;
                                case 3:
                                        searchcontact(&addressbook);
                                        break;
                                case 4:
                                        editcontact(&addressbook);
                                        break;
                                case 5:
                                        deletecontact(&addressbook);
                                        break;
                                case 6:
                                        savecontact(&addressbook);
                                        break;
                                default:
                                        printf("Invalid choice. Please try again.\n");
                        }
                }
                else
                {
                        printf("invalid choice entered\n");
                        while(getchar() != '\n');
                }
        }while(option != 7);
}

