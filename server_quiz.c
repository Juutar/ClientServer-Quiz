#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "QuizDB.h"
#include "server_quiz.h"
#include "socketUtil.h"

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

void run_server_quiz(int client_fd) {
    if (!start_quiz(client_fd)) {
        return;
    }
    int questions[NUM_QUESTIONS];
    initialize_questions(questions, NUM_QUESTIONS);

    int score = 0;
    ask_questions(questions, &score, client_fd);

    conclude_quiz(score, client_fd);
}

int start_quiz(int client_fd) {
    send_quiz_preamble(client_fd);
    char* answer;
    while (1) {
        get_message(&answer, client_fd);
        if (strcmp("Y", answer) == 0) {
            char* message = "Let the quiz begin!";
            send_message(&message, client_fd);
            free(answer);
            return 1;
        }
        if (strcmp("q", answer) == 0) {
            char* message = "Goodbye!";
            send_message(&message, client_fd);
            free(answer);
            return 0;
        }
        free(answer);
        char* message = "Answer not recognized.";
        send_message(&message, client_fd);
        message = "Please enter either Y or q: ";
        send_message(&message, client_fd);
    }
}

void send_quiz_preamble(int client_fd) {
    char* message = "Welcome to Unix Programming Quiz!\n"
        "The quiz comprises five questions posed to you one after the other.\n"
        "You have only one attempt to answer a question.\n"
        "Your final score will be sent to you after conclusion of the quiz.\n"
        "To start the quiz, press Y and <enter>.\n"
        "To quit the quiz, press q and <enter>.";
    send_message(&message, client_fd);
}

void initialize_questions(int questions[], int num) {
    srand(time(NULL));
    int value;
    for (int i = 0; i < num; i++) {
        do {
            value = rand() % (sizeof(QuizQ)/sizeof(QuizQ[0]));
        } while (num_in_array(value, questions, i));
        questions[i] = value;
    }
}

void ask_questions(int questions[], int* score, int client_fd) {
    char* answer;
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        send_message(&QuizQ[questions[i]], client_fd);
        get_message(&answer, client_fd);
        if (strcmp(answer, QuizA[questions[i]]) == 0) {
            (*score)++;
            notify_right(client_fd);
        } else {
            notify_wrong(QuizA[questions[i]], client_fd);
        }
        free(answer);
    }
}

void notify_right(int client_fd) {
    char* message = "Right Answer.";
    send_message(&message, client_fd);
}

void notify_wrong(char* answer, int client_fd) {
    int message_size = 40 + strlen(answer);
    char* message = malloc(message_size);
    snprintf(message, message_size, "Wrong Answer. Right answer is %s.", answer);
    send_message(&message, client_fd);
    free(message);
}

void conclude_quiz(int score, int client_fd) {
    char* message = malloc(40);
    snprintf(message, 40, "Your quiz score is %d/5. Goodbye!", score);
    send_message(&message, client_fd);
    free(message);
}

bool num_in_array(int num, int array[], int limit) {
    for (int i = 0; i < limit; i++) {
        if (array[i] == num) {
            return true;
        }
    }
    return false;
}
