//
// Created by Fuad on 04/06/2023.
//

#ifndef PHONEBOOK_SCREEN_H
#define PHONEBOOK_SCREEN_H

#define INVALID (-1)
#define EXIT 0
#define SCREEN_NEXT 1
#define SCREEN_PREVIOUS 2
#define SCREEN_CREATE_CONTACT   3
#define SCREEN_CONTACT_LIST     4
#define SCREEN_UPDATE_CONTACT 5
//#define SCREEN_CREATE_CONTACT 1
//#define SCREEN_CREATE_CONTACT 1

typedef struct {
    int id;

    char name[255];

    char description[255];

    void *previous;

    void *next;
} Screen;

/**
 * Allocates a memory address in the stack to store a screen variable
 * @return The start screen of the program.
 */
Screen initStartScreen();

/**
 * Overwrite the members in the Screen struct to the
 * values of the next screen as gotten from the id of the current
 * screen
 * @param screen
 */
void setNextScreen(Screen *screen);

/**
 * Perform the action of a particular screen eg collecting input from the user
 * or simply moving to another screen
 * @param screen the screen with info to help determine what action should be performed
 */
int performScreenAction(Screen screen);

/**
 * Overwrite the members in the Screen to the values of the previous screen
 * as gotten from the id of the current screen
 * @param screen
 */
void setPreviousScreen(Screen *screen);


void setScreenTo(Screen *screen, int to);

void displayInstructions();

void displayNewContactInstructions();

#endif //PHONEBOOK_SCREEN_H
