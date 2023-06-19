//
// Created by Fuad on 19/06/2023.
//

#include <string.h>
#include <stdio.h>


void clear_buffer(char *holder) {
    if(!strchr(holder, '\n')) {
        //these 2 clears the buffer up to the new line
        scanf("%*[^\n]");
        scanf("%*c");
    }
}

void clean_input() {

}
