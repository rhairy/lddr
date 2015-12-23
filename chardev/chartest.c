/* chartest.c - open char device and read from it. */

#include <fcntl.h> // open()
#include <stdio.h>
#include <unistd.h>

/* Must be supplied with a file path as the first argument. */
int main(int argc, char **argv)
{
  /* Check arguments. */
  if (argc < 2 || argc > 2) {
    printf("ERROR - Program only accepts a file path argument.\n");
    return -1;
  } 

  /* Attempt to get a file descriptor. */
  int fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    printf("ERROR - Could not open file %s\n", argv[1]);
    return -1;
  }

  /* Attempt to read from opened file descriptor. */
  int rdBytes = 0;
  char rdBuf[1024];

  while(read(fd, rdBuf, 1024)) {
    printf("%s\n", rdBuf);
  }
  
  return 0;
}
