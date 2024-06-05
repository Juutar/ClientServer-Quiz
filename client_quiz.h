#include <stdbool.h>

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

void run_client_quiz(int client_fd);
bool quiz_ended(char* message);
void send_user_answer(int client_fd);
bool get_quiz_prompt(int client_fd);
