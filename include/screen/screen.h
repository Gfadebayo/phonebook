//
// Created by Fuad on 04/06/2023.
//

#ifndef PHONEBOOK_SCREEN_H
#define PHONEBOOK_SCREEN_H

#include <stdbool.h>


#define INVALID               (-1)
#define EXIT                    0
#define SCREEN_NEXT             1
#define SCREEN_PREVIOUS         2
#define SCREEN_HOME             3
#define SCREEN_CREATE_CONTACT   4
#define SCREEN_CONTACT_LIST     5
#define SCREEN_UPDATE_CONTACT   6
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
Screen init_start_screen();

/**
 * Updates the screen struct according to what to is
 * @param screen the screen struct
 * @param to the id of the next screen
 */
void set_screen_to(Screen *screen, int to);

/**
 * Overwrite the members in the Screen struct to the
 * values of the next screen as gotten from the id of the current
 * screen
 * @param screen
 */
void set_next_screen(Screen *screen);

/**
 * Overwrite the members in the Screen to the values of the previous screen
 * as gotten from the id of the current screen
 * @param screen
 */
void set_previous_screen(Screen *screen);

/**
 * Perform the action of a particular screen eg collecting input from the user
 * or simply moving to another screen
 * @param screen the screen with info to help determine what action should be performed
 * @return the next screen to navigate to. Might be something vague like SCREEN_NEXT or SCREEN_PREVIOUS
 * or the exact screen to move to.
 */
int perform_screen_action(Screen screen);

static bool get_add_more_input();
static int home_action();
static int create_contact_action();
static int update_contact_action();
static int view_contact_list_action();

#endif //PHONEBOOK_SCREEN_H
