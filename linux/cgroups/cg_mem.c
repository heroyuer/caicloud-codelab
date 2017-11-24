// cgroups "Hello World".

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  int i;
  char *p;

  // Loop 40 times to consume 40MB memory.
  for (i = 0; i < 40; ++i) {
    if ((p = malloc(1<<20)) == NULL) {
      printf("malloc failed at %d MB\n", i);
      return 0;
    }

    // Consume the memory.
    memset(p, 0, (1<<20));
    printf("allocated %d MB\n", i+1);

    usleep(100*1000);
  }

  printf("Done!\n");
  return 0;
}
