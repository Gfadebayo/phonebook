//
// Created by Fuad on 19/06/2023.
//

#ifndef PHONEBOOK_UTIL_H
#define PHONEBOOK_UTIL_H

/**
 * The holder parameter is used to determine
 * if the input buffer still contains the newline or not.
 * If newline is in holder then the input buffer is clear,
 * if not then this function clears all characters in the input buffer
 * up to and including the new line.
 * \n\n
 * This basically helps to prevent incorrect values spilling over to the next input
 * action as the input buffer will still hold characters in the previous action that
 * were not consumed
 *
 * @param holder should be the result of the input buffer
 */
void clear_buffer(char *holder);

#endif //PHONEBOOK_UTIL_H
