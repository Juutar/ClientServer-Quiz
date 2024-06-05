#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socketUtil.h"

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

char* SERVERIP;
int PORT;

//utility to keep return value checking clean
void errcheck(int rc, char* origin) {
    if (rc <= -1) {
        perror(origin);
        exit(EXIT_FAILURE);
    }
}

void init_listening_endpoint(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Command Format: server PIV4Address port\n");
        exit(EXIT_SUCCESS);
    }
    SERVERIP = argv[1];
    PORT = atoi(argv[2]);
}

void basic_sockaddr_in_init(struct sockaddr_in* addr) {
    memset(addr, 0, sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(SERVERIP);
    addr->sin_port = htons(PORT);
}

int get_message(char** message, int socket_fd) {
    (*message) = malloc(sizeof(char) * BUFFERSIZE);
    int total_read = 0;

    char* buffptr_position = (*message);
    int local_read = 0;

    while (total_read < BUFFERSIZE) {
        local_read = read(socket_fd, buffptr_position, BUFFERSIZE - total_read);

        if (local_read == 0) { break; }
        if (local_read == -1 && errno == EINTR) { continue; }
        errcheck(local_read, "buffered get");

        total_read += local_read;
        buffptr_position += local_read;
    }
    return total_read;
}

int send_message(char** message, int socket_fd) {
    int total_sent = 0;

    char* buffprt_position = (*message);
    int local_sent = 0;

    while (total_sent < BUFFERSIZE) {
        local_sent = write(socket_fd, buffprt_position, BUFFERSIZE - total_sent);

        if (local_sent == 0) { break; }
        if (local_sent == -1 && errno == EINTR) { continue; }
        errcheck(local_sent, "buffered send");

        total_sent += local_sent;
        buffprt_position += local_sent;
    }
    return total_sent;
}

void print_listening_endpoint() {
    printf("<Listening on %s:%d>\n", SERVERIP, PORT);
    printf("<Press ctrl-C to terminate>\n");
}
