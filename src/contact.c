//
// Created by Fuad on 04/06/2023.
//

#include <contact.h>
#include <jansson.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define SAVE_FILE "phonebook.json"

static json_t *phonebook_json;

static void json_to_contact(json_t *json, Contact *contact) {
    if(!json_is_object(json)) return;

    contact->id = (int) json_integer_value(json_object_get(json, "id"));
    strcpy(contact->name, json_string_value(json_object_get(json, "name")));
    contact->created_at = json_integer_value(json_object_get(json, "created_at"));
    contact->updated_at = json_integer_value(json_object_get(json, "updated_at"));

    json_t *numbers = json_object_get(json, "number");

    size_t number_size = json_array_size(numbers);

    for(int i = 0; i < number_size; i++) {
        strcpy(contact->numbers[i], json_string_value(json_array_get(numbers, i)));
    }
}

void load_db_file() {
    errno = 0;
    FILE *file = fopen(SAVE_FILE, "r");
    json_error_t error;

    if(file) {
        phonebook_json = json_loadf(file, JSON_ALLOW_NUL, &error);

        printf("Error %s", error.text);
    }
    else if(errno == ENOENT) {
        phonebook_json = json_array();
    }

    fclose(file);
}

bool save_contact(Contact contact, bool isNew) {
    json_t *contact_json = json_object();

    json_t *numbers_array = json_array();

    for(int i = 0; i < ALLOWED_NUMBER_LIMIT; i++){
        if(strlen(contact.numbers[i]) <= 0) break;

        json_array_append(numbers_array, json_string(contact.numbers[i]));
    }

    time_t t;
    time(&t);
    long long now = t;

    long long created = isNew ? now : contact.created_at;

    json_object_set_new(contact_json, "id", json_integer(contact.id));
    json_object_set_new(contact_json, "name", json_string(contact.name));
    json_object_set_new(contact_json, "number", numbers_array);
    json_object_set_new(contact_json, "created_at", json_integer(created));
    json_object_set_new(contact_json, "updated_at", json_integer(now));

    if (phonebook_json) {
        json_array_append(phonebook_json, contact_json);

        return true;
    }
    else return false;
}

void save_to_file() {
    FILE *file = fopen(SAVE_FILE, "w");

    if(phonebook_json) {
        json_dumpf(phonebook_json, file, JSON_INDENT(4) | JSON_COMPACT);

        fclose(file);
        free(phonebook_json);
    }
    else printf("Error the json is not available\n");
}

int get_contact_size() {
    return (int) json_array_size(phonebook_json);
}

void get_all_contacts(Contact *contacts) {
    size_t contact_size = get_contact_size();

    for(int i = 0; i < contact_size; i++) {
        Contact contact;
        json_to_contact(json_array_get(phonebook_json, i), &contact);

        contacts[i] = contact;
    }
}

