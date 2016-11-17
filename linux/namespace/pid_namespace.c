// PID namespace 'Hello world'.

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

struct clone_args {
  char **argv;
};

static int child_exec(void *stuff)
{
  // Because the parent of the child created by clone() is in a different
  // namespace, the child cannot "see" the parent; therefore, getppid()
  // reports the parent PID as being zero.
  printf("child pid from child: %ld\n", (long)getpid());    /* 1 */
  printf("parent pid from parent: %ld\n", (long)getppid()); /* 0 */

  struct clone_args *args = (struct clone_args *)stuff;
  if (execvp(args->argv[0], args->argv) != 0) {
    fprintf(stderr, "failed to execvp argments %d\n", strerror(errno));
    exit(-1);
  }
  // We should never reach here!
  exit(-1);
}

int main(int argc, char **argv)
{
  struct clone_args args;
  args.argv = &argv[1];

  // The clone() function will create a new process by cloning the current
  // one and start execution at the beginning of the child_fn() function.
  // However, while doing so, it detaches the new process from the original
  // process tree and creates a separate process tree for the new process.
  // `child_stack+STACK_SIZE` means pointing to the start of downwardly growing
  // stack - 'child_stack' has a lower address.
  pid_t child_pid = clone(child_exec, child_stack+STACK_SIZE,
                          CLONE_NEWPID | SIGCHLD, &args);

  // The child pid here is the pid of the new child process in 'current
  // namespace'; in the new namespace, the pid is 0, as printed in the
  // child_fn() above.
  printf("child pid from parent: %ld\n", (long)child_pid); /* e.g. 25658 */

  // Note these processes still have unrestricted access to other common or
  // shared resources. For example, the networking interface: if the child
  // process created above were to listen on port 80, it would prevent every
  // other process on the system from being able to listen on it. Therefore,
  // we need other kind of namespace, e.g. net.

  waitpid(child_pid, NULL, 0);
  return 0;
}
