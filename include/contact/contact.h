//
// Created by Fuad on 04/06/2023.
//

#ifndef PHONEBOOK_CONTACT_H
#define PHONEBOOK_CONTACT_H

#include <stdbool.h>

#define PHONE_NUMBER_LENGTH 11
#define ALLOWED_NUMBER_LIMIT 10

typedef struct {
    int id;

    char name[255];

    char numbers[ALLOWED_NUMBER_LIMIT][PHONE_NUMBER_LENGTH];

    long long created_at;

    long long updated_at;
} Contact;

void load_db_file();
bool save_contact(Contact contact, bool isNew);
int get_contact_size();
void get_all_contacts(Contact *contacts);
void save_to_file();
void delete_contact(int contact_id);
#endif //PHONEBOOK_CONTACT_H
