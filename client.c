#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client_quiz.h"
#include "socketUtil.h"

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/


int main(int argc, char* argv[]) {

    init_listening_endpoint(argc, argv);

    //socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    errcheck(client_fd, "client socket");

    //connect
    struct sockaddr_in client_addr;
    basic_sockaddr_in_init(&client_addr);
    errcheck(connect(client_fd, (struct sockaddr* )&client_addr, sizeof(struct sockaddr)), "client connect");

    //exchange
    run_client_quiz(client_fd);

    //close
    errcheck(close(client_fd), "server listening close");

    exit(EXIT_SUCCESS);
}


