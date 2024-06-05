#include <arpa/inet.h>
#define BACKLOG 10
#define BUFFERSIZE 300

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

void errcheck(int rc, char* origin);
void init_listening_endpoint(int argc, char* argv[]);
void basic_sockaddr_in_init(struct sockaddr_in* addr);
int get_message(char** message, int socket_fd);
int send_message(char** message, int socket_fd);
void print_listening_endpoint();

