#include "pipe_networking.h"
#include <ctype.h>
#include <signal.h>

static void sighandler(int sig) {
  if (sig == SIGINT) {
    remove("mario");
    exit(0);
  }
}


int main() {

  signal(SIGINT, sighandler);

  int to_client;
  int from_client;

  while (1) {
    from_client = server_handshake( &to_client );
    // printf("pid: %d\tfrom_client: %d\tto_client: %d\n", getpid(), from_client, to_client);
    
    // get input from client
    char input[100];
    read(from_client, input, 100);

    // modify input
    int i = 0;
    while (input[i] != '\n') {
      input[i] = toupper(input[i]);
      i++;
    }

    // sends input back to client
    write(to_client, input, 100);
  }
}