#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "socketUtil.h"
#include "client_quiz.h"

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

void run_client_quiz(int client_fd) {
    //breaks if quiz was ended by server
    while (true) {
        if (!get_quiz_prompt(client_fd)) { break; }
        send_user_answer(client_fd);
        if (!get_quiz_prompt(client_fd)) { break; }
    }
}

bool quiz_ended(char* message) {
    return strstr(message, "Goodbye") != NULL;
}

void send_user_answer(int client_fd) {
    char* input = NULL;
    size_t input_size = 0;
    ssize_t chars_read = getline(&input, &input_size, stdin);
    input[chars_read-1] = '\0';
    send_message(&input, client_fd);
    free(input);
}

bool get_quiz_prompt(int client_fd) {
    char* question = NULL;
    get_message(&question, client_fd);
    fprintf(stdout, "%s\n", question);
    bool continuing = !quiz_ended(question);
    free(question);
    return continuing;
}
