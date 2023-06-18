#include <stdio.h>
#include <screen.h>
#include <contact.h>

int main() {
    load_db_file();

    Screen startScreen = initStartScreen();

    int status;
    while((status = performScreenAction(startScreen)) != EXIT) {
        if(status == SCREEN_NEXT) setNextScreen(&startScreen);
        else if(status == SCREEN_PREVIOUS) setPreviousScreen(&startScreen);
        else setScreenTo(&startScreen, status);
    }

    printf("Saving...\n");
    save_to_file();

    return 0;
}