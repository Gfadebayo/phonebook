//
// Created by Fuad on 04/06/2023.
//
/**
 * Structure of a screen is to display instructions to the user, then perform their actions based on those instructions
 */

#include <screen/screen.h>
#include <malloc.h>
#include <string.h>
#include <contact/contact.h>
#include <stdio.h>
#include <util/utils.h>

static Contact *selected_contact;

Screen init_start_screen() {
    Screen *startScreen = malloc(sizeof(Screen));

    set_next_screen(startScreen);

    return *startScreen;
}

void set_screen_to(Screen *screen, int to) {
    if(to == SCREEN_CREATE_CONTACT) {
        screen->id = SCREEN_CREATE_CONTACT;
        strcpy(screen->name, "Create Contact Screen");
        strcpy(screen->description, "A contact consists of the persons' name, and several associated numbers");
    }
    else if(to == SCREEN_CONTACT_LIST) {
        screen->id = SCREEN_CONTACT_LIST;
        strcpy(screen->name, "View contacts Screen");
        strcpy(screen->description, "You can view your contacts here");
    }
    else if(to == SCREEN_UPDATE_CONTACT) {
        screen->id = SCREEN_UPDATE_CONTACT;
        strcpy(screen->name, "Update contact Screen");
        strcpy(screen->description, "Here to show you a particular contact information");
    }
    else { //Home/Start screen
        screen->id = SCREEN_HOME;
        strcpy(screen->name, "Home Screen");
        strcpy(screen->description, "Welcome to the Phonebook app.");
    }
}

void set_next_screen(Screen *screen) {
    if (screen->id == SCREEN_HOME) set_screen_to(screen, SCREEN_CREATE_CONTACT);
    else if(screen->id == SCREEN_CREATE_CONTACT) set_screen_to(screen, SCREEN_CONTACT_LIST);
    else { //Create contact screen
        screen->id = SCREEN_HOME;
        strcpy(screen->name, "Home Screen");
        strcpy(screen->description, "Welcome to the Phonebook app.");
    }
}

void set_previous_screen(Screen *screen) {
    if (screen->id == SCREEN_CREATE_CONTACT) set_screen_to(screen, -1); //Create contact screen
    else if(screen->id == SCREEN_CONTACT_LIST) set_screen_to(screen, -1);
    else if(screen->id == SCREEN_UPDATE_CONTACT) set_screen_to(screen, SCREEN_CONTACT_LIST);
}

static bool get_add_more_input() {
    while(true) {
        printf("Would you like to add another number [Y/N]: ");

        char input = (char) getchar();
        getchar();

        if (input == 'y' || input == 'Y') return true;
        else if (input == 'n' || input == 'N') return false;
        else printf("Invalid input\n");
    }
}

int perform_screen_action(Screen screen) {
    printf("%s\n", screen.description);

    if (screen.id == SCREEN_HOME) return home_action();

    else if (screen.id == SCREEN_CREATE_CONTACT) return create_contact_action();

    else if (screen.id == SCREEN_CONTACT_LIST) return view_contact_list_action();

    else if (screen.id == SCREEN_UPDATE_CONTACT) return update_contact_action();

    else return INVALID;
}

static int home_action() {
    printf("%s\n", "Enter\n1 to create a new contact\n2 to view existing contacts\n0 to exit");

    while (true) {
        printf("Input: ");

        char input = (char) getchar();
        getchar(); //remove the new line entered

        if (input == '1') return SCREEN_CREATE_CONTACT;

        else if (input == '2') return SCREEN_CONTACT_LIST;

        else if (input == '0') return EXIT;

        else {
            printf("Invalid input\n");
            return INVALID;
        }
    }
}

static int create_contact_action() {
    Contact contact;
    char tempStorage[255];

    printf("Name: ");
    fgets(tempStorage, 255, stdin);
    clear_buffer(tempStorage);
    strcpy(contact.name, tempStorage);
    contact.name[strcspn(contact.name, "\n")] = 0;

    for (int i = 0; i < ALLOWED_NUMBER_LIMIT; i++) {
        printf("Number %d: ", i + 1);
        fgets(tempStorage, PHONE_NUMBER_LENGTH, stdin);
        clear_buffer(tempStorage);
        strcpy_s(contact.numbers[i], PHONE_NUMBER_LENGTH, tempStorage);
        contact.numbers[i][strcspn(contact.numbers[i], "\n")] = 0;

        if (!get_add_more_input()) break;
    }

    bool isSaved = save_contact(contact, true);

    if (isSaved) printf("Contact (%s) saved\n\n", contact.name);
    else printf("Error saving contact\n\n");

    return SCREEN_PREVIOUS;
}

static int view_contact_list_action() {
    int contact_size = get_contact_size();
    Contact contacts[contact_size];

    get_all_contacts(contacts);

    printf("You have %d contacts saved\n\n", contact_size);

    for (int i = 1; i < contact_size + 1; i++) {
        printf("Enter %d to view %s\n", i, contacts[i - 1].name);
    }

    printf("Enter 0 to go back \n");

    while (true) {
        printf("Input: ");

        int input = getchar() - '0';

        getchar(); //Clear the buffer

        if (input == 0) return SCREEN_PREVIOUS;
        else if (input >= 0 && input <= contact_size) {
            if (selected_contact == NULL) selected_contact = malloc(sizeof(Contact));
            memcpy(selected_contact, &(contacts[input + 1]), sizeof(Contact));
            return SCREEN_UPDATE_CONTACT;
        } else printf("Invalid input\n");
    }
}

static int update_contact_action() {
    printf("Contact name: %s\n", selected_contact->name);
    printf("Date created: %s\n", "2022");
    printf("Last updated: %s\n", "2022");

    printf("Enter\n1 to update contact name\n2 to change contact numbers\n3 to delete this contact\n4 to go back\n");

    while (true) {
        char input = (char) getchar();
        getchar(); //clear input buffer

        if (input == '1') {
            char name[255];
            printf("New name: ");
            fgets(name, 255, stdin);
            clear_buffer(name);

            strcpy(selected_contact->name, name);

            save_contact(*selected_contact, false);
            printf("Name updated");
        } else if (input == '2') {}
        else if (input == '3') {
            delete_contact(selected_contact->id);
            return SCREEN_PREVIOUS;
        } else if (input == '4') return SCREEN_PREVIOUS;
        else printf("Invalid input\n");
    }
}


