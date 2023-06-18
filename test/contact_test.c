//
// Created by Fuad on 14/06/2023.
//
#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include "../include/contact/contact.h"

void test_get_all_contact() {
    int contact_size = get_contact_size();

    Contact *contacts = malloc(sizeof(Contact) * contact_size);

    get_all_contacts(contacts);


    for(int i = 0; i < contact_size; i++) {
        printf("Name: %s, ID: %d\n", contacts[i].name, contacts[i].id);
    }

    free(contacts);
}

int main() {
    load_db_file();

    Contact *contact = malloc(sizeof(Contact));

    contact->id = 1;
    strcpy(contact->name, "Jotaro");
    strcpy(contact->numbers[0], "0812335621");
    strcpy(contact->numbers[1], "0812314721");
    strcpy(contact->numbers[2], "0912775621");
    strcpy(contact->numbers[3], "0912902677");
    strcpy(contact->numbers[4], "1912775621");

    save_contact(*contact, true);

    test_get_all_contact();

    save_to_file();

    return EXIT_SUCCESS;
}