// Net namespace 'Hello world'.

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

static int child_fn()
{
  // Calling unshare() from inside the init process lets you
  // create a new namespace after a new process has been spawned.
  unshare(CLONE_NEWNET);

  printf("new `net` Namespace:\n");
  system("ip link");
  return 0;
}

int main()
{
  printf("original `net` Namespace:\n");
  system("ip link");
  printf("\n");

  pid_t child_pid = clone(child_fn, child_stack+STACK_SIZE,
                          CLONE_NEWPID | SIGCHLD, NULL);

  waitpid(child_pid, NULL, 0);
  return 0;
}
