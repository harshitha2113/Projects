#ifndef CONTACT_H
#define CONTACt_H
#define MAX_CONTACTS 100
typedef struct
{
    char name[20];
    char phone[20];
    char email[50];
}Contact;
typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
}Addressbook;

void createcontact(Addressbook *addressbook);
void validatecontact(Addressbook *addressbook, char * phone);
void validateemail(Addressbook *addressbook,char * email);
void listcontact(Addressbook *addressbook);
void searchcontact(Addressbook *addressbook);
void editcontact(Addressbook *addressbook);
void deletecontact(Addressbook *addressbook);
void savecontact(Addressbook *addressbook);
//void loadcontact(Addressbook *addressbook);
void initialize(Addressbook *addressbook);
#endif

