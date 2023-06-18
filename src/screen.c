//
// Created by Fuad on 04/06/2023.
//
/**
 * Structure of a screen is to display instructions to the user, then perform their actions based on those instructions
 */

#include <screen.h>
#include <malloc.h>
#include <string.h>
#include <contact.h>
#include <stdio.h>
#include <stdbool.h>

static Contact *selected_contact;

Screen initStartScreen() {
    Screen *startScreen = malloc(sizeof(Screen));

    setNextScreen(startScreen);

    return *startScreen;
}

void setScreenTo(Screen *screen, int to) {
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
        screen->id = 0;
        strcpy(screen->name, "Home Screen");
        strcpy(screen->description, "Welcome to the Phonebook app.");
    }
}

void setNextScreen(Screen *screen) {
    if (screen->id == 0) setScreenTo(screen, SCREEN_CREATE_CONTACT);
    else if(screen->id == SCREEN_CREATE_CONTACT) setScreenTo(screen, SCREEN_CONTACT_LIST);
    else { //Create contact screen
        screen->id = 0;
        strcpy(screen->name, "Home Screen");
        strcpy(screen->description, "Welcome to the Phonebook app.");
        strcpy(screen->instructions, "Enter 1 to create a new contact\n2 to view existing contacts\n0 to exit");
    }
}

void setPreviousScreen(Screen *screen) {
    if (screen->id == SCREEN_CREATE_CONTACT) setScreenTo(screen, -1); //Create contact screen
    else if(screen->id == SCREEN_CONTACT_LIST) setScreenTo(screen, -1);
    else if(screen->id == SCREEN_UPDATE_CONTACT) setScreenTo(screen, SCREEN_CONTACT_LIST);
}

/**
 * Checks the input if it has a new line to determine
 * if the input buffer is empty or not. If the new line is present,
 * it clears the remaining unneeded characters in the buffer
 * @param holder
 */
void clearBuffer(char *holder) {
    if(!strchr(holder, '\n')) {
        //these 2 clears the buffer up to the new line
        scanf("%*[^\n]");
        scanf("%*c");
    }
}

static bool getAddMoreInput() {
    while(true) {
        printf("Would you like to add another number [Y/N]: ");

        char input = (char) getchar();
        getchar();

        if (input == 'y' || input == 'Y') return true;
        else if (input == 'n' || input == 'N') return false;
        else printf("Invalid input\n");
    }
}

int performScreenAction(Screen screen) {
    printf("%s\n", screen.description);

    if(screen.id == 0) { //Start/Home screen
        printf("%s\n", "Enter 1 to create a new contact\n2 to view existing contacts\n0 to exit");

        while (true) {
            printf("Input: ");

            char input = (char) getchar();
            getchar(); //remove the new line entered

            if(input == '1') {
                setNextScreen(&screen);
                return SCREEN_CREATE_CONTACT;
            }
            else if(input == '2') {
                return SCREEN_CONTACT_LIST;
            }
            else if (input == '0') return EXIT;

            else {
                printf("Invalid input\n");
                return INVALID;
            }
        }
    }
    else if(screen.id == SCREEN_CREATE_CONTACT) { //Create contact screen
        Contact contact;
        char tempStorage[255];

        printf("Name:");
        fgets(tempStorage, 255, stdin);
        clearBuffer(tempStorage);
        strcpy(contact.name, tempStorage);

        for(int i = 0; i < ALLOWED_NUMBER_LIMIT; i++) {
            printf("Number %d: ", i+1);
            fgets(tempStorage, PHONE_NUMBER_LENGTH, stdin);
            clearBuffer(tempStorage);
            strcpy_s(contact.numbers[i], PHONE_NUMBER_LENGTH, tempStorage);

            if(!getAddMoreInput()) break;
        }

        bool isSaved = save_contact(contact, true);

        if(isSaved) printf("Contact (%s) saved\n", contact.name);
        else printf("Error saving contact\n");

        return SCREEN_PREVIOUS;
    }
    else if(screen.id == SCREEN_CONTACT_LIST) {
        int contact_size = get_contact_size();
        Contact contacts[contact_size];

        get_all_contacts(contacts);

        printf("You have %d contacts saved\n\n", contact_size);

        for(int i = 1; i < contact_size+1; i++) {
            printf("Enter %d to view %s\n", i, contacts[i-1].name);
        }

        printf("Enter 0 to go back \n");

        while(true) {
            printf("Input: ");

            char input = (char) getchar();
            getchar(); //Clear the buffer

            if(input == 0) return SCREEN_PREVIOUS;
            else if(input > -1 && input <= contact_size) {
                selected_contact = &(contacts[input+1]);
                return SCREEN_UPDATE_CONTACT;
            }
            else printf("Invalid input\n");
        }
    }
    else return INVALID;
}


