#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define BUF_SIZE 8192
#define ARGS_SIZE 256

void execute_command(char **args) {
  int pid = fork();

  if (pid == 0) {
    // Child process
    execvp(args[0], args);
    perror("exec failed"); // This runs only if execvp fails
    exit(1);
  }
  else if (pid > 0) {
    // Parent process
    wait(NULL);
  }
  else {
    perror("Fork failed");
  }
}

void shell_loop() {
  char buf[BUF_SIZE];
  char *args[ARGS_SIZE];

  while (true) {
    printf("> ");
    fflush(stdout);

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      break;
    }

    buf[strcspn(buf, "\n")] = 0;  // Remove newline

    char *token = strtok(buf, " ");
    int i = 0;

    while (token != NULL && i < ARGS_SIZE - 1) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }

    args[i] = NULL;

    if (i > 0) {
      execute_command(args);
    }
  }
}

int main() {
  shell_loop();
}