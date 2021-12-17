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
    int from_client = server_setup();

    int f = fork();

    if (f == 0) { // child
      // connects to client in child process
      to_client = server_connect(from_client);
      
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

      exit(0);
    }
  }
}