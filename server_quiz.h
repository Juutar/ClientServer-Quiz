#define NUM_QUESTIONS 5

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

void run_server_quiz(int client_fd);
int start_quiz(int client_fd);
void send_quiz_preamble(int client_fd);
void initialize_questions(int questions[], int num);
void ask_questions(int questions[], int* score, int client_fd);
void notify_right(int client_fd);
void notify_wrong(char* answer, int client_fd);
void conclude_quiz(int score, int client_fd);
bool num_in_array(int num, int array[], int limit);
