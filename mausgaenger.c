
#include "./mausgaenger.h"
#include <fcntl.h>
#include <inttypes.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MOUSEFILE "/dev/input/event6"

int mouse(void) {
  int fd;
  struct input_event ie;
  if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    perror("opening device failed.");
    exit(EXIT_FAILURE);
  }
  while (read(fd, &ie, sizeof(struct input_event))) {
    printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
  }
  return 0;
}

#pragma weak main
int main (int argc, char** argv) {
  return mouse();
}
