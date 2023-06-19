#include <stdio.h>
#include <screen/screen.h>
#include <contact/contact.h>

int main() {
    load_db_file();

    Screen startScreen = initStartScreen();

    int status;
    while((status = perform_screen_action(startScreen)) != EXIT) {
        if(status == SCREEN_NEXT) setNextScreen(&startScreen);
        else if(status == SCREEN_PREVIOUS) setPreviousScreen(&startScreen);
        else setScreenTo(&startScreen, status);
    }

    printf("Saving...\n");
    save_to_file();

    return 0;
}