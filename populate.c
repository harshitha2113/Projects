#include "contact.h"
static Contact dummyContacts[] = {
        {"john doe", "1234567890","john@example.com"},
        {"alice smith", "0987654321","alice@example.com"},
        {"bob johnson", "1112223333","bob@company.com"},
        {"carol white", "4445556666","carol@company.com"},
        {"david brown","7778889999","david@example.com"},
        {"Eve Davis", "6665554444", "eve@example.com"},
        {"Frank Miller", "3334445555", "frank@example.com"},
        {"Grace Wilson", "2223334444", "grace@example.com"},
        {"Hannah Clark", "5556667777", "hannah@example.com"},
        {"Ian Lewis", "8889990000","ian@example.com"}
};
void populateAddressbook(Addressbook* addressbook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for(int i = 0; i < numDummyContacts && addressbook->contactCount < 10; ++i)
    {
        addressbook->contacts[addressbook->contactCount++] = dummyContacts[i];
    }
}

