#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_quiz.h"
#include "socketUtil.h"

/**
 * Alice Karatchentzeff de Vienne
 * 22707181
 * alice.karatchentzeff@ucdconnect.ie
*/

int main(int argc, char* argv[]) {

    //initialize variables
    init_listening_endpoint(argc, argv);

    //socket
    int listening_fd = socket(AF_INET, SOCK_STREAM, 0);
    errcheck(listening_fd, "server listening socket");
    int option_reuse = 1;
    errcheck(setsockopt(listening_fd, SOL_SOCKET, SO_REUSEADDR, &option_reuse, sizeof(int)), "server setsockopt");

    //bind
    struct sockaddr_in listening_addr;
    basic_sockaddr_in_init(&listening_addr);
    errcheck(bind(listening_fd, (struct sockaddr* )&listening_addr, sizeof(struct sockaddr_in)), "server bind");

    //listen
    errcheck(listen(listening_fd, BACKLOG), "server listen");

    //accept loop
    struct sockaddr_storage connect_addr;
    socklen_t connect_addr_len = sizeof(struct sockaddr_storage);
    while (1) {
        print_listening_endpoint();
        int connect_fd = accept(listening_fd, (struct sockaddr* )&connect_addr, &connect_addr_len);
        errcheck(connect_fd, "server connected socket");
        run_server_quiz(connect_fd);
        errcheck(close(connect_fd), "server connect close");
    }

    errcheck(close(listening_fd), "server listening close");

    exit(EXIT_SUCCESS);
}
