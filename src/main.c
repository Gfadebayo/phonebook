#include <stdio.h>
#include <screen/screen.h>
#include <contact/contact.h>

int main() {
    load_db_file();

    Screen startScreen = init_start_screen();

    int status;
    while((status = perform_screen_action(startScreen)) != EXIT) {
        if(status == SCREEN_NEXT) set_next_screen(&startScreen);
        else if(status == SCREEN_PREVIOUS) set_previous_screen(&startScreen);
        else set_screen_to(&startScreen, status);
    }

    printf("Saving...\n");
    save_to_file();

    return 0;
}