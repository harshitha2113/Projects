#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "contact.h"
#include "populate.h"

char contact_idx[100]; // store indexes of the contacts in search contact
int contact_list; // count of contact_idx

void initialize(Addressbook *addressbook)
{
        addressbook->contactCount = 0;
        populateAddressbook(addressbook);
        //open the file in r mode
        FILE *fptr = fopen("Contact.csv","r");
        //copying contactcount and contact details
        fscanf(fptr,"#%d",&addressbook->contactCount);
        for(int i = 0; i < addressbook->contactCount; i++)
        {
            fscanf(fptr,"\n%[^,],%[^,],%[^\n]",addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
        }
    
        
}
void createcontact(Addressbook *addressbook)
{

        char name[20];
        char phone[30];
        char email[50];
        int choice = 0;
        printf("Enter name : ");
        scanf(" %[^\n]",name);
        // storing name in addressbook->contactCount
        strcpy(addressbook->contacts[addressbook->contactCount].name,name);
        //validatecontact function call
        validatecontact(addressbook,phone);
        strcpy(addressbook->contacts[addressbook->contactCount].phone,phone);
        //validateemail function call
        validateemail(addressbook,email);
        strcpy(addressbook->contacts[addressbook->contactCount].email,email);
        printf("contact saved successfully\n");
        addressbook->contactCount++;
        return;

}

void listcontact(Addressbook *addressbook)
{
        // printing the contacts that are present in addressbook->contacts array
        printf("------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-30s | %-20s | %-50s\n","no", "name", "phone", "email");
        printf("------------------------------------------------------------------------------------------------\n");
        for(int i = 0; i < addressbook->contactCount; i++)
        {
                printf("| %-5d | %-30s | %-20s | %-50s\n", i + 1, addressbook->contacts[i].name, addressbook->contacts[i].phone, 
                                addressbook->contacts[i].email);
        }
}

void searchcontact(Addressbook *addressbook)
{
        char name[30];
        char phone[20];
        char email[50];
        int option;
        int index = 0;
        contact_list = 0;
        printf("enter the option to search :\n ");
        printf("1.by name :\n");
        printf("2.by mobile number : \n");
        printf("3.by mail id : \n");
        printf("enter the option : ");
        int result = scanf(" %d", &option);
        if(result)
        {
                switch(option)
                {
                        case 1:
                                printf("enter the name : ");
                                scanf(" %[^\n]",name);
                                for(int i = 0; i < addressbook->contactCount; i++)
                                {
                                        //if name is present in the list then stores that in array
                                        if(strstr(addressbook->contacts[i].name,name) != NULL)
                                        {
                                                contact_idx[index++] = i;
                                                contact_list++;

                                        }
                                }
                                break;
                        case 2:
                                printf("enter mobile number : ");
                                scanf(" %s", phone);
                                for(int i = 0; i < addressbook->contactCount; i++)
                                {
                                        //if mobile number is present in the list then stores that in array
                                        if(strstr(addressbook->contacts[i].phone,phone) != NULL)
                                        {
                                                contact_idx[index++] = i;
                                                contact_list++;
                                        }
                                }
                                break;

                        case 3:
                                printf("enter mail : ");
                                scanf(" %s", email);
                                for(int i = 0; i < addressbook->contactCount; i++)
                                {
                                        //if email is present in the list then stores that in array.
                                        if(strstr(addressbook->contacts[i].email,email) != NULL) 
                                        {
                                                contact_idx[index++] = i;
                                                contact_list++;

                                        }
                                }
                                break;

                        default:
                                printf("Invalid option\n");
                                return;

                }
        }
        else
        {
                printf("invalid choice\n");
                while(getchar() != '\n');
                return;
        }

        if(index == 0)
        {
                printf("contact not found\n");
                return;
        }
        else 
        {
                printf("------------------------------------------------------------------------------------------------\n");
                printf(" | %-5s | %-30s | %-20s | %-50s\n","no", "name", "phone", "email");
                printf("------------------------------------------------------------------------------------------------\n");
                for(int index = 0; index < contact_list; index++)
                {
                        int actual_index = contact_idx[index];
                        printf("| %-5d | %-30s | %-20s | %-50s\n", index + 1, addressbook->contacts[actual_index].name, 
                                        addressbook->contacts[actual_index].phone, addressbook->contacts[actual_index].email);
                }
        }
}
void editcontact(Addressbook *addressbook)
{

        char name[20];
        char phone[50];
        char email[50];
        int choice;
        int flag = 0;
        int actual_index;
        //calling searchcontact function
        searchcontact(addressbook);
        if(addressbook->contactCount == 0)
        {
                printf("no contacts present in the address book\n");
                return;
        }
        actual_index = contact_idx[0];
        //contact list contain more than 1 contact of same .
        if (contact_list > 1)
        {
                printf("Enter the contact_idx of the contact to edit(0 to %d) : \n", contact_list);
                int i;
                scanf("%d", &i);
                //checking index is in the range
                if(i >= 1 && i <= contact_list)
                {
                    actual_index = contact_idx[i - 1];
                }
                else
                    printf("invalid index\n");
        }
        if(contact_list != 0)
        {
                printf("1. Name \n");
                printf("2. Mobile number \n");
                printf("3. Email \n");
                int opt;
                printf("enter the option to edit : ");
                int result = scanf(" %d", &opt);
                if(result)
                {
                        switch(opt)
                        {
                                case 1: 
                                        printf("Enter name : ");
                                        scanf(" %[^\n]",name);
                                        strcpy(addressbook->contacts[actual_index].name,name);
                                        break;
                                case 2:
                                        //function call validatecontact
                                        validatecontact(addressbook,phone);
                                        strcpy(addressbook->contacts[actual_index].phone,phone);
                                        break;
                                case 3:
                                        //function call validateemail
                                        validateemail(addressbook,email);
                                        strcpy(addressbook->contacts[actual_index].email,email);
                        }
                }
                else
                {
                        printf("invalid option enter\n");
                        while(getchar() != '\n');
                        return;
                }
        }
        else
                return;

        printf("contact edited successfully\n");
}
void deletecontact(Addressbook *addressbook)
{ 
        int actual_index;
        if(addressbook->contactCount == 0)
        {
                printf("no contacts present in the address book\n");
                return;
        }
        //calling searchcontact function
        searchcontact(addressbook);
        actual_index = contact_idx[0];
        if(contact_list > 1)
        {
                printf("multiple contacts are found : \n");
                printf("Enter the contact_idx of the contact to delete(0 to %d) : \n", contact_list);
                int i;
                scanf("%d", &i);
                // checking index is in the range or not
                if(i >= 1 && i <= contact_list)
                {
                    actual_index = contact_idx[i - 1];
                }
                else
                    printf("invalid index\n");
        }
        //asking permission to user
        printf("do you want to delete the contact(Y/N) : ");
        char ch;
        scanf(" %c",&ch);
        if(ch == 'Y' || ch == 'y')
        {
            if(contact_list != 0)
            {
                for (int j = actual_index; j < addressbook->contactCount - 1; j++) 
                {
                        //swap the contacts present in addressbook.
                        addressbook->contacts[j]= addressbook->contacts[j + 1];
                }

            }
        }
        else
                return;
        addressbook->contactCount--;
        printf("contact deleted successfully\n");
}
void savecontact(Addressbook *addressbook)
{
        //open the file in w mode
        FILE *fp = fopen("Contact.csv", "w");
        //copying contactcount and contact details
        fprintf(fp, "#%d\n", addressbook->contactCount);
        for(int i = 0; i < addressbook->contactCount; i++)
        {
                fprintf(fp,"%s,%s,%s\n",addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
        }
        printf("contact saved successfully\n");
        fclose(fp); // close the file pointer
}
#if 0
void loadcontact(Addressbook *addressbook)
{
    //open the file in r mode
    FILE *fptr = fopen("Contact.csv","r");
    //copying contactcount and contact details
    fscanf(fptr,"#%d",&addressbook->contactCount);
    for(int i = 0; i < addressbook->contactCount; i++)
    {
        fscanf(fptr,"\n%[^,],%[^,],%[^\n]",addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
    }
    
    fclose(fptr); // close the file pointer
}
#endif
void validatecontact(Addressbook *addressbook, char * phone)
{
phone:
        printf("enter mobile number : ");
        scanf(" %[^\n]",phone);
        int flag = 0;
        int choice = 0;
        //length of the mobile number should be 10.
        if(strlen(phone) != 10)
        {
                printf("invalid number length\n");
                flag = 1;

        }   
        else
        {
                for(int i = 0; i < strlen(phone); i++)
                {
                        //mobile number must contains 0-9 digits.
                        if((phone[i] < '0' ) || (phone[i] > '9'))
                        {
                                printf("invalid characters in the number\n");
                                flag = 1;
                                break;
                        }
                }
                for(int i = 0; i < addressbook->contactCount; i++)
                {
                        //checking mobile number present in addressbook
                        if(!(strcmp(addressbook->contacts[i].phone,phone)))
                        {
                                printf("phone number already existed\n");
                                flag = 1;
                                break;

                        }
                }

        }

        while(flag)
        {
                printf("1.re enter\n 2.exit\n");
                printf("enter choice : ");
                scanf("%d", &choice);
                switch(choice)
                {
                        case 1:
                                goto phone;
                                break;
                        case 2:
                                return;
                }


        }
}
void validateemail(Addressbook *addressbook,char * email)
{
email:
        printf("enter email : ");
        scanf(" %s", email);
        int flag = 0;
        int choice = 0;
        char * temp;
        int a_index;
        //checking @ present in email or not.
        temp = (strchr(email, '@'));
        a_index = temp - email;
        for(int i = 0; i < addressbook->contactCount; i++)
        {
                //if mobile number already present in the list .
                if(!(strcmp(addressbook->contacts[i].email,email)))
                {
                        printf("email already existed\n");
                        flag = 1;
                        break;
                }
        }

        if (temp == NULL)
        {
                printf("error in email\n");
                flag = 1;

        }
        //if @ present in 1st position then it is invalid
        else if(a_index == 0)
        {
                printf("invalid mail\n");
                flag = 1;
        }
        else
        {
                //checking .com present in mail or not.
                temp = (strstr(email, ".com"));
                if(temp == NULL)
                {
                        printf("error\n");
                        flag = 1;
                }
                else
                {
                        int d_index = temp - email;
                        //checking in b.w @ and .com something is present or not.
                        if((d_index != strlen(email) - 4) || (d_index == a_index + 1))
                        {
                                printf("error\n");
                                flag = 1;
                        }
                }
        }
        while(flag)
        {
                printf("1.re enter\n 2.exit\n");
                printf("enter choice : ");
                scanf("%d",&choice);
                switch(choice)
                {
                        case 1:
                                goto email;
                                break;
                        case 2:
                                return;
                }
        }
        
}


