#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (1) {
    printf("$ ");
    fflush(stdout);

    char input[100];
    char* s = fgets(input, 100, stdin);

    if (s == 0) {
      return 0;
    }
    int l = strlen(input);
    input[l - 1] = 0;  // Remove trailing newline

    char* cmd = input;
    char* args[10];  // Array to hold command and arguments
    int i = 0;

    args[i] = strtok(input, " ");
    while (args[i] != NULL && i < 9) {
      i++;
      args[i] = strtok(NULL, " ");
    }

    cmd = args[0];  // First token is the command

    if (cmd == NULL) {
      continue;  // If the user enters nothing, prompt again
    }
    //___________________________________________________________
    if (strcmp("exit", cmd) == 0) {
      return 0;

    }
    //___________________________________________________________
    else if (strcmp("pwd", cmd) == 0) {
      char cwd[1024];
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
      } else {
        perror("getcwd() error");
      }
    }
    //___________________________________________________________
    else if (strcmp("cd", cmd) == 0) {
      if (args[1] == NULL) {
        printf("cd: missing argument\n");
      } else {
        if (chdir(args[1]) != 0) {
          perror("cd failed");
        }
      }
    }
    //___________________________________________________________
    else if (strcmp("ls", cmd) == 0) {
      DIR* d;
      struct dirent* dir;
      char* path = args[1] ? args[1] : ".";  // Default to current directory

      d = opendir(path);
      if (d) {
        while ((dir = readdir(d)) != NULL) {
          printf("%s\n", dir->d_name);
        }
        closedir(d);
      } else {
        perror("ls failed");
      }
    }
    //___________________________________________________________
    else if (strcmp("type", cmd) == 0) {
      if (strcmp("echo", args[1]) == 0 || strcmp("type", args[1]) == 0 ||
          strcmp("exit", args[1]) == 0 || strcmp("pwd", args[1]) == 0 ||
          strcmp("cd", args[1]) == 0 || strcmp("ls", args[1]) == 0) {
        printf("%s is a shell builtin\n", args[1]);
      } else {
        printf("%s not found\n", args[1]);
      }
    }
    //___________________________________________________________
    else if (strcmp("echo", cmd) == 0) {
      for (int j = 1; args[j] != NULL; j++) {
        printf("%s ", args[j]);
      }
      printf("\n");
      fflush(stdout);
    }
    //___________________________________________________________
    else {
      pid_t pid = fork();
      if (pid == 0) {
        // Child process
        execvp(cmd, args);
        perror("execvp failed");  // If execvp returns, there was an error
        return 1;
      } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
      } else {
        perror("fork failed");
      }
    }
  }

  return 1;
}
